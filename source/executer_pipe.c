/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:40:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/31 19:21:34 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int		safe_fork(void);
void	execute_command(t_astnode *node);
void	execute_pipe(t_astnode *node);

void	execute_pipe(t_astnode *node)
{
    int		pipedes[2];
    pid_t	left_pid, right_pid;
    int		status;

    if (!node || node->type != NODE_PIPE)
    {
        execute_command(node);
        return ;
    }
    
    if (pipe(pipedes) == -1)
    {
        printf("pipe() failed: %d.\n", errno);
        exit(1);
    }

    // Fork for left side (writes to pipe)
    left_pid = safe_fork();
    if (left_pid == 0)
    {
        close(pipedes[0]); // Close read end
        dup2(pipedes[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipedes[1]);
        
        // Execute left side (could be another pipe or command)
        if (node->left->type == NODE_PIPE)
            execute_pipe(node->left);
        else
            execute_command(node->left);
        exit(0);
    }

    // Fork for right side (reads from pipe)
    right_pid = safe_fork();
    if (right_pid == 0)
    {
        close(pipedes[1]); // Close write end
        dup2(pipedes[0], STDIN_FILENO); // Redirect stdin from pipe
        close(pipedes[0]);
        
        // Execute right side (could be another pipe or command)  
        if (node->right->type == NODE_PIPE)
            execute_pipe(node->right);
        else
            execute_command(node->right);
        exit(0);
    }

    // Parent process - close both ends and wait
    close(pipedes[0]);
    close(pipedes[1]);
    
    waitpid(left_pid, &status, 0);
    waitpid(right_pid, &status, 0);
}
