/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:39:02 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/09 16:43:10 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_option(char **args)
{
	if(!ft_strncmp(args[1], "-n", 2))
		return (2);
	return (1);
}

int    echoo(char **args)
{
	int i;
	int e;
	int sa;
	
	sa = ft_strdlen(args);
	if (sa == 1)
		write(1, "\n", 1);		
	else if (sa >= 2)
	{
		i = check_option(args);
		e = i;
		while (args[i])
		{
			write(1, args[i], ft_strlen(args[i]));
			if (args[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		if (e == 1)
			write(1, "\n", 1);
	}
	return (1);
}


char	*find_path2(char *cmd, char **env)
{
	int 	i;
	int		sa;
	int		scmd;
	char 	*path;

	i = 0;
	sa = ft_strdlen(env);
	scmd = ft_strlen(cmd);
	while (ft_strnstr(env[i], cmd , scmd) == 0 && i < sa - 1)
		i++;
	if (i == sa)
		return NULL;
	else
		path = ft_strdup(env[i] + scmd + 1);
	return path;
}

int	cd(char **cmd)
{
	chdir(cmd[1]);
	return (1);
}
int 	pwd(char **env)
{
	(void)env;
	char *pwd;
	pwd = getcwd(NULL,0);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	g_status_code = 0;
	return (1);
}

int 	env_c(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (1);
}

int 	builtin(t_command *cmd1, char **env)
{
	
	/*if (*cmd == NULL)
		return ;*/
	(void)env;
	char *cmd;
	
	cmd = cmd1->fcmd; 
	// printf("|%s|\n", cmd);
    if (!ft_strncmp("echo",cmd,4))
		return (echoo(cmd1->argument));
	else if (!ft_strncmp("exit",cmd,4))
       exit(0);
	else if (!ft_strncmp("cd",cmd,4))
		return (cd(cmd1->argument));
	if (!ft_strncmp("pwd",cmd,4))
		return (pwd(env));
	else if (!ft_strncmp("search",cmd,6))
       return (printf("%s\n", find_path2("PWD",env)));
	/*else if (!ft_strncmp("unset",cmd,4))
			return (unset(env));*/
	if (!ft_strncmp("env",cmd,4))
        return (env_c(env));
	return (0);
}

int 	non_builtin(t_command *cmd1, char **env)
{
	pid_t pid;
	pid = fork();
	if (pid == 0)
		cmd_call(cmd1, env);
	waitpid(pid, NULL, 0);
	return (1);
}


int	execute(t_main *main)
{
	t_command *cmd1;
	cmd1 = main->cmd;
	while (cmd1)
	{
		if (!builtin(cmd1,main->env))
			non_builtin(cmd1, main->env);	
		cmd1 = cmd1->nextcmd;
	}
	return (1);
}