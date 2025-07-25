/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:42:49 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:07:08 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "garbage_collector.h"
#include "lexer.h"
#include "str.h"
#include <stdlib.h>

static char	*crop_key(char *str)
{
	char	*ret;
	char	*cropped;
	int		len;

	len = 0;
	if (*str == '?')
		return (ft_strdup("?", SECTION_LA));
	while (str[len] && is_env_char(*str))
		len++;
	cropped = gc_calloc(sizeof(char *) * (len + 1), SECTION_LA);
	ret = cropped;
	while (*str && is_env_char(*str))
	{
		*cropped = *str;
		cropped++;
		str++;
	}
	return (ret);
}

static char	*create_variable(char *token_val)
{
	char	*cropped;
	char	*ret;

	cropped = crop_key(token_val);
	ret = get_variable(cropped);
	return (ret);
}

static void	insert_dollar_variable(char **val, char **new)
{
	char	*var;

	(*val)++;
	var = create_variable(*val);
	while (*var)
	{
		**new = *var;
		(*new)++;
		var++;
	}
	if (**val && **val == '?')
	{
		(*val)++;
		return ;
	}
	while (**val && is_env_char(**val))
		(*val)++;
}

static int	get_new_value_size(char *val)
{
	int		ret;
	char	*var;

	ret = 0;
	while (*val)
	{
		if (*val == '$')
		{
			val++;
			var = create_variable(val);
			ret += ft_strlen(var);
			while (*val && is_env_char(*val))
				val++;
		}
		else
		{
			ret++;
			val++;
		}
	}
	return (ret);
}

char	*create_new_value(char *token_val)
{
	char	*new;
	char	*ret;
	int		size;

	size = get_new_value_size(token_val);
	new = gc_calloc((sizeof(char) * (size + 1)), SECTION_LA);
	ret = new;
	while (*token_val)
	{
		if (*token_val == '$')
			insert_dollar_variable(&token_val, &new);
		else
			*new++ = *token_val++;
	}
	return (ret);
}
