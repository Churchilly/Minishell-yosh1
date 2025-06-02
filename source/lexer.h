/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:03:49 by obastug           #+#    #+#             */
/*   Updated: 2025/04/18 18:54:24 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "garbage_collector.h"
# include "environment.h"

typedef enum e_token_type
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
}	TokenType;

typedef struct	s_token{
	TokenType	type;
	char		*value;
}			t_token;

t_token	*lexer(char *input);
void	expander(t_token **tokens);

#endif

// discuss params -> if everything is k create lexer
// checkout: https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/utilities/V3_chap02.html#tag_18_10_02
// 2.10.2 Shell Grammar Rules

// in grammar rules it they gives the control sceme
// extract what is needed and what is not then implement parser.
// also check LR parser algo
// >>https://www.geeksforgeeks.org/shift-reduce-parser-compiler/
