/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:39:01 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:41:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include "environment.h"
#include "str.h"
#include <stdlib.h>
#include "heredoc.h"

void	insert_heredoc_variable(char *input, char **buffer, int i)
{
	char	*key;
	char	*var;

	key = crop_variable(input);
	var = get_variable(key);
	buffer[i] = var;
}

char	**get_variables(char *input)
{
	char	**buffer;
	int		size;
	int		i;

	size = count_variables(input);
	buffer = (char **)gc_calloc(sizeof(char *)
			* (size + 1), SECTION_LA);
	i = -1;
	while (*input)
	{
		if (*input == '$')
		{
			input++;
			insert_heredoc_variable(input, buffer, ++i);
			while (is_env_char(*input))
				input++;
		}
		else
			input++;
	}
	return (buffer);
}

int	get_new_len(char *input, char **buffer)
{
	int	i;

	i = 0;
	while (*input)
	{
		if (*input == '$')
		{
			input++;
			i += ft_strlen(*buffer);
			while (is_env_char(*input))
				input++;
			buffer++;
		}
		else
		{
			i++;
			input++;
		}
	}
	return (i);
}

void	insert_variables(char *input, char **buffer, char *new)
{
	int	i;
	int	j;

	i = 0;
	while (*input)
	{
		if (*input == '$')
		{
			j = 0;
			input++;
			while (buffer[i][j])
			{
				*new = buffer[i][j];
				new++;
				j++;
			}
			while (is_env_char(*input))
				input++;
			i++;
		}
		else
			*new++ = *input++;
	}
}

char	*expand_variables(char *input)
{
	char	**buffer;
	int		len;
	char	*ret;

	buffer = get_variables(input);
	len = get_new_len(input, buffer);
	ret = gc_calloc((sizeof(char) * len) + 1, SECTION_LA);
	insert_variables(input, buffer, ret);
	return (ret);
}
