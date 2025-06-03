/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:00:14 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 14:51:54 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_redirect_type	t_redirect_type;
typedef enum e_node_type		t_node_type;
typedef struct s_astnode		t_astnode;

enum e_redirect_type
{
	REDIRECT_LESS,
	REDIRECT_GREAT,
	REDIRECT_DGREAT
};

enum e_node_type
{
	UNINITIALIZED,
	NODE_COMMAND,
	NODE_REDIRECT,
	NODE_PIPE
};

struct s_astnode
{
	t_node_type			type;
	t_token				*tokens;
	struct s_astnode	*left;
	struct s_astnode	*right;
	char				**args;
	char				*file;
	t_token_type		redirect_type;
};

void		parser(t_astnode *root);
t_astnode	*create_node(t_token *tokens);

#endif
