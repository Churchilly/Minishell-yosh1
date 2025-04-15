/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_clear.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:02:35 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/16 02:53:56 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int		ft_strlen(char const *s);

void	gc_clean_list(t_gc_node **gc_list)
{
	t_gc_node	*curr;
	t_gc_node	*next;
	
	printf("gc::%p\n", (*gc_list));
	curr = *gc_list;
	while (curr)
	{
		next = curr->next;
		free(curr->data);
		curr->data = NULL;
		free(curr);
		curr = next;
	}
	*gc_list = NULL;
}

void	gc_clean_paths(t_gc_node **gc_list)
{
	t_gc_node	*curr;
	t_gc_node	*next;
	char		*path;
	
	curr = *gc_list;
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
	*gc_list = NULL;
}

static void	gc_cleanup(t_garbage_collector *gc)
{
	if (!gc)
		return ;
	if (gc->env)
	{
		clear_enviroment(gc->env);
		write(1, "#env cleared#\n", 15);
	}
	if (gc->tokens)
	{
		gc_clean_list(&gc->tokens);
		write(1, "#tokens cleared#\n", 18);
	}
	if (gc->lexer)
	{
		gc_clean_list(&gc->lexer);
		write(1, "lexer cleared\n", 15);
	}
	if (gc->expander)
	{
		gc_clean_list(&gc->expander);
		write(1, "expander cleared\n", 18);
	}
	if (gc->asttree)
	{
		gc_clean_list(&gc->asttree);
		write(1, "asttree cleared\n", 17);
	}
	if (gc->parser)
	{
		gc_clean_list(&gc->parser);
		write(1, "parser cleared\n", 16);
	}
	if (gc->executer)
	{
		gc_clean_list(&gc->executer);
		write(1, "executer cleared\n", 18);
	}
	if (gc->fork)
	{
		gc_clean_list(&gc->fork);
		write(1, "fork cleared\n", 14);
	}
	if (gc->paths)
	{
		gc_clean_paths(&gc->paths);
		write(1, "paths cleared\n", 15);
	}
}

void	gc_exit(int status ,char *msg, t_garbage_collector *gc)
{
	rl_clear_history();
	write(1, "CLEANUP START\n", 15);
	gc_cleanup(gc);
	write(1, "CLEANUP END\n", 13);
	if (msg)
		write(1, msg, ft_strlen(msg));
	exit(status);
}