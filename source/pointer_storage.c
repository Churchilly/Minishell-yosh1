/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_storage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:50 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/21 17:14:05 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include "enviroment.h"
#include <stdio.h>

void	*pointer_storage(int type, void *ptr)
{
	static void	*collector;
	static void	*enviroment;

	if (!ptr)
	{
		if (type == COLLECTOR)
			return (collector);
		else if (type == ENVIROMENT)
			return (enviroment);
	}
	else
	{
		if (type == COLLECTOR)
			collector = ptr;
		else if (type == ENVIROMENT)
			enviroment = ptr;
	}
	return (NULL);
}
