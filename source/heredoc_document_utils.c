/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_document_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 00:16:20 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/13 20:39:33 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_quoted(char *str)
{
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			return (1);
		str++;
	}
	return (0);
}

int	have_dollar(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}
#include <stdio.h>
int	strcmp_without_quotes(char *input, char *eof)
{
	if (!(*input))
		return (0);
	while (*input && *eof)
	{
		if (*eof == '\"' || *eof == '\'')
		{
			eof++;
			continue;
		}
		if (*eof != *input)
			return (0);
		eof++;
		input++;
	}
	return (1);
}