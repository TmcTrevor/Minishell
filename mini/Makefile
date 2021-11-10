NAME = minishell

SRCS =	srcs/cmd_utils.c \
		srcs/execution/main_exec.c \
		srcs/execution/cd.c \
		srcs/minishell.c \
		srcs/parse/parse.c \
		srcs/parse/parse_redirect.c \
		srcs/parse/redir_arg.c \
		srcs/parse/here_doc.c \
		srcs/parse/redir_type.c \
		srcs/parse/quotes_manu.c \
		srcs/parse/dollar.c \
		srcs/parse/dollar_util.c \
		srcs/env/env.c \
		srcs/env/delete.c \
		srcs/utils/manu_list.c \
		srcs/utils/manu_list_red.c \
		srcs/utils/free.c \
		libft/ft_split.c \
		libft/ft_split_advanced.c \
		libft/ft_strjoin.c \
		libft/ft_strdjoin.c \
		libft/ft_strlcpy.c \
		libft/ft_strncmp.c \
		libft/ft_strnstr.c \
		libft/ft_strdup.c \
		libft/ft_strcpy.c \
		libft/ft_substr.c \
		libft/ft_strchr.c \
		libft/ft_joinchar.c \
		libft/ft_strcat.c \
		GNL/get_next_line.c \

OBJS 	= ${SRCS:.c=.o}
OBJS_LIBFT = ${LIBFT:.c=.o}

CC		= gcc

CFLAGS = -Wall -Werror -Wextra -g

.c.o:		%.o : %.c
				@gcc ${CFLAGS}  -c $< -o $(<:.c=.o)

$(NAME):	
			@$(CC) $(CFLAGS) -lreadline ${SRCS} -o ${NAME} -fsanitize=address -g
			@echo "\033[32mPipex Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

all: $(NAME)
	


clean:
		@rm -f ${OBJS} 

fclean: 	clean
			@rm -f $(NAME)
			@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"
re : fclean all

.PHONY: all clean fclean re