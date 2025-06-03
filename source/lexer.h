/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:03:49 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 15:43:30 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "garbage_collector.h"
# include "environment.h"

typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;

enum e_token_type
{
	TOKEN_WORD,
	TOKEN_ASSIGNMENT_WORD,
	TOKEN_NAME,
	TOKEN_NEWLINE,
	TOKEN_IO_NUMBER,
	TOKEN_GREAT,
	TOKEN_LESS,
	TOKEN_DLESS,
	TOKEN_DGREAT,
	TOKEN_PIPE,
	TOKEN_SKIP,
	TOKEN_EON,
	TOKEN_EOF,
	TOKEN_ERROR
};

struct	s_token
{
	t_token_type	type;
	char			*value;
};

int		is_space(char c);
int		is_token(char c);
int		is_sequence(char c);
t_token	*lexer(char *input);
int		count_tokens(char *str);
void	split_tokens(char **tokens, char **str);
void	insert_types(t_token *tokens);
char	*token_dup(const char *s, int size);

#endif
