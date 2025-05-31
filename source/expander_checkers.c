/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_checkers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 05:11:54 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/31 21:06:58 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_isspace(char c);

int	have_heredoc(t_token *tokens)
{
	while (tokens->value)
	{
		if (tokens->type == TOKEN_DLESS)
			return (1);
		tokens++;
	}
	return (0);
}

int dollar_in_tokens(t_token *tokens)
{
	int	dquote;
	int	quote;
	char	*current;
	
	dquote = 0;
	quote = 0;
	while (tokens->value)
	{
		current = tokens->value;
		while (*current)
		{
			if (*(current) == '\"')
				dquote = !dquote;
			else if (*(current) == '\'')
				quote = !quote;
			else if (!dquote && !quote && *(current) == '$')
				return (1);
			(current)++;
		}
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

int	tilde_in_tokens(t_token *tokens)
{
    int	dquote;
    int	quote;
    char	*current;
    
    dquote = 0;
    quote = 0;
    while (tokens->value)
    {
        current = tokens->value;
        while (*current)
        {
            if (*(current) == '\"')
                dquote = !dquote;
            else if (*(current) == '\'')
                quote = !quote;
            else if (!dquote && !quote && *(current) == '~' &&
				(*(current + 1) == '/' || ft_isspace(*(current + 1)) || *(current + 1) == '\0')
			&& (ft_isspace(*(current - 1)) || *(current - 1) == '\0'))
                return (1);
            (current)++;
        }
        tokens++;
    }
    return (0);
}
