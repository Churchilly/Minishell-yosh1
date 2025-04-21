/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 06:08:59 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/21 17:00:10 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_VARIABLES_H
# define ENVIROMENT_VARIABLES_H

# ifndef ENVIROMENT
#  define ENVIROMENT 1
# endif

typedef struct s_node
{
	char	*key;
	char	*value;
	/* EXPORT LOCK (if export lock = 1 dont export var)
	in shell enviroment not all
	enviroment varables exported to child processes.
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
	struct s_node	*next;
}		t_node;

typedef struct s_enviroment
{
	int				last_pipe;
	struct	s_node	*top;
	struct	s_node	*bottom;
}		t_enviroment;

void	setup_enviroment(void);
void	setup_paths(void);
char	*get_cwd();
char	*get_variable(char *key);
t_node	*find_variable(char *key);
void	delete_variable(char *key);
int		revalue_variable(char *key, char *value);
void	add_variable(char *key, char *value);
void 	clear_enviroment(void);

#endif