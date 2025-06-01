/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:56:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/01 21:29:25 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"
#include "str.h"
#include <stdlib.h>

char	*create_new_value(char *token_val);

static int	dollar_in_token(char *token_val)
{
	int		dquote;
	int		quote;

	dquote = 0;
	quote = 0;
	while (*token_val)
	{
		if (*token_val == '\"')
			dquote = !dquote;
		else if (*token_val == '\'')
			quote = !quote;
		else if (*token_val == '$')
			return (1);
		token_val++;
	}
	return (0);
}

void	replace_dollars(t_token *tokens)
{
	while (tokens->value)
	{
		if (dollar_in_token(tokens->value))
			tokens->value = create_new_value(tokens->value);
		tokens++;
	}
}
