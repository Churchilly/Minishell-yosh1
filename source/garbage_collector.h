/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:08:32 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/16 02:41:54 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stddef.h>
# include "enviroment.h"

typedef struct s_gc_node
{
	void				*data;
	struct s_gc_node	*next;
}		t_gc_node;

typedef struct	s_garbage_collector
{
	t_enviroment	*env;
	t_gc_node		*tokens;
	t_gc_node		*lexer;
	t_gc_node		*expander;
	t_gc_node		*asttree;
	t_gc_node		*parser;
	t_gc_node		*executer;
	t_gc_node		*fork;
	t_gc_node		*paths;
}		t_garbage_collector;

void	gc_setup(t_garbage_collector *gc, t_enviroment *env);
void	*gc_add(void *new, t_gc_node **gc_section);
void	*gc_calloc(size_t size, t_gc_node **gc_section);
void	gc_clean_list(t_gc_node **gc_list);
void	gc_exit(int status ,char *msg, t_garbage_collector *gc);
#endif