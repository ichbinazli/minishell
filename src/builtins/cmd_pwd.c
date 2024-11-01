/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:01:24 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:03:28 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>

t_env	*get_pwd(t_data *data)
{
	t_env	*node;

	node = get_env(data, "PWD");
	if (!node)
	{
		node = memtrack_alloc(sizeof(t_env));
		node->key = "PWD";
		node->value = getcwd(NULL, 0);
		if (!node->value)
			ft_exit(strerror(errno));
		add_to_memtrack(node->value);
		node->next = data->env;
		data->env = node;
	}
	return (node);
}

void	cmd_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_exit(strerror(errno));
	add_to_memtrack(pwd);
	printf("%s\n", pwd);
	*get_exit_status() = 0;
}
