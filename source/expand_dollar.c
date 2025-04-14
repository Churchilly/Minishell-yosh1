/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:49:42 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/15 00:01:26 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "enviroment.h"
#include "str.h"
#include <stdlib.h>

void	print_tokens(t_token *tokens); // for testing purposes
int		replace_dollars(t_token *tokens, t_enviroment *env);
t_token	*divide_tokens(t_token *tokens);
void	free_tokens(t_token *tokens);

t_token	*expand_dollar(t_token *tokens, t_enviroment *env)
{
	t_token	*new;
	
	if (replace_dollars(tokens, env))
		return (NULL);
	printf("<EXPANDER_DOLLAR STEP1>\n");
	print_tokens(tokens);
	new = divide_tokens(tokens);
	if (!new)
		return (NULL);
	printf("<EXPANDER_DOLLAR STEP2>\n");
	print_tokens(new);
	free_tokens(tokens);
	return (new);
}