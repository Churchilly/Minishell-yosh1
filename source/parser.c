/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:29:28 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 14:42:50 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include "parser.h"
#include <stdio.h>
#include "str.h"
#include <unistd.h>

//first we initialize first node
//then we send it to the parser
//returns itself

//only pipe can have children

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