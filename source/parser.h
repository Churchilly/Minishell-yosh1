/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:00:14 by obastug           #+#    #+#             */
/*   Updated: 2025/04/29 18:12:20 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//NODE_LOGICAL_AND
//NODE_LOGICAL_OR
#include "lexer.h"

typedef enum e_redirect_type
{
	REDIRECT_LESS,
	REDIRECT_GREAT,
	REDIRECT_DGREAT
}	t_redirect_type;

typedef enum t_node_type
{
	UNINITIALIZED,
	NODE_COMMAND,
	NODE_REDIRECT,
	NODE_PIPE
}	e_node_type;

typedef struct s_astnode
{
	e_node_type			type;
	t_token				*tokens;
	struct s_astnode	*left;
	struct s_astnode	*right;
	char				**args;
	char				*file;
	t_token_type		redirect_type;
}	t_astnode;

void		parser(t_astnode *root);
t_astnode	*create_node(t_token *tokens);