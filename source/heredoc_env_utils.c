/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:27:46 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 14:55:49 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <stdlib.h>
#include "environment.h"

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
	while (is_env_char(str[size]))
		size++;
	cropped = (char *)gc_calloc((sizeof(char) * (size + 1)), SECTION_LA);
	ret = cropped;
	while (is_env_char(*str))
	{
		*cropped = *str;
		cropped++;
		str++;
	}
	return (ret);
}
