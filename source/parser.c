/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:29:28 by obastug           #+#    #+#             */
/*   Updated: 2025/04/29 18:01:49 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include "parser.h"
#include <stdio.h>
#include "str.h"

//first we initialize first node
//then we send it to the parser
//returns itself

//only pipe can have children
#include <unistd.h>

t_astnode	*parse_pipe(t_astnode *root);
t_astnode	*parse_redirect(t_astnode *root);
t_astnode	*parse_command(t_astnode *root);

t_astnode	*create_node(t_token *tokens)
{
	t_astnode	*ret;

	ret = (t_astnode *)gc_calloc(sizeof(t_astnode), SECTION_LA);
	ret->tokens = tokens;
	return (ret);
}

void	parser(t_astnode *root)
{
	parse_pipe(root);
	parse_redirect(root);
	parse_command(root);
}