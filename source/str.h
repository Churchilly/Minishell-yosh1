/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:23:23 by obastug           #+#    #+#             */
/*   Updated: 2025/02/26 13:05:35 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stddef.h>
# include "garbage_collector.h"

char	*ft_strjoin(char const *s1, char const *s2, t_section sec);
char	**ft_split(char const *s, char c, t_section sec);
char	*ft_strdup(const char *str, t_section sec);
char	*ft_strndup(const char	*str, int len, t_section sec);
char	*ft_itoa(int n, t_section sec);
int		ft_strcmp(char *str1, char *str2);
int		ft_strlen(char const *s);
void	ft_putchar(char c);
void	ft_bzero(void *addr, int size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	free_str_list(char **str);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *str1, char *str2);

#endif