/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:25:49 by obastug           #+#    #+#             */
/*   Updated: 2025/04/11 16:01:57 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_bzero(void *addr, int size)
{
	char	*bytes;
	int		i;

	bytes = addr;
	i = 0;
	while (i < size)
		bytes[i++] = '\0';
	return ;
}

int	ft_strcmp(char *str1, char *str2)
{
	if (!str1)
		return (0);
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	if ((!(*str2) && *str1) || (!(*str1) && *str2))
		return (0);
	return (1);
}

int	ft_strlen(char const *s)
{
	int	i;
	
	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	ptr1 = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	return (ptr1);
}
