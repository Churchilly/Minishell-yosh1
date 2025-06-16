/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:02:11 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/16 17:10:17 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

static int	get_new_size(char *token_val)
{
	int	ret;
	int	quote;
	int	dquote;

	ret = 0;
	quote = 0;
	dquote = 0;
	while (*token_val)
	{
		if (!quote && *token_val == '\"')
		{
			dquote = !dquote;
			token_val++;
			continue ;
		}
		if (!dquote && *token_val == '\'')
		{
			quote = !quote;
			token_val++;
			continue ;
		}
		ret++;
		token_val++;
	}
	return (ret);
}

char	*expand_quotes(char *token_value)
{
	char	*ret;
	int		i;
	int		len;
	int		quote;
	int		dquote;

	quote = 0;
	dquote = 0;
	len = get_new_size(token_value);
	ret = gc_calloc(sizeof(char) * (len + 1), SECTION_LA);
	i = 0;
	while (*token_value)
	{
		if (!quote && *token_value == '\"')
			dquote = !dquote;
		else if (!dquote && *token_value == '\'')
			quote = !quote;
		else
			ret[i++] = *token_value;
		token_value++;
	}
	return (ret);
}
