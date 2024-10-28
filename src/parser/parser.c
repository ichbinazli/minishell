/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:02:32 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:05:34 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/libft.h"
#include <string.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <unistd.h>

void	fork_and_execute_commands(t_data *data)
{
	t_token	*node;
	char	**env;
	int		pipfd[2];

	env = env_to_char_array(data);
	node = data->token;
	while (node)
	{
		if (is_args(node) || rdir(node))
		{
			if (data->pipes)
				if (pipe(pipfd) == -1)
					ft_exit(strerror(errno));
			data->pid = fork();
			if (data->pid == 0)
				handle_child_process(data, node, pipfd, env);
			else
				node = handle_parent_process(data, pipfd, node);
		}
		if (node)
			node = node->next;
	}
	while (wait(NULL) > 0)
		;
	close_and_zero(data, pipfd);
}

void	handle_multiple_command(t_data *data)
{
	t_token	*node;

	node = data->token;
	while (node)
	{
		if (rdir(node) == 2)
			data->heredoc = 1;
		if (node->type == PIPE)
			data->pipes = 1;
		node = node->next;
	}
	fork_and_execute_commands(data);
}

void	handle_single_command(t_data *data)
{
	if (is_args(data->token))
	{
		while (data->token && *data->token->value == '\0'
			&& data->token->type == WORD)
			data->token = data->token->next;
		if (!data->token)
			return ;
		if (!ft_strcmp(data->token->value, "cd"))
			cmd_cd(data, data->token->next, NULL, NULL);
		else if (!ft_strcmp(data->token->value, "pwd"))
			cmd_pwd();
		else if (!is_echo(data->token->value, "echo"))
			cmd_echo(data->token->next);
		else if (!ft_strcmp(data->token->value, "env"))
			cmd_env(data, data->token);
		else if (!ft_strcmp(data->token->value, "export"))
			cmd_export(data, data->token->next);
		else if (!ft_strcmp(data->token->value, "unset"))
			cmd_unset(data, data->token->next);
		else if (!ft_strcmp(data->token->value, "exit"))
			cmd_exit(data->token->next);
		else
			execute_command(data);
	}
}

int	command_count(t_data *data)
{
	t_token	*node;

	node = data->token;
	if ((is_args(node) && !node->next))
		return (1);
	else
	{
		while (node)
		{
			if (node->type == PIPE || rdir(node))
				return (0);
			node = node->next;
		}
		return (1);
	}
	return (0);
}

void	parser(t_data *data)
{
	if (check_syntax_errors(data->token))
		return ;
	if (!data->token)
		return ;
	if (command_count(data) == 1)
		handle_single_command(data);
	else
		handle_multiple_command(data);
}
