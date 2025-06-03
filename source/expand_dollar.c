/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:49:42 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:03:35 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"
#include "str.h"
#include <stdlib.h>
#include "expander.h"

t_token	*expand_dollar(t_token *tokens)
{
	t_token	*new;

	replace_dollars(tokens);
	new = divide_tokens(tokens);
	return (new);
}
