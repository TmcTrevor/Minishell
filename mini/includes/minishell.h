/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 11:26:17 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/11 09:28:12 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_redirect
{
        char	*line;
        char	*file;
       //char  **argument;
        int     type;
        struct	s_redirect *nextred;
}               t_redirect;

typedef struct  s_command
{
        char    			*cmd;
        char    			*fcmd;
		int					t[300];
        int 				count;
        char 				**argument;
        t_redirect  		*redirect;
        struct s_command	*nextcmd;
        
}               t_command;

typedef struct	s_main
{
	char			*line;
    t_env			*env;
	t_env			*secret_env;
    int				count;
    int				t[300];
    t_command       *cmd;

}				t_main;



/* ----------------------- libft util --------------------------*/
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(const char *str, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(char *c);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strdup(char *src);

/*-------------------------- command list minupilation -----------------*/

t_command	*new_stack(char *a);
int			ft_lstsize1(t_command *lst);
void		ft_lstadd_front1(t_command **alst, t_command *new);
void		ft_lstadd_back1(t_command **alst, t_command *new);
t_command	*delete_first(t_command *a);
/*---------------------------------------------------------------------*/

/*-------------------------- redirect list minupilation -----------------*/
t_redirect	*new_stack_red(char *a, int i);
int			ft_lstsize2(t_redirect *lst);
void		ft_lstadd_front2(t_redirect **alst, t_redirect *new);
void		ft_lstadd_back2(t_redirect **alst, t_redirect *new);
t_redirect	*delete_first2(t_redirect *a);

/*------------------------- MINISHELL - parse---------------------------*/
int			parse(t_main *main);
int			check_quotes(char c, int open);
int			parse_redirection(t_command *cmd);
/*------------------------------ MINISHELL - exec ----------------------*/
void		error(void);
char		*find_path(char *cmd, char **envp);
void		cmd_call(char *argv, char **envm);

/* Bonus functions */
int			open_file(char *argv, int i);
void		arg_err(void);
void		check_cmd(char *inpt, char **cmd, char **envm);

#endif