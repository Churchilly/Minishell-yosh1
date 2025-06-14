/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:28:21 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 15:18:41 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

void	executer(t_astnode *root);
void	execute_pipe(t_astnode *node);
void	execute_redirection(t_astnode *node);
void	execute_command(t_astnode *node);
int		setup_child_signals(void);
char	*search_executable_path(char *file_path);
void	update_execute(char *path);

#endif