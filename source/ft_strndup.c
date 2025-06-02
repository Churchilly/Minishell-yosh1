/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:58:18 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/21 21:37:46 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"
#include "garbage_collector.h"

char	*ft_strndup(const char	*str, int len, t_section section)
{
	int		i;
	char	*ret;

	ret = gc_calloc(sizeof(char) * (len + 1), section);
	i = -1;
	while (++i < len)
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}
