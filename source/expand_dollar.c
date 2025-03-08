/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:18:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/03/08 06:19:30 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "enviroment.h"
#include "str.h"
#include <stdlib.h>

// only handles if token have $ sign at the begining
t_token	*allocate_new_tokens(t_token * tokens, t_enviroment *env);

static int	insert_non_envs(t_token **new, char *var)
{
	if (*var == '\0')
	{
		(*new)->value = ft_strdup("$");
		(*new)->type = TOKEN_WORD;
		if (!(*new)->value)
			return (1);
		(*new)++;
		return (0);
	}
	return (-1);
}

static int	insert_new_tokens(t_token **new, char *var, t_enviroment *env)
{
	char	**vars;
	char	**vars_start;
	int		is_env;
	
	is_env = insert_non_envs(new, var);
	if (is_env >= 0)
		return (is_env);
	var = get_variable(env, var);
	if (!var)
		return (1);
	vars = ft_split(var, ' ');
	free(var);
	if (!vars)
		return (1);
	vars_start = vars;
	while (*vars)
	{
		(*new)->value = *vars;
		(*new)->type = TOKEN_WORD;
		(*new)++;
		vars++;
	}
	free(vars_start);
	return (0);
}

static void	insert_old_tokens(t_token **new, t_token *tokens)
{
	(*new)->value = tokens->value;
	(*new)->type = tokens->type;
	(*new)++;
}

t_token	*expand_dollar(t_token *tokens, t_enviroment *env)
{
	t_token	*new_tokens;
	t_token	*ret;
	int		i;
	
	new_tokens = allocate_new_tokens(tokens, env);
	if (!new_tokens)
		return (NULL);
	i = -1;
	ret = new_tokens;
	while (tokens[++i].value)
	{
		if (*(tokens[i].value) == '$')
		{
			if (insert_new_tokens(&new_tokens, (tokens[i].value + 1), env))
				return (NULL);
			free(tokens[i].value);
		}
		else
			insert_old_tokens(&new_tokens, tokens + i);
	}
	free(tokens);
	new_tokens->value = NULL;
	return (ret);
}
