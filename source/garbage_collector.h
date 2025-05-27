/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:08:32 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/27 18:33:34 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stddef.h>
# include "environment.h"

# ifndef COLLECTOR
#  define COLLECTOR 2
# endif

typedef enum e_section				t_section;
typedef struct s_gc_node			t_gc_node;
typedef struct s_garbage_collector	t_garbage_collector;

enum	e_section
{
	SECTION_ENV,
	SECTION_LA,
	SECTION_PATHS
};

struct s_gc_node
{
	void				*data;
	struct s_gc_node	*next;
};

struct	s_garbage_collector
{
	t_environment	*env;
	t_gc_node		*lexical_analysis;
	t_gc_node		*paths;
	int				in_fork;
};

void	gc_setup(t_garbage_collector *gc, t_environment *env);
void	gc_add(void *new, t_section section_name);
void	*gc_calloc(size_t size, t_section section_name);
void	gc_clean_list(t_section section_name);
void	gc_clean_paths(void);
void	gc_cleanup(void);
#endif