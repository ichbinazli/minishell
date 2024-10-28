/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:08:20 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:10:48 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "inc/libft.h"
#include "inc/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

void	run_shell(t_data *data)
{
	while (1)
	{
		signal_state(PROMT_SIG);
		manage_sigquit();
		data->cmd = readline("\033[0;32mMinishell ~ \033[0m");
		if (!data->cmd)
			break ;
		add_to_memtrack(data->cmd);
		add_history(data->cmd);
		lexer(data);
		if (data->syntax_err)
		{
			printf("syntax error\n");
			free_token(data);
			free_memtrack_block(data->cmd);
			data->syntax_err = 0;
			continue ;
		}
		expander(data);
		parser(data);
		free_token(data);
		free_memtrack_block(data->cmd);
	}
}

void	init_data(t_data *data)
{
	data->env = memtrack_alloc(sizeof(t_env));
	data->token = NULL;
	data->cmd = 0;
	data->syntax_err = 0;
	data->in_fd = 0;
	data->pid = 0;
	data->pipes = 0;
	data->heredoc = 0;
}

void	setup_system(t_data *data, char **envp)
{
	t_env	*node;
	int		i;
	char	*tmp;

	init_data(data);
	i = -1;
	node = data->env;
	while (envp[++i])
	{
		tmp = ft_strchr(envp[i], '=');
		data->env->key = ft_substr(envp[i], 0, tmp - envp[i]);
		data->env->value = ft_substr(envp[i], (tmp - envp[i]) + 1,
				ft_strlen(envp[i]));
		add_to_memtrack(data->env->key);
		add_to_memtrack(data->env->value);
		if (envp[i + 1])
			data->env->next = memtrack_alloc(sizeof(t_env));
		data->env = data->env->next;
	}
	data->env = node;
	update_oldpwd(data, NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac == 1)
	{
		setup_system(&data, env);
		signal(SIGINT, handle_sigint);
		run_shell(&data);
		free_memtrack();
	}
	return (0);
}
