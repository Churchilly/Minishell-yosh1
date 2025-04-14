/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/13 19:01:14 by yusudemi         ###   ########.fr       */
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
#include "enviroment.h"

volatile int g_signal = 0;
/*
Be careful. This global variable must only store the signal number
and must not provide any additional information or access to data.
Therefore, using "norm" type structures in the global scope is
forbidden.
*/

void	print_tokens(t_token *tokens); // for testing purposes
void	print_env(t_enviroment *env); // for testing purposes
void	free_tokens(t_token *tokens);
int	setup_parent_signals(void);

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

int main(void)
{
	char			*input;
	t_token 		*tokens;
	t_astnode		*root;
	t_enviroment	env;
	
	ft_bzero(&env, sizeof(t_enviroment));
	setup_enviroment(&env);
	if (setup_paths(&env))
		return (-1);

	while (1)
	{
		setup_parent_signals();
		//input = get_input(); // checks if input completed
		input = readline("yosh1> "); // YEAP IT HAS LEAKS THAT WE CANT HANDLE -> https://cboard.cprogramming.com/c-programming/136521-memory-leak-readline.html
		if (g_signal)
			env.last_pipe = g_signal + 128;
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (check_sequence_complete(input))
		/* err according to subject : • Not interpret
		unclosed quotes or special characters 
		which are not required by the subject 
		such as \ (backslash) or ; (semicolon). */
		{
			free(input);
			exit(1); // clear and exit ofc -- later implement
		}
		tokens = lexer(input);
		printf("<LEXER TOKENS>\n");
		print_tokens(tokens);
		if (!tokens)
			break ;
		if (!tokens->value)
		{
			free(input);
			continue ;
		}
		add_history(input);
		expander(&tokens, &env); /* deletes quotes and dquotes
						and gets env variables */
		printf("<EXPANDER TOKENS>\n");
		print_tokens(tokens);// for testing purposes
		root = init_node(tokens);
		if (!root)
		{
			perror("init_node");
			free(input);
		}
		//parser(root);
		//executer(root, &env);
		//free_asttree(root);
		free(input);
	}
	clear_enviroment(&env);
	rl_clear_history();
	free(input);
	return (env.last_pipe);
}
