/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:04:51 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:06:35 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include "../../inc/minishell.h"

void	lex_words(t_data *data, int *i)
{
	t_token	*node;
	int		end;

	end = *i;
	while (data->cmd[end] && !ft_strchr(" \t\v\f|<>\'\"", data->cmd[end]))
		end++;
	node = new_token(ft_substr(data->cmd, *i, end - *i), WORD);
	add_to_memtrack(node->value);
	if (data->cmd[end] == '\'' || data->cmd[end] == '\"')
		node->flag = 1;
	add_token_back(&data->token, node);
	*i = end - 1;
}

void	lex_pipe(t_data *data)
{
	t_token	*node;

	node = new_token(ft_strdup("|"), PIPE);
	add_to_memtrack(node->value);
	add_token_back(&data->token, node);
}

void	lex_redirections(t_data *data, int *i, enum e_token_type type)
{
	t_token	*node;

	if (data->cmd[*i] == '>' && data->cmd[*i + 1] == '>')
	{
		node = new_token(ft_strdup(">>"), APPEND);
		*i += 1;
	}
	else if (data->cmd[*i] == '<' && data->cmd[*i + 1] == '<')
	{
		node = new_token(ft_strdup("<<"), HEREDOC);
		*i += 1;
	}
	else if (data->cmd[*i] == '>' )
		node = new_token(ft_strdup(">"), type);
	else
		node = new_token(ft_strdup("<"), type);
	add_to_memtrack(node->value);
	add_token_back(&data->token, node);
}

void	lex_quotes(t_data *data, int *i, enum e_token_type type)
{
	int		end;
	char	quote;
	t_token	*node;

	quote = data->cmd[*i];
	end = *i;
	while (data->cmd[++end] != quote)
	{
		if (data->cmd[end] == '\0')
		{
			data->syntax_err = 1;
			return ;
		}
	}
	node = new_token(ft_substr(data->cmd, *i + 1, end - *i - 1), type);
	add_to_memtrack(node->value);
	if (ft_validchar(data->cmd[end + 1]) && !ft_strchr("|<>", data->cmd[end
				+ 1]))
		node->flag = 1;
	add_token_back(&data->token, node);
	*i = end;
}

void	lexer(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd[++i])
	{
		i = skip_space(data->cmd, i);
		if (data->cmd[i] == '\0')
			break ;
		if (data->cmd[i] == '\'')
			lex_quotes(data, &i, SINGLE_QUOTE);
		else if (data->cmd[i] == '\"')
			lex_quotes(data, &i, DOUBLE_QUOTE);
		else if (data->cmd[i] == '|')
			lex_pipe(data);
		else if (data->cmd[i] == '<')
			lex_redirections(data, &i, REDIRECT_IN);
		else if (data->cmd[i] == '>')
			lex_redirections(data, &i, REDIRECT_OUT);
		else
			lex_words(data, &i);
	}
}
