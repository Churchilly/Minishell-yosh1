/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:56:21 by obastug           #+#    #+#             */
/*   Updated: 2025/04/29 14:00:52 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include <stdio.h>


//when it sees a pipe, defines current
//left and right nodes defined as follows
t_astnode	*divide_pipe(t_astnode *node, int i)
{
	node->left = create_node(node->tokens);
	node->right = create_node(node->tokens + i + 1);
	node->type = NODE_PIPE;
	node->tokens[i].type = TOKEN_EON;
	return (node);
}

t_astnode	*parse_pipe(t_astnode *root)
{
	int		i;
	int		breakpoint;

	i = 0;
	breakpoint = -1;
	if (!root)
		return (NULL);
	while (root->type == UNINITIALIZED && root->tokens[i].value
			&& root->tokens[i].type != TOKEN_EON)
	{
		if (root->tokens[i].type == TOKEN_PIPE)
			breakpoint = i;
		i++;
	}
	if (breakpoint != -1)
		divide_pipe(root, breakpoint);
	parse_pipe(root->left);
	parse_pipe(root->right);
	return (root);
}