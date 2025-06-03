/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:04:04 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 14:37:52 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "garbage_collector.h"

char	*ft_strdup(const char *str, t_section section_name)
{
	int		len;
	int		i;
	char	*ret;

	if (!str)
	{
		return (gc_calloc(sizeof(char) * 1, section_name));
	}
	len = 0;
	while (str[len])
		len++;
	ret = gc_calloc(sizeof(char) * (len + 1), section_name);
	i = -1;
	while (++i < len)
		ret[i] = str[i];
	return (ret);
}
