/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:27:46 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/22 01:54:38 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
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
	cropped = (char *)gc_calloc((sizeof(char) * (size + 1)), SECTION_LA);
	ret = cropped;
	while (is_alpha_numerical(*str))
	{
		*cropped = *str;
		cropped++;
		str++;
	}
	return (ret);
}
