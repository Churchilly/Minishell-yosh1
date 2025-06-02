/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/02 16:50:32 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"
#include "parser.h"
#include <unistd.h>
#include "executer.h"
#include "str.h"
#include "environment.h"
#include "garbage_collector.h"

volatile int	g_signal = 0;

void	print_tokens(t_token *tokens); // for testing purposes
void	print_env(t_environment *env); // for testing purposes
void	free_tokens(t_token *tokens);
int		setup_parent_signals(void);
void	__attribute__((destructor));
void	bye(void);
void	*pointer_storage(int type, void *ptr);
void	print_asttree(t_astnode *parent);
char	*get_exec_path(char	*command);

static int	check_sequence_complete(char *input)
{
	int	quote;
	int	dquote;

	if (!input || !(*input))
		return (0);
	quote = 0;
	dquote = 0;
	while (*input)
	{
		if (*input == '\\')
			return (1);
		else if (*input == ';')
			return (1);
		else if (*input == '\"' && !(quote))
			dquote = !(dquote);
		else if (*input == '\'' && !(dquote))
			quote = !(quote);
		input++;
	}
	return (quote || dquote);
}

int	check_syntax(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].value)
	{
		if (tokens[i].type == TOKEN_DGREAT || tokens[i].type == TOKEN_DLESS
			|| tokens[i].type == TOKEN_LESS || tokens[i].type == TOKEN_GREAT)
		{
			if (tokens[i + 1].value == NULL || tokens[i + 1].type != TOKEN_WORD)
			{
				if (tokens[i + 1].type == TOKEN_DGREAT)
					printf("yosh1: syntax error near unexpected token `>>'\n");
				else if (tokens[i + 1].type
					== TOKEN_GREAT && tokens[i].type != TOKEN_LESS)
					printf("yosh1: syntax error near unexpected token `>'\n");
				else if (tokens[i + 1].type == TOKEN_DLESS)
					printf("yosh1: syntax error near unexpected token `<<'\n");
				else if (tokens[i + 1].type == TOKEN_LESS)
					printf("yosh1: syntax error near unexpected token `<'\n");
				else if (tokens[i + 1].type == TOKEN_PIPE)
					printf("yosh1: syntax error near unexpected token `|'\n");
				else
					printf("yosh1: syntax error near \
						unexpected token `newline'\n");
				return (2);
			}
		}
		else if (tokens[i].type == TOKEN_PIPE)
		{
			if (i == 0)
				return (printf("yosh1: syntax \
					error near unexpected token `|'\n"), 2);
			else if (!(tokens[i - 1].value) || tokens[i - 1].type != TOKEN_WORD)
				return (printf("yosh1: syntax error near \
					unexpected token `|'\n"), 2);
			else if (!(tokens[i + 1].value)
				|| tokens[i + 1].type != TOKEN_WORD)
				return (printf("yosh1: syntax error \
					near unexpected token `|'\n"), 2);
		}
	}
	return (0);
}

int	main(void)
{
	char				*input;
	t_token				*tokens;
	t_astnode			*ast;
	t_environment		env;
	t_garbage_collector	gc;
	int					status;

	gc_setup(&gc, &env);
	setup_environment();
	while (1)
	{
		gc_clean_list(SECTION_LA);
		setup_parent_signals();
		input = readline("yosh1> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		gc_add(input, SECTION_LA);
		if (check_sequence_complete(input))
		{
			exit(1);
		}
		tokens = lexer(input);
		status = check_syntax(tokens);
		if (!tokens->value || status)
		{
			update_last_pipe(status);
			continue ;
		}
		add_history(input);
		if (expander(&tokens))
			continue ;
		ast = create_node(tokens);
		parser(ast);
		executer(ast);
		gc_clean_paths();
	}
	exit(env.last_pipe);
}

void	bye(void)
{
	rl_clear_history();
	clear_environment();
	gc_cleanup();
}
