/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 11:26:17 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/28 21:26:02 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../GNL/get_next_line.h"

/*typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}					char *;*/

typedef struct s_garbage
{
    void *garb;
    struct s_garbage *next;

} t_garbage;

typedef struct s_tools
{
    int fd[2];
    int read;
    int write;
    int *pid;
    int in;
    int i;
    int out;
} t_tools;

typedef struct s_redirect
{
    char *line;
    char *file;
    //char  **argument;
    int type;
    int flag;
    char **env;
    struct s_redirect *nextred;
} t_redirect;

typedef struct s_command
{
    char *cmd;
    char *fcmd;
    int t[300];
    int count;
    char **argument;
    char **fakearg;
    t_redirect *redirect;
    struct s_command *nextcmd;

} t_command;

typedef struct s_main
{
    char *line;
    char **env;
    char **files;
    int count;
    int t[300];
    t_command *cmd;

} t_main;

typedef enum e_norm
{
    GETEXIT,
    SETEXIT,
    GETPID,
    SETPID
} t_norm;

t_garbage *g;

/* ----------------------- libft / util --------------------------*/
void ft_putstr_fd(char *s, int fd);
char **ft_split(const char *str, char c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strnstr(const char *str, const char *to_find, size_t len);
char *ft_strjoin(char *s1, char *s2);
int ft_strlen(char *c);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strcpy(char *dest, char *src);
char *ft_strdup(char *src);
char **ft_split1(char const *s, char c);
char **strdjoin(int e, char **a, char **b);
char *ft_strchr(const char *s, int c);
char *ft_joinchar(char *a, char c);
char *ft_strcat(char *dest, char *src);
char **strdup2(char **b, int e);
char **strdup23(char **a, char *s);
char **strdup24(char **b);
int ft_strdlen(char **a);
int ft_isdigit(int c);
int ft_isalpha(int c);
int ft_strcmp(const char *s1, const char *s2);
char *ft_itoa(int n);
/*-------------------------- command list minupilation -----------------*/

t_command *new_stack(char *a);
int ft_lstsize1(t_command *lst);
void ft_lstadd_front1(t_command **alst, t_command *new);
void ft_lstadd_back1(t_command **alst, t_command *new);
t_command *delete_first(t_command *a);
/*---------------------------------------------------------------------*/

/*-------------------------- redirect list minupilation -----------------*/
t_redirect *new_stack_red(char *a, int i, char **env);
int ft_lstsize2(t_redirect *lst);
void ft_lstadd_front2(t_redirect **alst, t_redirect *new);
void ft_lstadd_back2(t_redirect **alst, t_redirect *new);
t_redirect *delete_first2(t_redirect *a);

/*------------------------- MINISHELL - parse---------------------------*/
int parse(t_main *main);
int check_quotes(char c, int open);
int check_quotes1(char c, int open);
int parse_redirection(t_command *cmd, char **env);
char *ignore_quotes(char *a, int c);
int env_init(t_main *main, char **env_array);
char **ignore_quotes1(char **s, char **env);
int check_next(char *c);
int redirect(t_command *cmd, int i, char **env);
int get_type(t_command *cmd, char **env);
int get_argv(t_command *cmd, char **env);
char **getter(t_redirect **red, int i, char c, char ***arg);
int check_eol(char *c, int type);
int sizedoublp(char **a);
void execute_here_doc(t_main *main);
char **strdup23(char **a, char *s);
char *sub_split(t_main *main, int i, int j);
int get_pipe(t_main *main, int *ope, int *j, int *i);
int check_piperror(t_main *main, int i);
int	exist(t_main *main);
/*-------------------------- MINISHELL -PARSE - HERE_DOC --------------------------------*/
char *ft_herdocs(char *str);
void ft_herdocs_rl(char *limiter, int fd);
/*------------------------ MINISHELL - PARSE - DOLLAR ------------------*/
int get_index(char *c, char w);
char *odd_dollar(char *s, int k, int *i);
char *even_dollar(char *s, char *res, int k, int i);
int skip_dollar(char *s, int *k, int i);
char *random_join(char *res, int a);
char *dollar_check(char *s, char **env);
char *dollar_small_case(char *s);
char *dollar_prefix(char *s, int *i, char *res, int open);
char *dollar_cases(char *res, char *s, char **env, int *i);
char *check_env(char *c, char *res, char **env);
char **helfer(t_redirect **red, char ***arg, int j);
char **arg_fill(t_redirect **red, char ***arg, int j);
char *join(char *a, char *c, int *open, int *i);
/*------------------------------ MINISHELL - exec ----------------------*/
int non_builtin(t_command *cmd1, char **env);
int builtin(t_command *cmd1, char ***env);
int env_c(char **env);
int pwd(char **env);
void tools_init(int i, t_tools *tools);
void execute_pipe(t_tools *tools, t_command *cmd, char ***env);
void ft_free_tools(t_tools *tools);
void execute_lcmd(t_tools *tools, t_command *cmd, char ***env);
int check_option(char **args);
void all_waits(t_main *main, t_tools *tools);
char **delete_from_env(int sa, char *c, char **env);
char *ignore_loop(char *a, char *c);
char **strdup21(char **b);
char **fillc(char **c, char **a, char **b, int i);
char **fillb(char *s);
int ft_exit(char **args);
int	ft_simple(t_command *cmd, char ***env, t_tools *tools);
/*------------------------------ MINISHELL - exec 2 ----------------------*/
int echoo(char **args);
void error(char *c);
char *find_path(char *cmd, char *to_find, char **envp);
void cmd_call(t_command *cmd, char **envm);
void clear_all(t_main *main);
int execute(t_main *main);
char *find_path2(char *cmd, char **env);
char *find_path3(char *cmd, char **env);
char **delete_line(char **env, char *c);
int cd(char **cmd, char ***env);
int replace(char ***env, char *c, char *to_replace);
int export_unset(char **args, char ***env, int mode);
int check_syntax(char *arg);
int redirect_to(t_command *cmd, t_tools *tools);
int get_fo_index(char *c);
void add_quotes(char **my_env);
char **return_free(char **env, char **new_env);
int get_index1(char *c, char w, int open);
void assign(t_command *cmd, int *i, int *j);
/* Bonus functions */
int open_file(char *argv, int i);
void arg_err(void);
void check_cmd(char *inpt, char **cmd, char **envm);
/*-----------------------------------signals--------------------------------*/
void handle_sigint(int sigint);
int __get_var(t_norm op, int value);
void handle_sigint_herdoc(int sigint);
/*------------------------------------ MINISHELL FREE ----------------------*/
void free_cmd(t_main *main);
void free_redirect(t_command *cmd);
void free_argument(char **argument);
void clear_all(t_main *main);
int ft_error(char *c);
void ft_fres(char **b, int a);
void garbage(t_garbage **garbage, void *address);
int g_status_code;

#endif