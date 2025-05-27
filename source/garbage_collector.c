/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:07:37 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/27 18:29:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

void	ft_bzero(void *addr, int size);
void	*pointer_storage(int type, void *ptr);

void	**gc_get_section(t_section section)
{
	t_garbage_collector	*gc;

	gc = pointer_storage(COLLECTOR, NULL);
	if (!gc)
		return (NULL);
	if (section == SECTION_ENV)
		return ((void **)&gc->env);
	if (section == SECTION_LA)
		return ((void **)&gc->lexical_analysis);
	if (section == SECTION_PATHS && !(gc->in_fork))
		return ((void **)&gc->paths);
	return (NULL);
}

void	gc_setup(t_garbage_collector *gc, t_environment *env)
{
	ft_bzero(gc, sizeof(t_garbage_collector));
	ft_bzero(env, sizeof(t_environment));
	gc->env = env;
	pointer_storage(ENVIRONMENT, env);
	pointer_storage(COLLECTOR, gc);
}

void	gc_add(void *new, t_section section_name)
{
	t_gc_node	*new_gc_node;
	t_gc_node	**section;

	if (!new)
		return ;
	new_gc_node = (t_gc_node *)malloc(sizeof(t_gc_node));
	if (!new_gc_node)
	{
		printf("malloc() failed: %d\n", errno);
		exit(1);
	}
	section = (t_gc_node **)gc_get_section(section_name);
	new_gc_node->data = new;
	new_gc_node->next = *section;
	*section = new_gc_node;
}

void	*gc_calloc(size_t size, t_section section_name)
{
	void	*new;

	new = malloc(size);
	if (!new)
	{
		printf("malloc() failed: %d\n", errno);
		exit(1);
	}
	ft_bzero(new, size);
	gc_add(new, section_name);
	return (new);
}
