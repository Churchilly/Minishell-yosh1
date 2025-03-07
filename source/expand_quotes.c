/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:02:11 by yusudemi          #+#    #+#             */
/*   Updated: 2025/03/07 04:20:01 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	is_sequence(char c);

static int	get_new_size(char *token_val)
{
	int ret;

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

	len =  get_new_size(token_value);
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
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
	ret[len] = '\0';
	return (ret);
}