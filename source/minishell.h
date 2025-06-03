/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:05 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 14:42:14 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_tokens(t_token *tokens);
int		setup_parent_signals(void);
void 	__attribute__((destructor)) bye(void);
void	*pointer_storage(int type, void *ptr);
char	*get_exec_path(char	*command);