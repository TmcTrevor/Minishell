/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 11:26:17 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/18 03:50:52 by mokhames         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../GNL/get_next_line.h"

/*typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}					char *;*/
typedef struct s_tools
{
    int fd[2];
    int *pid;
    int in;
    int i;
    int out;
}   t_tools;

typedef struct s_redirect
{
        char	*line;
        char	*file;
       //char  **argument;
        int     type;
        int		flag;
        struct	s_redirect *nextred;
}               t_redirect;

typedef struct  s_command
{
        char    			*cmd;
        char    			*fcmd;
		int					t[300];
        int 				count;
        char 				**argument;
        char		        **fakearg;
        t_redirect  		*redirect;
        struct s_command	*nextcmd;
        
}               t_command;

typedef struct	s_main
{
	char			*line;
    char            **env;
    char		    **files;
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
char		**ft_split1(char const *s, char c);
char		**strdjoin(int e, char **a, char **b);
char		*ft_strchr(const char *s, int c);
char		*ft_joinchar(char *a, char c);
char		*ft_strcat(char *dest, char *src);
char		**strdup2(char **b, int e);
char		**strdup23(char **a, char *s);
int			ft_strdlen(char **a);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int		ft_strcmp(const char *s1, const char *s2);
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
int			check_quotes1(char c, int open);
int			parse_redirection(t_command *cmd, char * *env);
char		*ignore_quotes(char *a, int c);
int			env_init(t_main *main, char **env_array);
char		**ignore_quotes1(char **s, char * *env);
int			check_next(char *c);
int			redirect(t_command *cmd, int i);
int			get_type(t_command *cmd);
int			get_argv(t_command *cmd, char * *env);
char		**getter(t_redirect **red, int i, char c, char ***arg);
int			check_eol(char *c, int type);
int			sizedoublp(char **a);
void		execute_here_doc(t_main *main);
char		**strdup23(char **a, char *s);
/*------------------------ MINISHELL - PARSE - DOLLAR ------------------*/
int			get_index(char *c, char w);
char		*odd_dollar(char *s, int k, int *i);
char		*even_dollar(char *s, char *res, int k, int i);
int			skip_dollar(char *s, int *k, int i);
char		*random_join(char *res, int a);
char		*dollar_check(char *s, char * *env);
char		*dollar_small_case(char *s);
char		*dollar_prefix(char *s, int *i, char *res, int open);
char		*dollar_cases(char *res, char *s, char * *env, int *i);
char		*check_env(char *c, char *res, char * *env);
/*------------------------------ MINISHELL - exec ----------------------*/
void		error(char *c);
char		*find_path(char *cmd, char *to_find, char **envp);
void		cmd_call(t_command *cmd, char **envm);
void		clear_all(t_main *main);
int			execute(t_main *main);
char		*find_path2(char *cmd, char **env);
char        *find_path3(char *cmd, char **env);
char		**delete_line(char **env, char *c);
int			cd(char **cmd, char ***env);
int         replace(char ***env, char *c, char *to_replace);
int			export_unset(char **args, char ***env, int mode);
int			check_syntax(char *arg);
/* Bonus functions */
int			open_file(char *argv, int i);
void		arg_err(void);
void		check_cmd(char *inpt, char **cmd, char **envm);

/*------------------------------------ MINISHELL FREE ----------------------*/
void        free_cmd(t_main *main);
void        free_redirect(t_command *cmd);
void        free_argument(char **argument);
void        clear_all(t_main *main);
int			ft_error(char *c);
void        ft_fres(char **b, int a);

int			g_status_code;

#endif