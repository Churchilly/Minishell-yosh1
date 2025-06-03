/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:26:18 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 14:42:01 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"

int	count_words(t_token *tokens)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (tokens[i].type != TOKEN_EON && tokens[i].value)
	{
		if (tokens[i].type != TOKEN_SKIP)
			words++;
		i++;
	}
	return (words);
}

char	**token_to_command(t_token *tokens)
{
	int		i;
	char	**command_list;
	int		word_count;
	int		word;

	word_count = count_words(tokens);
	command_list = gc_calloc(sizeof(char *) * (word_count + 1), SECTION_LA);
	i = 0;
	word = 0;
	while (tokens[i].type != TOKEN_EON && tokens[i].value)
	{
		if (tokens[i].type != TOKEN_SKIP)
			command_list[word++] = tokens[i].value;
		i++;
	}
	return (command_list);
}

t_astnode	*parse_command(t_astnode *root)
{
	char	**command_list;

	if (!root)
		return (NULL);
	if (root->type == UNINITIALIZED)
	{
		command_list = token_to_command(root->tokens);
		root->args = command_list;
		root->type = NODE_COMMAND;
	}
	else
	{
		if (root->left)
			parse_command(root->left);
		if (root->right)
			parse_command(root->right);
	}
	return (root);
}
