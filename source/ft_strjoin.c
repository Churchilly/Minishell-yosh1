/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:15:08 by obastug           #+#    #+#             */
/*   Updated: 2025/04/12 00:32:00 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*final_string;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	final_string = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!final_string)
		return (NULL);
	ft_memcpy(final_string, s1, s1_len);
	ft_memcpy(final_string + s1_len, s2, s2_len);
	final_string[s1_len + s2_len] = '\0';
	return (final_string);
}