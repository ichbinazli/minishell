/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:02:50 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/18 12:34:02 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"
#include <string.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <unistd.h>

char	*check_path(char **path, t_token *node)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (path[i])
	{
		tmp = ft_str_arr_join((char *[]){path[i], "/", node->value}, 3);
		if (access(tmp, F_OK) == 0)
		{
			if (access(tmp, X_OK) == 0)
				return (tmp);
			else
			{
				print_error(node, ": Permission denied\n", 126);
				return (NULL);
			}
		}
		i++;
		free_memtrack_block(tmp);
	}
	return (print_error(node, ": command not found\n", 127), NULL);
}

int	is_path(char *str)
{
	return ((str[0] == '.' && str[1] == '/') || str[0] == '/');
}

int	is_builtin(char *path)
{
	if (!is_echo(path, "echo"))
		return (1);
	if (ft_strcmp(path, "cd") == 0)
		return (1);
	if (ft_strcmp(path, "pwd") == 0)
		return (1);
	if (ft_strcmp(path, "export") == 0)
		return (1);
	if (ft_strcmp(path, "unset") == 0)
		return (1);
	if (ft_strcmp(path, "env") == 0)
		return (1);
	if (ft_strcmp(path, "exit") == 0)
		return (1);
	return (0);
}

char	*finding_path(t_data *data, t_token *node)
{
	t_env	*env;
	char	**path;
	int		i;

	i = -1;
	if (!node)
		return (NULL);
	if (!(*node->value))
		return (print_error(data->token, ": command not found\n", 127), NULL);
	if (is_builtin(node->value))
		return (NULL);
	if (is_path(node->value))
		return (handle_executable_file(node, node->value));
	env = get_env(data, "PATH");
	if (!env)
		return ((print_error(node, ": command not found\n", 127)), NULL);
	path = ft_split(env->value, ':');
	add_to_memtrack(path);
	while (path[++i])
		add_to_memtrack(path[i]);
	return (check_path(path, node));
}

void	execute_command(t_data *data)
{
	pid_t	pid;
	char	**env;
	char	*path;
	char	**args;

	signal_state(EXEC_SIG);
	manage_sigquit();
	env = env_to_char_array(data);
	if (is_args(data->token))
	{
		path = finding_path(data, data->token);
		if (!path)
			return ;
		args = get_command_args(data->token);
		while (data->token->next && is_args(data->token->next))
			data->token = data->token->next;
		pid = fork();
		if (pid == -1)
			ft_exit(strerror(errno));
		else if (pid == 0)
			if (execve(path, args, env) == -1)
				ft_putendl_fd(strerror(errno), 2);
		waitpid(pid, get_exit_status(), 0);
		update_exit_status();
	}
}
