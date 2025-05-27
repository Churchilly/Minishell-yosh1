/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_mirror.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:24:35 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/27 17:56:12 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include <stddef.h>
#include <stdio.h>
#include "garbage_collector.h"

void	*pointer_storage(int type, void *ptr);
void	*gc_calloc(size_t size, t_section section_name);

static int	count_variables(t_node *head)
{
	int	i;

	i = 0;
	while (head->next)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	*join_env_variable(char *key, char *value)
{
	char	*joined;
	char	*ret;
	int		key_len;
	int		value_len;
	int		ret_len;

	key_len = 0;
	value_len = 0;
	while (key[key_len])
		key_len++;
	while (value[value_len])
		value_len++;
	ret_len = key_len + value_len + 1;
	joined = gc_calloc(sizeof(char) * (ret_len + 1), SECTION_LA);
	ret = joined;
	while (*key)
		*joined++ = *key++;
	*joined++ = '=';
	while (*value)
		*joined++ = *value++;
	return (ret);
}

char	**env_mirror()
{
	t_environment	*env;
	t_node			*head;
	char			**mirror;
	char			**ret;
	
	env = (t_environment *)pointer_storage(ENVIRONMENT, NULL);
	head = env->top;
	mirror = gc_calloc(sizeof(char *) * (count_variables(head) + 1), SECTION_LA);
	ret = mirror;
	while (head->next)
	{
		*mirror = join_env_variable(head->key, head->value);
		head = head->next;
		mirror++;
	}
	return (ret);
}
