NAME	= minishell

CC		= cc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror

SRC =	main.c								\
		memtrack/allocation.c				\
		memtrack/deallocation.c				\
		src/builtins/cmd_cd.c				\
		src/builtins/cmd_env.c				\
		src/builtins/cmd_pwd.c				\
		src/builtins/cmd_exit.c				\
		src/builtins/cmd_echo.c				\
		src/builtins/cmd_unset.c			\
		src/builtins/cmd_export.c			\
		src/parser/syntax_check.c			\
		src/parser/parser.c					\
		src/executer/command_execution.c	\
		src/executer/process_execution.c	\
		src/lexer/lexer.c					\
		src/lexer/utils_token.c				\
		src/signal/signal.c					\
		src/expander/expander.c				\
		src/utils/exit.c					\
		src/utils/utils_builtin.c			\
		src/utils/utils_env.c				\
		src/utils/utils_parser.c			\
		src/utils/utils_rdir.c				\
		src/utils/utils.c					\

LIBFT = libft/libft.a


OBJ_DIR = .objs

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME):$(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) -lreadline
	@echo "$(B_BLUE)Minishell compiled : ✅$(NC)"


$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@sleep 0.01
	echo -e "\033[2J\033[H"
	@echo "$(B_CYAN)[Src compiling] $(B_GREEN):$(B_GREEN) $<$(B_GREEN)$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C libft clean
	echo -e "\033[2J\033[H"
	@echo "$(B_RED)Minishell object files cleaned : ✅$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	echo -e "\033[2J\033[H"
	@echo "$(B_RED)Minishell cleaned : ✅$(NC)"

re: fclean all

iclean:
	@grep -v '^#' .gitignore | grep -v '^$$' | while read pattern; do \
		find . -name "$$pattern" -exec rm -rf {} +; \
	done
	echo -e "\033[2J\033[H"
	@echo "$(B_RED)Minishell ignor files cleared: ✅$(NC)"


norm:
	@if norminette | grep -q "Error"; then \
		echo "Norminette: $(B_RED)[KO]$(NC)"; \
		norminette | grep "Error"; \
	else \
		echo "Norminette: $(B_GREEN)[OK]$(NC)"; \
	fi

.PHONY: all fclean clean re

NC		= \033[0m
CYAN	= \033[0;36m
B_BLUE	= \033[1;34m
B_RED	= \033[1;31m
B_GREEN	= \033[1;32m
B_CYAN	= \033[1;36m
