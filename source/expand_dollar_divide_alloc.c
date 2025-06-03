/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_divide_alloc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:50:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:08:33 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"
#include "garbage_collector.h"
#include "str.h"
#include <stdlib.h>

int	count_divided(char *s)
{
	int		i;
	int		on_word;
	int		dquote;
	int		quote;

	i = 0;
	on_word = 0;
	dquote = 0;
	quote = 0;
	while (*s)
	{
		if (*s == '\'')
			quote = !quote;
		else if (*s == '\"')
			dquote = !dquote;
		else if (!dquote && !quote && !is_space(*s) && !on_word)
		{
			on_word = 1;
			i++;
		}
		else if (!dquote && !quote && is_space(*s) && on_word)
			on_word = 0;
		s++;
	}
	return (i);
}

static int	get_divided_size(t_token *tokens)
{
	int		ret;
	char	*current;

	ret = 0;
	while (tokens->value)
	{
		current = tokens->value;
		while (is_space(*current))
			current++;
		ret += count_divided(current);
		tokens++;
	}
	return (ret);
}

t_token	*allocate_divided(t_token *tokens)
{
	int		size;
	t_token	*ret;

	size = get_divided_size(tokens);
	ret = (t_token *)gc_calloc((sizeof(t_token) * (size + 1)), SECTION_LA);
	return (ret);
}
