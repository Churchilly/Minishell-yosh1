/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_in_dquote_env.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 03:56:25 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:04:49 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "garbage_collector.h"
#include <stdlib.h>
#include "str.h"
#include "lexer.h"

static char	*get_dollar(char *token_value)
{
	char	*ret;
	char	*trim;
	int		i;

	i = 0;
	if (*(token_value + 1) == '?')
		return (get_variable("?"));
	if (!token_value[i + 1] || !is_env_char(token_value[i + 1]))
		return (ft_strdup("$", SECTION_LA));
	while (token_value[i + 1] && is_env_char(token_value[i + 1]))
		i++;
	trim = ft_strndup(token_value + 1, i, SECTION_LA);
	ret = get_variable(trim);
	return (ret);
}

void	pass_env_var(char **token_val, char ***env_vars)
{
	(*token_val)++;
	if (**token_val == '?')
		(*token_val)++;
	while (**token_val && is_env_char(**token_val))
	{
		(*token_val)++;
	}
	(*env_vars)++;
}

void	get_env_vars(char *token_value, char **env_vars)
{
	int	dquote;

	dquote = 0;
	while (*token_value)
	{
		if (dquote && *token_value == '$')
		{
			*env_vars = get_dollar(token_value);
			pass_env_var(&token_value, &env_vars);
		}
		else
		{
			if (*token_value == '\"')
				dquote = !dquote;
			token_value++;
		}
	}
}
