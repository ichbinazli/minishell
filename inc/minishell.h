/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:58:46 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:56:16 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SYNTAX_LINE "syntax error near unexpected token `newline'\n"
# define SYNTAX_PIPE "syntax error near unexpected token `|'\n"

# define PROMT_SIG 0
# define HERE_SIG 1
# define EXEC_SIG 2
# define NOT_SET -1

typedef struct s_malloc
{
	void				*ptr;
	struct s_malloc		*next;
}						t_malloc;

enum					e_token_type
{
	WORD,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
	int					flag;
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	t_env				*env;
	t_token				*token;
	char				*cmd;
	int					syntax_err;
	int					in_fd;
	int					pid;
	int					pipes;
	int					heredoc;
}						t_data;

t_malloc				*get_memtrack(void);
void					*memtrack_alloc(unsigned int size);
void					add_to_memtrack(void *ptr);
void					free_memtrack(void);
void					free_memtrack_block(void *ptr);
void					free_token(t_data *data);
void					ft_exit(char *str);
void					print_error(t_token *node, char *str, int exit_status);
void					close_and_zero(t_data *data, int pipfd[2]);
char					*exit_status(void);
void					init_data(t_data *data);
void					setup_system(t_data *data, char **envp);
t_env					*get_env(t_data *data, char *key);
char					*ft_str_arr_join(char **str_list,
							unsigned int str_count);
int						rdir(t_token *node);
int						is_args(t_token *node);
int						skip_space(char *str, int i);
int						ft_validchar(int c);
void					lexer(t_data *data);
t_token					*last_token(t_token *node);
t_token					*new_token(char *value, enum e_token_type type);
void					add_token_back(t_token **node, t_token *new);
void					expander(t_data *data);
void					expand_tokens(t_data *data, t_token *node);
void					parser(t_data *data);
char					*handle_executable_file(t_token *node, char *path);
char					*finding_path(t_data *data, t_token *node);
char					**env_to_char_array(t_data *data);
char					**get_command_args(t_token *node);
int						run_builtin_command(t_data *data, char **args);
void					handle_single_command(t_data *data);
void					handle_redirection(t_token *node, t_data *data);
int						check_syntax_errors(t_token *node);
void					update_oldpwd(t_data *data, char *pwd);
void					cmd_cd(t_data *data, t_token *node, char *path,
							char *pwd);
void					cmd_echo(t_token *node);
void					cmd_env(t_data *data, t_token *node);
void					cmd_exit(t_token *node);
int						*get_exit_status(void);
void					update_exit_status(void);
void					cmd_export(t_data *data, t_token *node);
t_env					*get_pwd(t_data *data);
void					cmd_pwd(void);
int						check_valid_key(char *key, t_token *node);
void					cmd_unset(t_data *data, t_token *node);
void					execute_command(t_data *data);
void					manage_sigquit(void);
void					handle_sigint(int sig);
int						is_echo(char *str1, char *str2);
t_token					*handle_parent_process(t_data *data, int pipfd[2],
							t_token *node);
void					handle_child_process(t_data *data, t_token *node,
							int pipfd[2], char **env);
int						signal_state(int set_signal);

#endif
