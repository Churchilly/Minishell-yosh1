/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:39:01 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/14 20:06:32 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "str.h"
#include <stdlib.h>

int	is_alpha_numerical(char c);
int	count_variables(char *str);
char	*crop_variable(char *str);
char	**alloc_buffer(char *input);
void	free_buffer(char **buffer);

int	insert_heredoc_variable(char *input, char **buffer, t_enviroment *env, int i)
{
	char	*key;
	char	*var;
	
	key = crop_variable(input);
	if (!key)
		return (1);
	var = get_variable(env, key);
	free(key);
	if (!var)
		return (1);
	buffer[i] = var;
	return (0);
}

char	**get_variables(char *input, t_enviroment *env)
{
	char	**buffer;
	int		i;
	
	buffer = alloc_buffer(input);
	if (!buffer)
		return (NULL);
	i = -1;
	while (*input)
	{
		if (*input == '$')
		{
			input++;
			if (insert_heredoc_variable(input, buffer, env, ++i))
				return (NULL);
			while (is_alpha_numerical(*input))
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
			while (is_alpha_numerical(*input))
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
	int j;

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
			while (is_alpha_numerical(*input))
				input++;
			i++;
		}
		else
			*new++ = *input++;
	}
}

char	*expand_variables(char *input, t_enviroment *env)
{
	char	**buffer;
	int		len;
	char	*ret;
	
	buffer = get_variables(input, env);
	if (!buffer)
		return (NULL);
	len = get_new_len(input, buffer);
	ret = malloc((sizeof(char) * len) + 1);
	ret[len] = '\0';
	if (!ret)
		return (free_buffer(buffer), NULL);
	insert_variables(input, buffer, ret);
	free_buffer(buffer);
	return (ret);
}
