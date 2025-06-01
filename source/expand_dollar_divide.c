/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_divide.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:46:54 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/01 21:28:05 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"
#include "garbage_collector.h"
#include "str.h"
#include <stdlib.h>

int			is_space(char c);
t_token		*allocate_divided(t_token *tokens);
int			count_divided(char *s);

int	curr_divide_size(char *str)
{
	int	ret;
	int	dquote;
	int	quote;

	ret = 0;
	dquote = 0;
	quote = 0;
	while (is_space(*str))
		str++;
	while (*str)
	{
		if (!quote && *str == '\"')
			dquote = !dquote;
		else if (!dquote && *str == '\'')
			quote = !quote;
		else if (!dquote && !quote && is_space(*str))
			break ;
		else
			ret++;
		str++;
	}
	return (ret);
}

void	insert_divided_token(char *value, int *idx, char *new)
{
	int	dquote;
	int	quote;

	dquote = 0;
	quote = 0;
	while (is_space(value[(*idx)]))
		*idx += 1;
	while (value[(*idx)])
	{
		if (!quote && value[(*idx)] == '\"')
			dquote = !dquote;
		else if (!dquote && value[(*idx)] == '\'')
			quote = !quote;
		else if (!dquote && !quote && is_space(value[(*idx)]))
			break ;
		*new = value[(*idx)];
		new++;
		(*idx) += 1;
	}
}

char	*get_divided_token(char *value, int *idx)
{
	int		size;
	char	*new;

	size = curr_divide_size(value + (*idx));
	new = gc_calloc((sizeof(char) * (size + 1)), SECTION_LA);
	insert_divided_token(value, idx, new);
	return (new);
}

t_token	*divide_tokens(t_token *tokens)
{
	t_token	*new;
	t_token	*ret;
	int		curr_div_size;
	int		i;

	new = allocate_divided(tokens);
	ret = new;
	while (tokens->value)
	{
		curr_div_size = count_divided(tokens->value);
		i = 0;
		while (curr_div_size--)
		{
			new->value = get_divided_token(tokens->value, &i);
			new->type = TOKEN_WORD;
			new++;
		}
		tokens++;
	}
	return (ret);
}
