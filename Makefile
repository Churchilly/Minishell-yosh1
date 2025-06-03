CC				= cc
CFLAGS			= -Wall -Wextra -Werror
LDFLAGS			= -lreadline
NAME			= minishell

MANDATORY_DIR 		= source

SOURCE			=	builtin_cd.c \
					builtin_echo.c \
					builtin_env_unset_pwd.c \
					builtin_execute.c \
					builtin_exit.c \
					builtin_export.c \
					enviroment_memory.c \
					environment_functions.c \
					environment_mirror.c \
					environment_setup.c \
					environment.c \
					executer_command.c \
					executer_path_finder.c \
					executer_pipe.c \
					executer_redirection.c \
					executer.c \
					expand_dollar_divide_alloc.c \
					expand_dollar_divide.c \
					expand_dollar_env.c \
					expand_dollar_in_dquote.c \
					expand_dollar_in_dquote_env.c \
					expand_dollar_replace.c \
					expand_dollar.c \
					expand_quotes.c \
					expand_tilde.c \
					expander_checkers.c \
					expander.c \
					ft_atoi.c \
					ft_itoa.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_strjoin.c \
					ft_strndup.c \
					ft_substr.c \
					ft_split.c \
					garbage_collector_clear.c \
					garbage_collector.c \
					heredoc_document_utils.c \
					heredoc_document.c \
					heredoc_env_utils.c \
					heredoc_env.c \
					heredoc_pipe.c \
					heredoc_signals.c \
					heredoc_utils.c \
					heredoc.c \
					lexer_tokenizer.c \
					lexer_utils.c \
					lexer.c \
					main_checkers.c \
					main.c \
					parse_command.c \
					parse_pipe.c \
					parse_redirect.c \
					parser.c \
					pointer_storage.c \
					safe_fork.c \
					safe_open.c \
					signals.c \
					str_functions.c
SRC				= $(addprefix $(MANDATORY_DIR)/, $(SOURCE))
OBJ				= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re