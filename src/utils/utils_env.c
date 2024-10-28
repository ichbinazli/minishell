/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:31:27 by sekeskin          #+#    #+#             */
/*   Updated: 2024/10/18 12:34:30 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/libft.h"
#include <stdio.h>

t_env	*get_env(t_data *data, char *key)
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	**env_to_char_array(t_data *data)
{
	t_env	*node;
	char	**env;
	int		i;

	i = 0;
	node = data->env;
	while (node)
	{
		node = node->next;
		i++;
	}
	env = memtrack_alloc(sizeof(char *) * (i + 1));
	i = -1;
	node = data->env;
	while (++i, node->next)
	{
		if (node->value)
			env[i] = ft_str_arr_join((char *[]){node->key, "=", node->value},
					3);
		else
			env[i] = ft_str_arr_join((char *[]){node->key, "="}, 2);
		node = node->next;
	}
	env[i] = NULL;
	return (env);
}
