/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:06:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/16 02:13:53 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <unistd.h>
#include <stdlib.h>

int		is_space(char c);
int		count_tokens(char *str);
void	split_tokens(char **tokens, char **str, t_garbage_collector *gc);
void	insert_types(t_token *tokens);
void	free_tokens(t_token *tokens);

t_token	*lexer(char *input, t_garbage_collector *gc)
{
	t_token	*tokens;
	int		number_of_tokens;
	int		i;
	
	number_of_tokens = count_tokens(input);
	printf("numb of tokens: [%d]\n", number_of_tokens);
	tokens = (t_token *)gc_calloc(sizeof(t_token) * (number_of_tokens + 1),
		&(gc->tokens));
	if (!tokens)
		return ((t_token *)NULL);
	i = -1;
	while (*input)
	{
		if (is_space(*input))
			input++;
		else
		{
			split_tokens(&(tokens[++i].value), &input, gc);
			if (!(tokens[i].value))
				return (free_tokens(tokens), NULL);
		}
	}
	tokens[++i].value = NULL;
	insert_types(tokens);
	return (tokens);
}
