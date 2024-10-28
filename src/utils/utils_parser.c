/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:06:58 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:09:17 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"
#include <sys/stat.h>
#include <unistd.h>

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

char	*handle_executable_file(t_token *node, char *path)
{
	char	*tmp;

	if (is_directory(path))
	{
		print_error(node, ": is a directory\n", 126);
		return (NULL);
	}
	else if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			tmp = ft_strdup(path);
			add_to_memtrack(tmp);
			return (tmp);
		}
		print_error(node, ": Permission denied\n", 126);
		return (NULL);
	}
	print_error(node, ": No such file or directory\n", 127);
	return (NULL);
}

int	get_token_lenght(t_token *node)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = node;
	while (tmp && (is_args(tmp) || rdir(tmp) == 1))
	{
		if (is_args(tmp) && (!tmp->prev || (tmp->prev && !rdir(tmp->prev))))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**get_command_args(t_token *node)
{
	char	**args;
	int		i;

	args = memtrack_alloc(sizeof(char *) * (get_token_lenght(node) + 1));
	i = 0;
	while (node && (is_args(node) || rdir(node) == 1))
	{
		if (is_args(node) && (!node->prev || (node->prev && !rdir(node->prev))))
		{
			args[i] = node->value;
			i++;
		}
		node = node->next;
	}
	args[i] = NULL;
	return (args);
}
