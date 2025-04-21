/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:08:32 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/21 20:40:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stddef.h>
# include "enviroment.h"

# ifndef COLLECTOR
#  define COLLECTOR 2
# endif

typedef enum
{
	SECTION_ENV,
	SECTION_LA,
	SECTION_PATHS,
	SECTION_FORK
}	t_section;

typedef struct s_gc_node
{
	void				*data;
	struct s_gc_node	*next;
}		t_gc_node;

typedef struct	s_garbage_collector
{
	t_enviroment	*env;
	t_gc_node		*lexical_analysis;
	t_gc_node		*paths;
	t_gc_node		*asttree;
	t_gc_node		*parser;
	t_gc_node		*executer;
	int				in_fork;
}		t_garbage_collector;

void	gc_setup(t_garbage_collector *gc, t_enviroment *env);
void	gc_add(void *new, t_section section_name);
void	*gc_calloc(size_t size, t_section section_name);
void	gc_clean_list(t_section section_name);
void	gc_clean_paths();
void	gc_cleanup();
#endif