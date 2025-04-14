/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 01:23:52 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/12 03:47:21 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "str.h"

char	*ft_itoa(int n);

static char	*find_path(char *path)
{
	static int	i = 0;
	char		*numeric;
	char		*full;
	
	numeric = ft_itoa(i);
	if (!numeric)
		return (NULL);
	full = ft_strjoin(path, numeric);
	if (!full)
		return (NULL);
	if (access(full, F_OK) == -1)
	{
		free(path);
		free(numeric);
		free(full);
		return (NULL);
	}
	i++;
	free(path);
	free(numeric);
	return (full);
}

int	delete_temp_files(void)
{
	char	*path;

	path = ft_strdup("/tmp/yosh_heredoc_temp_");
	if (!path)
		return (1); 
	while (42)
	{
		path = find_path(path);
		if (!path)
			break ;
		if (unlink(path) == -1)
		{
			write(2, "Failed to delete temp file\n", 28);
			free(path);
			return (1);
		}
	}
	free(path);
	return (0);
}