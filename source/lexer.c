/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:06:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/03/04 23:48:30 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <unistd.h>
#include <stdlib.h>

int	is_space(char c);
int	count_tokens(char *str);
void	split_tokens(char **tokens, char **str);
void	insert_types(t_token *tokens);
void	free_tokens(t_token *tokens);

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		number_of_tokens;
	int		i;
	
	number_of_tokens = count_tokens(input);
	printf("numb of tokens: [%d]\n", number_of_tokens);
	tokens = (t_token *)malloc(sizeof(t_token) * (number_of_tokens + 1));
	if (!tokens)
		return ((t_token *)NULL);
	i = -1;
	while (*input)
	{
		if (is_space(*input))
			input++;
		else
		{
			split_tokens(&(tokens[++i].value), &input);
			if (!(tokens[i].value))
				return (free_tokens(tokens), NULL);
		}
	}
	tokens[++i].value = NULL;
	insert_types(tokens);
	return (tokens);
}
