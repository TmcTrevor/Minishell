NAME = minishell

SRCS =	srcs/cmd_utils.c \
		srcs/minishell.c \
		srcs/rebuilt_cmd.c \
		srcs/parse/parse.c \
		srcs/parse/parse_redirect.c \
		srcs/utils/manu_list.c \
		srcs/utils/manu_list_red.c \
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

OBJS 	= ${SRCS:.c=.o}
OBJS_LIBFT = ${LIBFT:.c=.o}

CC		= gcc

CFLAGS = -Wall -Werror -Wextra -g

.c.o:		%.o : %.c
				@gcc ${CFLAGS}  -c $< -o $(<:.c=.o)

$(NAME):	
			@$(CC) -lreadline ${SRCS} -o ${NAME}
			@echo "\033[32mPipex Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

all: $(NAME)
	


clean:
		@rm -f ${OBJS} 

fclean: 	clean
			@rm -f $(NAME)
			@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"
re : fclean all

.PHONY: all clean fclean re