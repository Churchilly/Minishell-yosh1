/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:30:07 by obastug           #+#    #+#             */
/*   Updated: 2025/06/01 22:56:47 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"
#include "str.h"

int	tilde_counter(char *string)
{
	int	i;
	int	tilde_count;

	i = 0;
	tilde_count = 0;
	while (string[i])
	{
		if (string[i] == '~')
			tilde_count++;
		i++;
	}
	return (tilde_count);
}

void	write_to_final_token(char *final_token, char *home, t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '~' && i == 0 && (token->value[i + 1] == '/' || token->value[i+1] == '\0'))
			ft_strcpy(final_token + ft_strlen(final_token), home);
		else
			final_token[ft_strlen(final_token)] = token->value[i];
		i++;
	}
	token->value = final_token;
}

void	expand_tilde(t_token *tokens)
{
	int		i;
	char	*home;
	int		tilde_count;
	char	*final_token;

	home = get_variable("HOME");
	if (!home || !*home)
		return ;
	i = 0;
	while (tokens[i].value)
	{
		tilde_count = tilde_counter(tokens[i].value);
		if (!tilde_count)
		{
			i++;
			continue ;
		}
		final_token = gc_calloc((tilde_count * ft_strlen(home) - tilde_count)
				+ ft_strlen(tokens[i].value) + 1, SECTION_LA);
		write_to_final_token(final_token, home, tokens + i);
		i++;
	}
}
