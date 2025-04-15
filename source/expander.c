/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 05:04:51 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/16 02:39:21 by yusudemi         ###   ########.fr       */
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
t_token	*expand_heredoc(t_token *tokens, t_enviroment *env);

int	have_heredoc(t_token *tokens);
int dollar_in_tokens(t_token *tokens);
int	dollar_in_dquote(char *str);
int	have_quotes(char *str);

static void	quotes(t_token **tokens, t_enviroment *env)
{
	char	*expanded;
	int		i;

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

void	expander(t_token **tokens, t_enviroment *env)
{
	if (have_heredoc(*tokens))
	{
		if (expand_heredoc(*tokens, env))
			return ;
	}
	print_tokens(*tokens);
	if (dollar_in_tokens(*tokens))
	{
		(*tokens) = expand_dollar((*tokens), env);
		if (!(*tokens))
			return ;
	}
	quotes(tokens, env);
}
