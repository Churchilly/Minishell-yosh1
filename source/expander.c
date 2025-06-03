/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 05:04:51 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/01 21:54:54 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"
#include "str.h"
#include <stdlib.h>

void	print_tokens(t_token *tokens); //for testing purposes
char	*expand_dollar_in_dquote(char *token_value);
t_token	*expand_dollar(t_token *tokens);
char	*expand_quotes(char *token_value);
t_token	*expand_heredoc(t_token *tokens);
void	expand_tilde(t_token *tokens);
int		have_heredoc(t_token *tokens);
int		dollar_in_tokens(t_token *tokens);
int		dollar_in_dquote(char *str);
int		have_quotes(char *str);
int		tilde_in_tokens(t_token *tokens);

static void	quotes(t_token **tokens)
{
	char	*expanded;
	int		i;

	i = -1;
	while (((*tokens)[++i].value))
	{
		if (dollar_in_dquote((*tokens)[i].value))
			expanded = expand_dollar_in_dquote((*tokens)[i].value);
		else if (have_quotes((*tokens)[i].value))
			expanded = expand_quotes((*tokens)[i].value);
		else
			continue ;
		(*tokens)[i].value = expanded;
	}
}

void	expander(t_token **tokens)
{
	if (have_heredoc(*tokens))
	{
		expand_heredoc(*tokens);
	}
	if (dollar_in_tokens(*tokens))
	{
		(*tokens) = expand_dollar(*tokens);
	}
	if (tilde_in_tokens(*tokens))
	{
		expand_tilde(*tokens);
	}
	quotes(tokens);
}
