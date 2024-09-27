NAME	= minishell

CC		= cc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror

SRC =	src/main.c					\
		garbage_collecter/alloc.c	\
		garbage_collecter/clean.c	\
		src/check/cmd_check.c		\
		src/command/cmd_cd.c		\
		src/command/cmd_env.c		\
		src/command/cmd_pwd.c		\
		src/command/cmd_exit.c		\
		src/command/cmd_echo.c		\
		src/command/cmd_unset.c		\
		src/command/cmd_export.c	\
		src/excec/parser.c			\
		src/excec/use_execve.c		\
		src/excec/execute_conf.c	\
		src/lexer/lexer.c			\
		src/lexer/token.c			\
		src/signal/signal.c			\
		src/expander/expander.c		\
		src/utils/exit.c			\
		src/utils/utils.c			\
		src/utils/rdir_utils.c		\
		src/utils/parser_utils.c	\
		src/utils/builtin_utils.c	\
		src/utils/signal_controller.c \

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
