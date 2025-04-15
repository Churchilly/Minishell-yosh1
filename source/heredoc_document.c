/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_document.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:35:50 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/15 19:14:52 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern volatile int g_signal;

#include <readline/readline.h>
#include "lexer.h"
#include "enviroment.h"
#include "str.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*ft_strjoin_nl(char const *s1, char const *s2);
char	*expand_variables(char *input, t_enviroment *env);
int		setup_heredoc_child_signals(void);
char	*ft_itoa(int n);
int	is_quoted(char *str);
int	have_dollar(char *str);
int	strcmp_without_quotes(char *input, char *eof);


char	*create_content(char *eof, char *ret, char *input, t_enviroment *env)
{
	char	*tmp;

	tmp = ret;
	if (!is_quoted(eof) && have_dollar(input))
	{
		input = expand_variables(input, env);
		if (!input)
			return (NULL);
	}
	ret = ft_strjoin_nl(ret, input);
	if (!ret)
		return (NULL);
	free(tmp);
	free(input);
	return (ret);
}

static char	*get_document_content(char *eof, t_enviroment *env)
{
	char	*input;
	char	*ret;

	ret = ft_strdup("\0");
	if (!ret)
		return (NULL);
	while (42)
	{
		input = readline("> ");
		printf("here\n");
		if (g_signal)
			return (env->last_pipe = g_signal + 128, free(ret),
				free(input), NULL);
		if (!input || strcmp_without_quotes(input, eof))
		{
			if (!input)
				printf("yosh1: warning: here-document delimited by end-of-file\
 (wanted `%s')", eof);
 			free(input);
			break ;
		}
		ret = create_content(eof, ret, input, env);
		printf("here2\n");
		if (!ret)
			return (NULL);
		printf("here1\n");
	}
	return (ret);
}

static char	*create_unique_path(char *path)
{
	int		i;
	char	*numeric;
	char	*full;
	
	i = 0;
	while (42)
	{
		numeric = ft_itoa(i);
		if (!numeric)
			return (NULL);
		full = ft_strjoin(path, numeric);
		if (!full)
			return (NULL);
		if (access(full, F_OK) == -1)
			break ;
		free(numeric);
		free(full);
		i++;
	}
	free(path);
	free(numeric);
	return (full);
}

static char	*create_temp_file(char *content)
{
	char	*path;
	int		fd;

	path = ft_strdup("/tmp/yosh_heredoc_temp_");
	path = create_unique_path(path);
	if (!path)
		return (NULL);
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		write(2, "Failed to create temp file\n", 28);
		free(path);
		return (NULL);
	}
	if (write(fd, content, ft_strlen(content)) == -1)
	{
		write(2, "Failed to write to temp file\n", 30);
		close(fd);
		free(path);
		return (NULL);
	}
	close(fd);
	return (path);
}

char	*new_document(char *eof, t_enviroment *env)
{
	char	*content;
	char	*path;

	if (setup_heredoc_child_signals())
		return (NULL);
	content = get_document_content(eof, env);
	if (!content)
		return (NULL);
	path = create_temp_file(content);
	return (path);
}
