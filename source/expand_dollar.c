/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:49:42 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/22 00:45:21 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"
#include "str.h"
#include <stdlib.h>

void	print_tokens(t_token *tokens); // for testing purposes
void	replace_dollars(t_token *tokens);
t_token	*divide_tokens(t_token *tokens);

t_token	*expand_dollar(t_token *tokens)
{
	t_token	*new;
	
	replace_dollars(tokens);
	printf("<EXPANDER_DOLLAR STEP1>\n");
	print_tokens(tokens);
	new = divide_tokens(tokens);
	printf("<EXPANDER_DOLLAR STEP2>\n");
	print_tokens(new);
	return (new);
}