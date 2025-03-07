/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 05:04:51 by yusudemi          #+#    #+#             */
/*   Updated: 2025/03/07 04:04:00 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "enviroment.h"
#include "str.h"
#include <stdlib.h>

void print_tokens(t_token *tokens); //for testing purposes
char	*expand_dollar_in_dquote(char *token_value, t_enviroment *env);
t_token	*expand_dollar(t_token *tokens, t_enviroment *env);
char	*expand_quotes(char *token_value);

int dollar_in_token(t_token *tokens)
{
	while (tokens->value)
	{
		if (*(tokens->value) == '$')
			return (1);
		tokens++;
	}
	return (0);
}

int	dollar_in_dquote(char *str)
{
	int	dquote;

	dquote = 0;
	while (*str)
	{
		if (*str == '\"')
			dquote = !dquote;
		else if (dquote && *str == '$')
			return (1);
		str++;
	}
	return (0);
}
int	have_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			return (1);
		str++;
	}
	return (0);
}
void	expander(t_token **tokens, t_enviroment *env)
{
	char	*expanded;
	int		i;
	if (dollar_in_token(*tokens))
	{
		(*tokens) = expand_dollar((*tokens), env);
		if (!(*tokens))
			return ;
	}
	i = -1;
	while (((*tokens)[++i].value))
	{
		if (dollar_in_dquote((*tokens)[i].value))
			expanded = expand_dollar_in_dquote((*tokens)[i].value, env);
		else if (have_quotes((*tokens)[i].value)) // 'abc' -> abc
			expanded = expand_quotes((*tokens)[i].value);
		else
			continue;
		if (!expanded)
			return ;
		free((*tokens)[i].value);
		(*tokens)[i].value = expanded;
	}
}
