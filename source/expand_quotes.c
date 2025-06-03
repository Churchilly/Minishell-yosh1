/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:02:11 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:02:59 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

static int	get_new_size(char *token_val)
{
	int	ret;

	ret = 0;
	while (*token_val)
	{
		if (!is_sequence(*token_val))
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

	len = get_new_size(token_value);
	ret = gc_calloc(sizeof(char) * (len + 1), SECTION_LA);
	i = 0;
	while (*token_value)
	{
		if (!is_sequence(*token_value))
		{
			ret[i] = *token_value;
			i++;
		}
		token_value++;
	}
	return (ret);
}
