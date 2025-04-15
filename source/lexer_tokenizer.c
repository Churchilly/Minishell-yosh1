/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:54:57 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/16 02:13:25 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stddef.h>
#include <unistd.h>

int	is_token(char c);
int	is_sequence(char c);
int	is_space(char c);
char	*token_dup(const char *s, int size, t_garbage_collector *gc);
int	ft_strcmp(char *str1, char *str2);

static void	pass_sequence(char token, char	**str)
{
	(*str)++;
	while ((**str) != token)
		(*str)++;
	if (is_sequence(*((*str) + 1)))
	{
		(*str)++;
		pass_sequence(*((*str)), str);
	}
}

static void pass_token(char token, char **str)
{
	if (token == '>' || token == '<')
	{
		if ((*((*str)+1)) == token)
			(*str)++;
	}
	else if (token == '$')
	{
		while (*((*str) + 1) && *((*str) + 1) != ' ' &&
			!is_token(*((*str) + 1)) && !is_sequence(*((*str) + 1))) 
			(*str)++;
	}
}

int	count_tokens(char *str)
{
	int	is_compound;
	int	count;
	
	count = 0;
	is_compound = 0;
	while (*str)
	{
		if (is_token(*str))
		{
			pass_token(*str, &str);
			is_compound = 0;
			count++;
		}
		else if (is_space(*str) && is_compound)
			is_compound = 0;
		else if (!is_space(*str) && !is_compound)
		{
			is_compound = 1;
			count++;
		}
		if (is_sequence(*str))
			pass_sequence(*str, &str);
		str++;
	}
	return (count);
}

void	split_tokens(char **tokens, char **str, t_garbage_collector *gc)
{
	char	*p;

	if (is_token(**str))
	{
		p = *str;
		pass_token(**str, str);
		*tokens = token_dup(p, ((*str) + 1) - p, gc);
		(*str)++;
	}
	else if (!is_space(**str))
	{
		p = *str;
		while (**str && !is_token(**str) && !is_space(**str))
		{
			if (is_sequence(**str))
				pass_sequence(**str, str);
			(*str)++;
		}
		*tokens = token_dup(p, (*str) - p, gc);
	}
	else
		(*str)++;
}

void	insert_types(t_token *tokens)
{
	int	i;
	
	i = 0;
	while (tokens[i].value)
	{
		if (ft_strcmp((tokens + i)->value, ">"))
			(tokens + i)->type = TOKEN_GREAT;
		else if (ft_strcmp((tokens + i)->value, "<"))
			(tokens + i)->type = TOKEN_LESS;
		else if (ft_strcmp((tokens + i)->value, ">>"))
			(tokens + i)->type = TOKEN_DGREAT;
		else if (ft_strcmp((tokens + i)->value, "<<"))
			(tokens + i)->type = TOKEN_DLESS;
		else if (ft_strcmp((tokens + i)->value, "|"))
			(tokens + i)->type = TOKEN_PIPE;
		else if (ft_strcmp((tokens + i)->value, "\n"))
			(tokens + i)->type = TOKEN_NEWLINE;
		else
			(tokens + i)->type = TOKEN_WORD;
		i++;
	}
}