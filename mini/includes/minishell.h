/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 11:26:17 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/02 20:26:53 by mokhames         ###   ########.fr       */
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
        char                **fakearg;
        t_redirect  		*redirect;
        struct s_command	*nextcmd;
        
}               t_command;

typedef struct	s_main
{
	char			*line;
    t_env			*env;
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
char        *ft_joinchar(char *a, char c);
char		*ft_strcat(char *dest, char *src);
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
int			parse_redirection(t_command *cmd, t_env *env);
char		*ignore_quotes(char *a, int c);
char		*dollar_check(char *c, char *s, t_env *env);
int			env_init(t_main *main, char **env_array);
char        **ignore_quotes1(char **s, t_env *env);
int         check_next(char *c);
int			redirect(t_command *cmd, int i);
int			get_type(t_command *cmd);
int			get_argv(t_command *cmd, t_env *env);
char		**getter(t_redirect **red, int i, char c, char ***arg);
int			check_eol(char *c, int type);
int         sizedoublp(char **a);
/*------------------------ MINISHELL - PARSE - DOLLAR ------------------*/
int         get_index(char *c, char w);
char        *odd_dollar(char *s, int k, int *i);
char        *even_dollar(char *s, char *res, int k, int i);
int         skip_dollar(char *s, int *k, int i);
char        *random_join(char *res, int a);
char        *dollar_check(char *c, char *s, t_env *env);
char        *dollar_small_case(char *c, char *s);
char        *dollar_prefix(char *s, int *i, char *res);
char        *dollar_cases(char *res, char *s, t_env *env, int *i);
char        *check_env(char *c, char *res, t_env *env);
/*------------------------------ MINISHELL - exec ----------------------*/
void		error(void);
char		*find_path(char *cmd, char **envp);
void		cmd_call(char *argv, char **envm);
void		clear_all(t_main *main);

/* Bonus functions */
int			open_file(char *argv, int i);
void		arg_err(void);
void		check_cmd(char *inpt, char **cmd, char **envm);

/*------------------------------------ MINISHELL FREE ----------------------*/
void        free_cmd(t_main *main);
void        free_redirect(t_command *cmd);
void        free_argument(char **argument);
void        clear_all(t_main *main);
int         ft_error(char *c);

#endif