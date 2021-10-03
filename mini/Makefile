NAME = minishell

SRCS =	srcs/cmd_utils.c \
		srcs/minishell.c\
		srcs/rebuilt_cmd.c \
		libft/ft_split.c \
		libft/ft_strjoin.c \
		libft/ft_strlcpy.c \
		libft/ft_strncmp.c \
		libft/ft_strnstr.c \

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