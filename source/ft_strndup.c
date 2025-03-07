/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:58:18 by yusudemi          #+#    #+#             */
/*   Updated: 2025/03/06 05:29:11 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"

char	*ft_strndup(const char	*str, int len)
{
	int i;
	char	*ret;

	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while(++i < len)
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}
