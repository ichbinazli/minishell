/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:06:15 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:08:41 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"
#include <unistd.h>

t_token	*args_to_token(char **args)
{
	t_token	*token;
	int		i;

	i = -1;
	token = NULL;
	while (args[++i])
		add_token_back(&token, new_token(args[i], WORD));
	return (token);
}

int	run_builtin_command(t_data *data, char **args)
{
	t_token	*node;

	if (args)
	{
		node = args_to_token(args);
		if (!ft_strcmp(args[0], "cd"))
			return (cmd_cd(data, node->next, NULL, NULL), 1);
		else if (!ft_strcmp(args[0], "pwd"))
			return (cmd_pwd(), 1);
		else if (!is_echo(args[0], "echo"))
			return (cmd_echo(node->next), 1);
		else if (!ft_strcmp(args[0], "env"))
			return (cmd_env(data, node), 1);
		else if (!ft_strcmp(args[0], "export"))
			return (cmd_export(data, node->next), 1);
		else if (!ft_strcmp(args[0], "unset"))
			return (cmd_unset(data, node->next), 1);
		else if (!ft_strcmp(args[0], "exit"))
			return (cmd_exit(node->next), 1);
	}
	return (0);
}
