/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 04:31:33 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/13 20:39:43 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"
#include "enviroment.h"
#include "str.h"
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

void	*free_docs(char **docs);
char	*new_document(char *eof, t_enviroment *env);

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

static char	**create_docs(t_token *tokens, t_enviroment *env)
{
	char	**paths;
	char	*eof;
	int		count;
	int		i;
	
	count = count_heredocs(tokens);
	paths = (char **)malloc((sizeof(char *) * count) + 1);
	i = 0;
	while (i < count)
	{
		while ((*tokens).type != TOKEN_DLESS)
		{
			tokens++;
		}
		eof = (*(tokens + 1)).value;
		if (!eof)
			return (write(1, "yosh: syntax error\
 near unexpected token `newline'\n", 52), free_docs(paths));
		paths[i] = new_document(eof, env);
		if (!paths[i])
			return (free_docs(paths));
		i++;
	}
	paths[count] = NULL;
	return (paths);
}

int	expand_heredoc(t_token *tokens, t_enviroment *env)
{
	char		**buffer;
	
	buffer = create_docs(tokens, env);
	if (!buffer)
		return (1);
	while (*buffer)
	{
		while ((*tokens).type != TOKEN_DLESS)
			tokens++;
		tokens->type = TOKEN_LESS;
		free(tokens->value);
		tokens->value = ft_strdup("<");
		if (!tokens->value)
			return (1);
		tokens++;
		free(tokens->value);
		tokens->value = *buffer;
		buffer++;
	}
	return (0);
}
