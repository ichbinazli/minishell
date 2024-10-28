/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deallocation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:58:12 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:01:53 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

void	free_memtrack(void)
{
	t_malloc	*tmp;
	t_malloc	*memtrack;

	memtrack = get_memtrack()->next;
	while (memtrack)
	{
		tmp = memtrack;
		memtrack = memtrack->next;
		free(tmp->ptr);
		free(tmp);
	}
}

void	free_memtrack_block(void *ptr)
{
	t_malloc	*memtrack;
	t_malloc	*tmp;

	if (!ptr)
		return ;
	memtrack = get_memtrack();
	while (memtrack)
	{
		if (memtrack->ptr == ptr)
		{
			tmp->next = memtrack->next;
			free(memtrack);
			free(ptr);
			ptr = NULL;
			return ;
		}
		tmp = memtrack;
		memtrack = memtrack->next;
	}
}

void	free_token(t_data *data)
{
	t_token	*token;
	t_token	*tmp;

	token = data->token;
	while (token)
	{
		tmp = token;
		token = token->next;
		free_memtrack_block(tmp->value);
		free_memtrack_block(tmp);
	}
	data->token = NULL;
}
