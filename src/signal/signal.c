/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:05:45 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:07:11 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../inc/minishell.h"
#include <readline/readline.h>
#include <signal.h>

int	signal_state(int set_signal)
{
	static int	signal = 0;

	if (set_signal != NOT_SET)
		signal = set_signal;
	return (signal);
}

void	handle_sigint(int sig)
{
	*get_exit_status() = 128 + sig;
	if (signal_state(NOT_SET) == HERE_SIG)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_exit(NULL);
	}
	else if (signal_state(NOT_SET) == EXEC_SIG)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (signal_state(NOT_SET) == PROMT_SIG)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	*get_exit_status() = 128 + sig;
	if (signal_state(NOT_SET) == EXEC_SIG)
	{
		printf("Quit : %d\n", sig);
		rl_replace_line("", 0);
	}
}

void	manage_sigquit(void)
{
	if (signal_state(NOT_SET) == EXEC_SIG)
		signal(SIGQUIT, handle_sigquit);
	else
		signal(SIGQUIT, SIG_IGN);
}
