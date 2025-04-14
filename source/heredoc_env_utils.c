/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:27:46 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/11 19:59:42 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_alpha_numerical(char c);

int	count_variables(char *str)
{
	int ret;

	ret = 0;
	while (*str)
	{
		if (*str == '$')
			ret++;
		str++;
	}
	return (ret);
}

char	*crop_variable(char *str)
{
	char	*cropped;
	char	*ret;
	int		size;
	
	size = 0;
	while (is_alpha_numerical(str[size]))
		size++;
	cropped = (char *)malloc((sizeof(char) * size) + 1);
	if (!cropped)
		return (NULL);
	ret = cropped;
	while (is_alpha_numerical(*str))
	{
		*cropped = *str;
		cropped++;
		str++;
	}
	ret[size] = '\0';
	return (ret);
}

char	**alloc_buffer(char *input)
{
	int		size;
	char	**ret;

	size = count_variables(input);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = NULL;
	return (ret);
}

void	free_buffer(char **buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}