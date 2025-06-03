/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:01:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:44:52 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"
#include "parser.h"
#include <unistd.h>
#include "executer.h"
#include "str.h"
#include "environment.h"
#include "garbage_collector.h"
#include "expander.h"
#include "minishell.h"

volatile int	g_signal = 0;

static t_token	*get_tokens(t_environment *env)
{
	char	*input;
	t_token	*tokens;
	int		status;

	input = readline("yosh1> ");
	if (!input)
	{
		write(1, "exit\n", 5);
		exit(env->last_pipe);
	}
	gc_add(input, SECTION_LA);
	if (check_sequence_complete(input))
		exit(1);
	tokens = lexer(input);
	status = check_syntax(tokens);
	if (!tokens->value || status)
	{
		update_last_pipe(status);
		return (NULL);
	}
	add_history(input);
	return (tokens);
}

int	main(void)
{
	t_token				*tokens;
	t_astnode			*ast;
	t_environment		env;
	t_garbage_collector	gc;

	gc_setup(&gc, &env);
	setup_environment();
	while (1)
	{
		gc_clean_list(SECTION_LA);
		setup_parent_signals();
		tokens = get_tokens(&env);
		if (expander(&tokens))
			continue ;
		ast = create_node(tokens);
		parser(ast);
		executer(ast);
		gc_clean_paths();
	}
	exit(env.last_pipe);
}

void	bye(void)
{
	rl_clear_history();
	clear_environment();
	gc_cleanup();
}
