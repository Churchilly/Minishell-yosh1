/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:37:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/30 19:54:48 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "garbage_collector.h"

char	*ft_strjoin_nl(char const *s1, char const *s2)
{
	int	s1_len;
	int	s2_len;
	char	*final_string;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	final_string = gc_calloc(sizeof(char) * (s1_len + s2_len + 2), SECTION_LA);
	ft_memcpy(final_string, s1, s1_len);
	ft_memcpy(final_string + s1_len, s2, s2_len);
	final_string[s1_len + s2_len] = '\n';
	final_string[s1_len + s2_len + 1] = '\0';
	return (final_string);
}


