/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:07:37 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/16 02:29:03 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <stdlib.h>

void	ft_bzero(void *addr, int size);

void	gc_setup(t_garbage_collector *gc, t_enviroment *env)
{
	ft_bzero(gc, sizeof(t_garbage_collector));
	gc->env = env;
}

void	*gc_add(void *new, t_gc_node **gc_section)
{
	t_gc_node	*new_gc_node;
	
	new_gc_node = (t_gc_node *)malloc(sizeof(t_gc_node));
	if (!new_gc_node)
		return (NULL);
	new_gc_node->data = new;
	new_gc_node->next = *gc_section;
	*gc_section = new_gc_node;
	return (new);
}

void	*gc_calloc(size_t size, t_gc_node **gc_section)
{
	void			*new;
	unsigned char	*p;
	
	new = malloc(size);
	if (!new)
		return (NULL);
	p = new;
	while (size--)
		*p++ = '\0';
	if (!gc_add(new, gc_section))
		return (NULL);
	return (new);
}


