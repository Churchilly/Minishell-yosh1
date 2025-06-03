/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:27:19 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 14:59:56 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "garbage_collector.h"
#include "str.h"

char	*ft_substr(char const *s, unsigned int start, size_t len,
		t_section section)
{
	char	*sub;

	if (!s || start >= (unsigned int)ft_strlen(s))
		return (ft_strdup("", section));
	if (len > (unsigned int)ft_strlen(s + start))
		len = (unsigned int)ft_strlen(s + start);
	sub = gc_calloc((len + 1) * sizeof(char), section);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}