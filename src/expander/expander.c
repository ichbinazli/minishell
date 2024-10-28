/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:04:13 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:07:58 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"

void	join_value(t_token *node)
{
	char	*new;

	new = ft_strjoin(node->prev->value, node->value);
	add_to_memtrack(new);
	node->prev->value = new;
	node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	node->prev->flag = node->flag;
}

void	expand_variable(t_data *data, t_token *node, char *tmp, int i)
{
	t_env	*env;
	char	*str;
	char	*env_key;
	char	*prev;

	env_key = NULL;
	str = NULL;
	env_key = ft_substr(tmp + 1, 0, i - 1);
	add_to_memtrack(env_key);
	prev = ft_substr(node->value, 0, tmp - node->value);
	add_to_memtrack(prev);
	env = get_env(data, env_key);
	if (env && env->value)
		str = ft_str_arr_join((char *[]){prev, env->value, tmp + i}, 3);
	else if (*env_key == '?')
		str = ft_str_arr_join((char *[]){prev, exit_status(), tmp + 2}, 3);
	else
		str = ft_str_arr_join((char *[]){prev, tmp + i}, 2);
	if (str == NULL)
		str = "";
	free_memtrack_block(node->value);
	node->value = ft_strdup(str);
	add_to_memtrack(node->value);
	free_memtrack_block(str);
}

void	expand_tokens(t_data *data, t_token *node)
{
	char	*tmp;
	int		i;

	tmp = ft_strchr(node->value, '$');
	while (tmp)
	{
		i = 1;
		while (tmp[i] && (ft_isalnum(tmp[i]) || tmp[i] == '?' || tmp[i] == '_'))
		{
			i++;
			if (ft_isdigit(tmp[1]))
				break ;
		}
		if (i == 1)
		{
			tmp++;
			tmp = ft_strchr(tmp, '$');
			continue ;
		}
		expand_variable(data, node, tmp, i);
		tmp = ft_strchr(node->value, '$');
	}
}

void	expander(t_data *data)
{
	t_token	*node;
	int		in_heredoc;

	in_heredoc = 0;
	node = data->token;
	while (node)
	{
		if (node->type == HEREDOC)
		{
			node = node->next;
			in_heredoc = 1;
			continue ;
		}
		if ((node->type == WORD || node->type == DOUBLE_QUOTE) && !in_heredoc)
			expand_tokens(data, node);
		if (node->prev && node->prev->flag)
			join_value(node);
		if (!node->flag)
			in_heredoc = 0;
		node = node->next;
	}
}
