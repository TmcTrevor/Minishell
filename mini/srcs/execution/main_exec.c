/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:39:02 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/23 12:07:49 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_option(char **args)
{
	if (!ft_strncmp(args[1], "-n", 2))
		return (2);
	return (1);
}

int echoo(char **args)
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

char *find_path2(char *cmd, char **env)
{
	int i;
	int sa;
	int scmd;
	char *path;

	i = 0;
	sa = ft_strdlen(env);
	scmd = ft_strlen(cmd);
	while (ft_strcmp(env[i], cmd) && i < sa)
		i++;
	if (i == sa)
		return (NULL);
	else if (ft_strchr(env[i], '='))
		path = ft_strdup(env[i] + scmd + 1);
	else
		path = ft_strdup(cmd);
	return (path);
}

char *find_path3(char *cmd, char **env)
{
	int i;
	int sa;
	int scmd;
	char *path;

	i = 0;
	sa = ft_strdlen(env);
	scmd = ft_strlen(cmd);
	while (ft_strncmp(env[i], cmd, ft_strlen(cmd)) && i < sa)
		i++;
	if (i == sa)
		return (NULL);
	else if (ft_strchr(env[i], '='))
		path = ft_strdup(env[i] + scmd + 1);
	else
		path = ft_strdup(cmd);
	return (path);
}

int pwd(char **env)
{
	(void)env;
	char *pwd;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		free(pwd);
		pwd = NULL;
		g_status_code = 0;
	}
	else
		g_status_code = 1;
	return (1);
}

int env_c(char **env)
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
	//write(1, env[i], ft_strlen(env[i]));
	return (1);
}

int builtin(t_command *cmd1, char ***env)
{
	char *cmd;

	cmd = cmd1->fcmd;
	//printf("|%s|\n", cmd);
	if (!cmd)
		return (0);
	if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
		return (echoo(cmd1->argument));
	else if (!ft_strncmp("exit", cmd, ft_strlen(cmd)))
		exit(0);
	else if (!ft_strncmp("cd", cmd, ft_strlen(cmd)))
		return (cd(cmd1->argument, env));
	if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
		return (pwd(*env));
	else if (!ft_strncmp("export", cmd, ft_strlen(cmd)))
		return (export_unset(cmd1->argument, env, ft_strlen(cmd)));
	else if (!ft_strncmp("unset", cmd, ft_strlen(cmd)))
		return (export_unset(cmd1->argument, env, ft_strlen(cmd)));
	if (!ft_strncmp("env", cmd, ft_strlen(cmd)))
		return (env_c(*env));
	return (0);
}

int non_builtin(t_command *cmd1, char **env)
{
	/*pid_t pid;
	if (!cmd1->argument[0])
		return (0);
	pid = fork();
	if (pid == 0)*/
//	printf("%s")
	if (*cmd1->fcmd)
		cmd_call(cmd1, env);
	//	waitpid(pid, NULL, 0);
	return (1);
}

void tools_init(int i, t_tools *tools)
{
	//(void)i;
	tools->i = 0;
	tools->in = -1;
	tools->out = -1;
	//tools->read = dup(0);
	//tools->write = dup(1);
	tools->pid = (int *)malloc((i + 1) * sizeof(int));
}

void execute_pipe(t_tools *tools, t_command *cmd, char ***env)
{
	if (pipe(tools->fd) == -1)
		write(1, "error\n", 7);
	tools->pid[tools->i] = fork();
	if (tools->pid[tools->i] == -1)
		write(1, "error\n", 7);

	///child
	if (tools->pid[tools->i] == 0)
	{
		close(tools->fd[0]);
		dup2(tools->fd[1], 1);
		//	close(tools->write);
		close(tools->fd[1]);
		if (cmd->redirect)
			redirect_to(cmd, tools);
		if (builtin(cmd, env))
			exit(0);
		else
			non_builtin(cmd, *env);
	}
	else
	{
		close(tools->fd[1]);
		dup2(tools->fd[0], 0);
		close(tools->fd[0]);
		//wait(NULL);
	}
}

void execute_lcmd(t_tools *tools, t_command *cmd, char ***env)
{
	tools->pid[tools->i] = fork();
	if (tools->pid[tools->i] == 0)
	{
		if (cmd->redirect)
			redirect_to(cmd, tools);
		if (builtin(cmd, env))
			exit(0);
		else
			non_builtin(cmd, *env);
	}
	//wait(NULL);
}

void	ft_free_tools(t_tools *tools)
{
	free(tools->pid);
	tools->pid = NULL;
	free(tools);
	tools = NULL;
		
}

int execute(t_main *main)
{
	t_command *cmd1;
	t_tools *tools;
	int i;
	int in;
	int out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	
	i = 0;
	tools = malloc(sizeof(t_tools));
	tools_init(main->count, tools);
	cmd1 = main->cmd;
	if (!cmd1->nextcmd && builtin(cmd1, &main->env))
		return (0);
	while (cmd1->nextcmd)
	{
		
		execute_pipe(tools, cmd1, &main->env);
		tools->i++;
		cmd1 = cmd1->nextcmd;
	}
	execute_lcmd(tools, cmd1, &main->env);
	tools->i++;
	while (i <= main->count)
	{
		waitpid(tools->pid[i], NULL, 0);
		i++;
	}
	dup2(in, 1);
	dup2(out, 0);
	close(in);
	close(out);
	ft_free_tools(tools);
	return (1);
}