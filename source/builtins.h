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

int		pwd(char **args);
void	ft_export(char	**args);
void	unset(char	**args);
int		echo(char	**args);
int		cd(int argc, char	**args);
void	unset(char	**args);
void	printenv(char	**args);

#endif