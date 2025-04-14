/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:56:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/15 00:00:09 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "enviroment.h"
#include "str.h"
#include <stdlib.h>

char	*create_new_value(char *token_val, t_enviroment *env);

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

int	replace_dollars(t_token *tokens, t_enviroment *env)
{
	char	*tmp;
	
	while (tokens->value)
	{
		if (dollar_in_token(tokens->value))
		{
			tmp = create_new_value(tokens->value, env);
			if (!tmp)
				return (1);
			free(tokens->value);
			tokens->value = tmp;
		}
		tokens++;
	}
	return (0);
}