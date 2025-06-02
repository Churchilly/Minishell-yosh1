/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:29:30 by obastug           #+#    #+#             */
/*   Updated: 2025/06/02 19:30:22 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

int	main_helper(char *input, t_token *tokens, t_astnode *ast)
{
	int	status;

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
		return (1);
	}
	add_history(input);
	if (expander(&tokens))
		return (1);
	ast = create_node(tokens);
	parser(ast);
	executer(ast);
	return (0);
}

int	check_syntax_helper(t_token *tokens, int i)
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
	else
		return (1);
}
