/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:53:33 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 15:53:03 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "lexer.h"

char	*new_document(char *eof);
int		count_variables(char *str);
char	*crop_variable(char *str);
char	*expand_variables(char *input);
void	setup_heredoc_child_signals(void);
int		is_quoted(char *str);
int		have_dollar(char *str);
int		strcmp_without_quotes(char *input, char *eof);
int		expand_heredoc(t_token *tokens);
void	read_from_pipe(t_token *tokens, int pipe_fd[2]);
char	*reader(int fd);
#endif
