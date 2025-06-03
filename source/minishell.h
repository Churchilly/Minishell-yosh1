/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:05 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 15:52:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"

void	free_tokens(t_token *tokens);
int		setup_parent_signals(void);
void	bye(void) __attribute__((destructor));
void	*pointer_storage(int type, void *ptr);
char	*get_exec_path(char	*command);
void	*pointer_storage(int type, void *ptr);
void	update_last_pipe(int status);
int		safe_fork(void);
void	safe_open(int *fd, int *red, const char *__file, int __oflag);
void	*gc_calloc(size_t size, t_section section_name);
int		check_syntax(t_token *tokens);
int		check_sequence_complete(char *input);
#endif