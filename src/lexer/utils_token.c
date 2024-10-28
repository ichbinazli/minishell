/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:05:21 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:07:00 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stddef.h>

t_token	*new_token(char *value, enum e_token_type type)
{
	t_token	*token;

	token = memtrack_alloc(sizeof(t_token));
	*token = (t_token){.value = value, .type = type, .flag = 0};
	return (token);
}

t_token	*last_token(t_token *node)
{
	if (node == NULL)
		return (0);
	while (node)
	{
		if (node->next == NULL)
			return (node);
		node = node->next;
	}
	return (node);
}

void	add_token_back(t_token **node, t_token *new)
{
	t_token	*token;

	if (!new)
		return ;
	if (*node)
	{
		token = last_token(*node);
		new->prev = token;
		token->next = &*new;
	}
	else
		*node = new;
}
