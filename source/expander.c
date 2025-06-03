/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 05:04:51 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:05:10 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"
#include "str.h"
#include <stdlib.h>
#include "heredoc.h"
#include "expander.h"

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
