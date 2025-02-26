/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/02/26 16:15:51 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
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
		if (*input == '\"' && !(quote))
			dquote = !(dquote);
		if (*input == '\'' && !(dquote))
			quote = !(quote);
		input++;
	}
	return (quote || dquote);
}

void free_tokens(t_token *tokens)
{
    int i = 0;
    while (tokens[i].value)
    {
        free(tokens[i].value);
        i++;
    }
    free(tokens);
}


void	print_tokens(t_token *tokens)
{
	int i = 0;
	while (tokens[i].value)
	{
		printf("tokens: [%s]\n", tokens[i].value);
		i++;
	}
	printf("END\n");
}

int main(void)
{
	char		*input;
	t_token 	*tokens;
	t_astnode	*root;
	
	while (1)
	{
		//input = get_input(); // checks if input completed
		input = readline("yosh1> "); // YEAP IT HAS LEAKS THAT WE CANT HANDLE -> https://cboard.cprogramming.com/c-programming/136521-memory-leak-readline.html
		if (!input)
			exit(1);
		if (check_sequence_complete(input))
		/* err according to subject : • Not interpret
		unclosed quotes or special characters 
		which are not required by the subject 
		such as \ (backslash) or ; (semicolon). */
		{
			free(input);
			exit(1); // clear and exit ofc -- later implement
		}
		if (ft_strcmp(input, "exit"))
		{
			break; // exit is also a command so delete this line
		}
		tokens = lexer(input);
		if (!tokens->value)
		{
			free(input);
			continue;
		}
		add_history(input);
		expander(tokens); /* deletes quotes and dquotes
						and gets env variables */
		// print_tokens(tokens); // for testing purposes
		// parser

		root = init_node(tokens);
		if (!root)
		{
			perror("init_node");
			free(input);
		}
		parser(root);
		execute(root);
		free_asttree(root);
		free(input);
	}
	rl_clear_history();
	free(input);
	return (0);
}