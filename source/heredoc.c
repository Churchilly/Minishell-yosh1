/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 04:31:33 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/22 01:54:19 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"
#include "enviroment.h"
#include "str.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>

char	*new_document(char *eof);
int	setup_heredoc_signals(void);
void	*pointer_storage(int type, void *ptr);

static int	count_heredocs(t_token *tokens)
{
	int	ret;
	int	i;

	i = -1;
	ret = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == TOKEN_DLESS)
			ret++;
	}
	return (ret);
}

static char	**create_docs(t_token *tokens)
{
	char	**paths;
	char	*eof;
	int		count;
	int		i;
	
	count = count_heredocs(tokens);
	paths = (char **)gc_calloc((sizeof(char *) * (count + 1)), SECTION_LA);
	eof = NULL;
	i = 0;
	while (i < count)
	{
		while ((tokens)->type != TOKEN_DLESS)
		{
			tokens++;
		}
		eof = (tokens + 1)->value;
		printf("eof00::%s\n",eof);
		if (!eof)
		{
			printf("yosh: syntax error near unexpected token `newline'\n");
			exit(1);
		}
		printf("eof0::%s\n",eof);
		paths[i] = new_document(eof);
		i++;
	}
	write(1, "ducker\n", 8);
	return (paths);
}

int	expand_heredoc_child(t_token *tokens)
{
	char		**buffer;
	
	buffer = create_docs(tokens);
	while (*buffer)
	{
		while ((*tokens).type != TOKEN_DLESS)
			tokens++;
		tokens->type = TOKEN_LESS;
		tokens->value = ft_strdup("<", SECTION_LA);
		tokens++;
		tokens->value = *buffer;
		buffer++;
	}
	exit(0);
}

int	expand_heredoc(t_token *tokens)
{
	pid_t	pid;
	int		status;
	t_garbage_collector *gc;

	gc = pointer_storage(COLLECTOR, NULL);
	gc->in_fork = 1;
	printf("curr:%s\n", tokens->value);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (setup_heredoc_signals())
		exit(1);
	if (pid == 0)
		expand_heredoc_child(tokens);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit(1);
	}
	gc->in_fork = 0;
	return (0);
}