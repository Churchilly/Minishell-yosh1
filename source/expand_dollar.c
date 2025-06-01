/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:49:42 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/01 21:29:38 by obastug          ###   ########.fr       */
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
	new = divide_tokens(tokens);
	return (new);
}
