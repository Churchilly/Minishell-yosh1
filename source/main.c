/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/29 20:17:22 by yusudemi         ###   ########.fr       */
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

volatile int g_signal = 0;
/*
Be careful. This global variable must only store the signal number
and must not provide any additional information or access to data.
Therefore, using "norm" type structures in the global scope is
forbidden.
*/

void	print_tokens(t_token *tokens); // for testing purposes
void	print_env(t_environment *env); // for testing purposes
void	free_tokens(t_token *tokens);
int	setup_parent_signals(void);
void __attribute__((destructor)) bye(void);
void	*pointer_storage(int type, void *ptr);
void	print_asttree(t_astnode *parent);

static int	check_sequence_complete(char *input)
/*
• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).
*/
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
char	*get_exec_path(char	*command);

int main(void)
{
	char				*input;
	t_token 			*tokens;
	t_astnode			*ast;
	t_environment		env;
	t_garbage_collector gc;
	
	gc_setup(&gc, &env);
	setup_environment();
	setup_paths();
	//after this point gc and env does not be sent anywhere
	//but should be obtained from pointer storage
	setup_parent_signals();
	while (1)
	{
		//input = get_input(); // checks if input completed
		input = readline("yosh1> "); // YEAP IT HAS LEAKS THAT WE CANT HANDLE -> https://cboard.cprogramming.com/c-programming/136521-memory-leak-readline.html
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		gc_add(input, SECTION_LA);
		if (check_sequence_complete(input))
		/* err according to subject : • Not interpret
		unclosed quotes or special characters 
		which are not required by the subject 
		such as \ (backslash) or ; (semicolon). */
		{
			exit(1);
		}
		tokens = lexer(input);
		printf("<LEXER TOKENS>\n");
		print_tokens(tokens);
		if (!tokens)
			exit(1);
		if (!tokens->value)
		{
			gc_clean_list(SECTION_LA);
			continue ;
		}
		add_history(input);
		expander(&tokens);
		printf("<EXPANDER TOKENS>\n");
		print_tokens(tokens);// for testing purposes
		ast = create_node(tokens);
		parser(ast); // <- SEG
		printf("parser end\n");
		print_asttree(ast);
		executer(ast);
		gc_clean_paths();
	}
	exit(env.last_pipe);
}

void bye(void)
{
	rl_clear_history();
	write(1, "CLEANUP START\n", 15);
	gc_cleanup();
	write(1, "CLEANUP END\n", 13);
}