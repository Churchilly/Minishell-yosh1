/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:54:53 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/16 16:11:25 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

int	is_token(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '\n');
}

int	is_sequence(char c)
{
	return (c == '\"' || c == '\'');
}

int	is_space(char c)
{
	return (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32);
}

char	*token_dup(const char *s, int size)
{
	char	*dup;
	int		i;

	dup = gc_calloc(sizeof(char) * (size + 1), SECTION_LA);
	i = 0;
	while (i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
