/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_document.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:35:50 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/28 14:41:04 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "str.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

extern volatile int	g_signal;

char	*ft_strjoin_nl(char const *s1, char const *s2);
char	*expand_variables(char *input);
void	setup_heredoc_child_signals(void);
int		is_quoted(char *str);
int		have_dollar(char *str);
int		strcmp_without_quotes(char *input, char *eof);

char	*create_content(char *eof, char *ret, char *input)
{
	if (!is_quoted(eof) && have_dollar(input))
	{
		input = expand_variables(input);
	}
	ret = ft_strjoin_nl(ret, input);
	return (ret);
}

static char	*get_document_content(char *eof)
{
	char	*input;
	char	*ret;

	ret = ft_strdup("\0", SECTION_LA);
	while (42)
	{
		input = readline("> ");
		if (g_signal)
			exit(1);
		if (!input || strcmp_without_quotes(input, eof))
		{
			if (!input)
				printf("yosh1: warning: here-document delimited by end-of-file\
 (wanted `%s')", eof);
			break ;
		}
		ret = create_content(eof, ret, input);
	}
	return (ret);
}

static char	*create_unique_path(char *path)
{
	int		i;
	char	*numeric;
	char	*full;

	i = 1;
	while (42)
	{
		numeric = ft_itoa(i, SECTION_LA);
		full = ft_strjoin(path, numeric, SECTION_LA);
		if (access(full, F_OK) == -1)
			break ;
		i++;
	}
	return (full);
}

static char	*create_temp_file(char *content)
{
	char	*path;
	int		fd;

	path = create_unique_path("/tmp/yosh_heredoc_temp_");
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		write(2, "Failed to create temp file\n", 28);
		exit(1);
	}
	if (write(fd, content, ft_strlen(content)) == -1)
	{
		write(2, "Failed to write to temp file\n", 30);
		close(fd);
		exit(1);
	}
	close(fd);
	return (path);
}

char	*new_document(char *eof)
{
	char	*content;
	char	*path;

	setup_heredoc_child_signals();
	content = get_document_content(eof);
	if (!content)
		return (NULL);
	path = create_temp_file(content);
	return (path);
}
