/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:31:39 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 14:31:51 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# ifndef ENVIRONMENT
#  define ENVIRONMENT 1
# endif

/* EXPORT LOCK (if export lock = 1 dont export var)
in shell environment not all
environment varables exported to child processes.
*Commonly Exported Variables
	**PATH: Specifies the directories in which executable programs are located.
	**HOME: The home directory of the current user.
	**USER: The name of the current user.
	**SHELL: The path to the current user's shell.
	**PWD: The current working directory.
	**OLDPWD: The previous working directory.
	**LANG: The current locale.
	**TERM: The type of terminal to emulate.
*Variables Typically Not Exported
	**Internal Shell Variables: Variables used internally by the shell
	that do not need to be available to child processes.
	**Temporary Variables: Variables that are only needed for the duration
	of the current shell session or script.
We only use EXPORTED VALUES in minishell!!
*/
typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}		t_node;

typedef struct s_environment
{
	int				last_pipe;
	struct s_node	*top;
	struct s_node	*bottom;
}		t_environment;

void	setup_environment(void);
char	*get_cwd(void);
char	*get_variable(char *key);
t_node	*find_variable(char *key);
void	delete_variable(char *key);
int		revalue_variable(char *key, char *value);
void	update_last_pipe(int status);
void	add_variable(char *key, char *value);
char	*create_env_value(char *str);
void	clear_environment(void);

#endif
