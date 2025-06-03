/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:05 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 15:20:25 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			free_tokens(t_token *tokens);
int				setup_parent_signals(void);
void 			__attribute__((destructor)) bye(void);
void			*pointer_storage(int type, void *ptr);
char			*get_exec_path(char	*command);
void			*pointer_storage(int type, void *ptr);
void			update_last_pipe(int status);
int				safe_fork(void);
void			*gc_calloc(size_t size, t_section section_name);