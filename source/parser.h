/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:00:14 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 14:42:43 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//NODE_LOGICAL_AND
//NODE_LOGICAL_OR
#include "lexer.h"

typedef enum
{
	REDIRECT_LESS,
	REDIRECT_GREAT,
	REDIRECT_DGREAT
}	t_redirect_type;

typedef enum
{
	UNINITIALIZED,
	NODE_COMMAND,
	NODE_REDIRECT,
	NODE_PIPE
} e_node_type;

typedef struct s_astnode
{
	e_node_type			type;
	t_token				*tokens;
	struct s_astnode	*left;
	struct s_astnode	*right;
	char				**args;
	char				*file;
	TokenType			redirect_type;
} t_astnode;

void		parser(t_astnode *root);
t_astnode	*create_node(t_token *tokens);
t_astnode	*parse_pipe(t_astnode *root);
t_astnode	*parse_redirect(t_astnode *root);
t_astnode	*parse_command(t_astnode *root);