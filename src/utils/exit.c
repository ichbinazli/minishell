/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:06:33 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:08:25 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

char	*exit_status(void)
{
	char	*status;

	status = ft_itoa(*get_exit_status());
	add_to_memtrack(status);
	return (status);
}

void	close_and_zero(t_data *data, int pipfd[2])
{
	data->in_fd = 0;
	data->pid = 0;
	if (data->pipes)
	{
		close(pipfd[0]);
		close(pipfd[1]);
		data->pipes = 0;
	}
}

void	print_error(t_token *node, char *str, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	if (node)
		ft_putstr_fd(node->value, 2);
	ft_putstr_fd(str, 2);
	*get_exit_status() = exit_status;
}

void	ft_exit(char *str)
{
	free_memtrack();
	if (str)
	{
		ft_putstr_fd("Error! :", 2);
		ft_putstr_fd(str, 2);
	}
	rl_clear_history();
	exit(*get_exit_status());
}
