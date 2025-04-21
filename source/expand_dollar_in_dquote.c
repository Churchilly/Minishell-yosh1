/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_in_dquote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 05:48:02 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/21 21:19:01 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"
#include "enviroment.h"
#include "garbage_collector.h"
#include <stdio.h>

int	is_token(char c);
int	is_sequence(char c);
int	is_space(char c);

void	pass_env_var(char **token_val, char ***env_vars);
int		get_env_vars(char *token_value, char **env_vars);

char	*expand_quotes(char *token_value);

static int	count_dollars_in_dquotes(const char *str)
{
	int	ret;
	int	dquote;

	ret = 0;
	dquote = 0;
	while (*str)
	{
		if (*str == '\"')
			dquote = !dquote;
		else if (dquote && *str == '$')
			ret++;
		str++;
	}
	return (ret);
}

static void	get_new_size(char *token_val, char **env_vars, int *len)
{
	int	dquote;
	int	i;

	*len = 0;
	dquote = 0;
	i = -1;
	while (*token_val)
	{
		if (dquote && *token_val == '$')
		{
			while ((*env_vars)[++i])
			{
				(*len)++;
			}
			pass_env_var(&token_val, &env_vars);
		}
		else
		{
			if (*token_val == '\"')
				dquote = !dquote;	
			(*len)++;
			token_val++;
		}
	}
}

static void	place_env_vars(char *token_val, char **env_vars, char *expanded)
{
	int	dquote;
	int	i;
	
	dquote = 0;
	i = -1;
	while (*token_val)
	{
		if (dquote && *token_val == '$')
		{
			while ((*env_vars)[++i])
			{
				*expanded = (*env_vars)[i];
				expanded++;
			}
			pass_env_var(&token_val, &env_vars);
		}
		else
		{
			if (*token_val == '\"')
				dquote = !dquote;	
			*expanded = *token_val;
			expanded++;
			token_val++;
		}
	}
}

char	*expand_dollar_in_dquote(char *token_value)
{
	char	*tmp;
	char	*ret;
	char	**env_vars;
	int		len;
	
	len = count_dollars_in_dquotes(token_value);
	env_vars = (char **)gc_calloc(sizeof(char *) * (len + 1), SECTION_LA);
	get_env_vars(token_value, env_vars);
	env_vars[len] = NULL;
	get_new_size(token_value, env_vars, &len);
	tmp = malloc(sizeof(char) * (len + 1));
	place_env_vars(token_value, env_vars, tmp);
	tmp[len] = '\0';
	ret = expand_quotes(tmp);
	return (ret);
}
