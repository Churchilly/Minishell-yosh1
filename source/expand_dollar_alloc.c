/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 05:40:55 by yusudemi          #+#    #+#             */
/*   Updated: 2025/03/08 06:02:42 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "enviroment.h"
#include <stdlib.h>

static int	count_words(char *s, char c)
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
	char	*tmp;

	ret = 0;
	while (tokens->value)
	{
		if (*(tokens->value) == '$')
		{
			tmp = get_variable(env, tokens->value + 1);
			if (!tmp)
				return (-1); //malloc err
			ret += count_words(tmp, ' ');
			free(tmp);
		}
		else
			ret += 1;
		tokens++;
	}
	return (ret);
}

t_token	*allocate_new_tokens(t_token *tokens, t_enviroment *env)
{
	int	size;
	t_token	*new;

	size = get_expanded_size(tokens, env) + 1;
	if (size == -1)
		return (NULL);
	new = (t_token *)malloc(sizeof(t_token) * size);
	if (!new)
		return (NULL);
	return (new);
}
