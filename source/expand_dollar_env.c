/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:42:49 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/15 00:00:03 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "lexer.h"
#include "str.h"
#include <stdlib.h>

static char	*crop_key(char *str)
{
	char	*ret;
	char	*cropped;
	int		len;

	len = 0;
	while (str[len] && str[len] != '$' && str[len] != '\"' && str[len] != '\'')
		len++;
	cropped = malloc((sizeof(char *) * len) + 1);
	if (!cropped)
		return (NULL);
	cropped[len] = '\0';
	ret = cropped;
	while (*str && *str != '$' && *str != '\"' && *str != '\'')
	{
		*cropped = *str;
		cropped++;
		str++;
	}
	return (ret);
}

static char	*create_variable(char *token_val, t_enviroment *env)
{
	char	*cropped;
	char	*ret;

	cropped = crop_key(token_val);
	if (!cropped)
		return (NULL);
	ret = get_variable(env, cropped);
	if (!ret)
		return (NULL);
	return (ret);
}



static int	insert_dollar_variable(char **val, char **new, t_enviroment *env)
{
	char	*var;
	
	(*val)++;
	var = create_variable(*val, env);
	if (!var)
		return (1);
	while (*var)
	{
		**new = *var;
		(*new)++;
		var++;
	}
	**new = '\0';
	while (**val && **val != '$' && **val != '\"' && **val != '\'')
		(*val)++;
	return (0);
}

static int	get_new_value_size(char *val, t_enviroment *env)
{
	int		ret;
	char	*var;

	ret = 0;
	while (*val)
	{
		if (*val == '$')
		{
			val++;
			var = create_variable(val, env);
			if (!var)
				return (-1);
			ret += ft_strlen(var);
			free(var);
			while (*val && *val != '$' && *val != '\"' && *val != '\'')
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

char	*create_new_value(char *token_val, t_enviroment *env)
{
	char	*new;
	char	*ret;
	int		size;

	size = get_new_value_size(token_val, env);
	if (size == -1)
		return (NULL);
	new = malloc((sizeof(char) * size) + 1);
	if (!new)
		return (NULL);
	ret = new;
	while (*token_val)
	{
		if (*token_val == '$')
		{
			if (insert_dollar_variable(&token_val, &new, env))
				return (NULL);
		}
		else
			*new++ = *token_val++;
	}
	return (ret);
}