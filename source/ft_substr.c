/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:27:19 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/26 12:31:07 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "garbage_collector.h"
char	*ft_strdup(const char *str, t_section section_name);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strlen(char const *s);

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