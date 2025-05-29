/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 09:06:49 by obastug           #+#    #+#             */
/*   Updated: 2025/02/27 00:07:49 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "environment.h"

int		builtin_echo(char **args);
int		builtin_cd(int argc, char **args);
int		builtin_pwd(void);
void	builtin_export(char **args);
void	builtin_unset(char **args);
void	builtin_printenv(void);
int		is_builtin(char *command);
int		execute_builtin(char *command, int argc, char **args);

#endif