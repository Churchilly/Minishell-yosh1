/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:18:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/03/04 23:46:56 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "enviroment.h"
#include "str.h"
#include <stdlib.h>
#include <stdio.h>

// only handles if token have $ sign at the begining
void	print_tokens(t_token *tokens); // testing purposes

static int	count_words(char const *s, char c)
{
	int		i;
	int		on_word;

	i = 0;
	on_word = 0;
	while (*s)
	{
		if (*s != c && !on_word)
		{
			on_word = 1;
			i++;
		}
		else if (*s == c && on_word)
			on_word = 0;
		s++;
	}
	return (i);
}

static int	get_expanded_size(t_token *tokens, t_enviroment *env)
{ // $
	int		ret;

	ret = 0;
	while (tokens->value)
	{
		if (*(tokens->value) == '$')
			ret += count_words(get_variable(env, tokens->value + 1), ' ');
		else
			ret += 1;
		tokens++;
	}
	return (ret);
}

int	insert_new_tokens(t_token **new, char *var, t_enviroment *env)
{ // abc def ge
	char	**vars;
	
	if (*var == '\0')
	{
		(*new)->value = ft_strdup("$");
		(*new)->type = TOKEN_WORD;
		if (!(*new)->value)
			return (1);
		(*new)++;
		return (0);
	}
	vars = ft_split(get_variable(env, var), ' ');
	if (!vars)
		return (1);
	while (*vars)
	{
		(*new)->value = *vars;
		(*new)->type = TOKEN_WORD;
		(*new)++;
		vars++;
	}
	//free(vars); // only free the array pointer bucause we will use arrays inside
	return (0);
}

t_token	*expand_dollar(t_token *tokens, t_enviroment *env)
{
	t_token	*new_tokens;
	t_token	*ret;
	
	new_tokens = (t_token *)malloc(sizeof(t_token) * get_expanded_size(tokens, env));
	if (!new_tokens)
		return (NULL);
	ret = new_tokens;
	while (tokens->value)
	{
		if (*(tokens->value) == '$')
		{
			if (insert_new_tokens(&new_tokens, tokens->value + 1, env))
				return (NULL);
			free(tokens->value);
		}
		else
		{
			new_tokens->value = tokens->value;
			new_tokens->type = tokens->type;
			new_tokens++;
		}
		tokens++;
	}
	new_tokens->value = NULL;
	return (ret);
}
