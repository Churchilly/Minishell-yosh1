/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:56:04 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:28:41 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_sequence_complete(char *input)
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

static void	print_redirection_syntax_error(t_token_type type)
{
	if (type == TOKEN_DGREAT)
		printf("yosh1: syntax error near unexpected token `>>'\n");
	else if (type == TOKEN_GREAT && type != TOKEN_LESS)
		printf("yosh1: syntax error near unexpected token `>'\n");
	else if (type == TOKEN_DLESS)
		printf("yosh1: syntax error near unexpected token `<<'\n");
	else if (type == TOKEN_LESS)
		printf("yosh1: syntax error near unexpected token `<'\n");
	else if (type == TOKEN_PIPE)
		printf("yosh1: syntax error near unexpected token `|'\n");
	else
		printf("yosh1: syntax error near unexpected token `newline'\n");
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
				return (print_redirection_syntax_error(tokens[i + 1].type), 2);
		}
		else if (tokens[i].type == TOKEN_PIPE)
		{
			if (i == 0)
				return (printf("yosh1: syntax error \
near unexpected token `|'\n"), 2);
			else if (!(tokens[i - 1].value) || tokens[i - 1].type != TOKEN_WORD)
				return (printf("yosh1: syntax error \
near unexpected token `|'\n"), 2);
			else if (!(tokens[i + 1].value) || tokens[i + 1].type != TOKEN_WORD)
				return (printf("yosh1: syntax error \
near unexpected token `|'\n"), 2);
		}
	}
	return (0);
}
