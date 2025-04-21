/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_clear.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:02:35 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/22 00:29:47 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int		ft_strlen(char const *s);
void	**gc_get_section(t_section section);

void	gc_clean_list(t_section section_name)
{
	t_gc_node	*curr;
	t_gc_node	*next;
	t_gc_node	**section;
	
	section = (t_gc_node **)gc_get_section(section_name);
	if (!section)
		return ;
	curr = *section;
	while (curr)
	{
		next = curr->next;
		if (curr->data)
			free(curr->data);
		curr->data = NULL;
		free(curr);
		curr = next;
	}
	*section = NULL;
}

void	gc_clean_paths()
{
	t_gc_node	*curr;
	t_gc_node	*next;
	char		*path;
	t_gc_node	**section;
	
	section = (t_gc_node **)gc_get_section(SECTION_PATHS);
	if (!section)
		return ;
	curr = *section;
	while (curr)
	{
		path = curr->data;
		next = curr->next;
		if (unlink(path) == -1)
		{
			write(2, "Failed to delete temp file\n", 28);
			free(path);
			exit (1);
		}
		free(path);
		curr->data = NULL;
		free(curr);
		curr = next;
	}
	*section = NULL;
}

void	gc_cleanup()
{
	clear_enviroment();
	write(1, "#env cleared#\n", 15);
	gc_clean_list(SECTION_LA);
	write(1, "lexical analysis cleared\n", 26);
	//gc_clean_list(&gc->asttree);
	//write(1, "asttree cleared\n", 17);
	//gc_clean_list(&gc->parser);
	//write(1, "parser cleared\n", 16);
	//gc_clean_list(&gc->executer);
	//write(1, "executer cleared\n", 18);
	gc_clean_list(SECTION_FORK);
	write(1, "fork cleared\n", 14);
	gc_clean_paths();
	write(1, "paths cleared\n", 15);
}
