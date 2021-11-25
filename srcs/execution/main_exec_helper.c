/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 02:18:16 by mbifenzi          #+#    #+#             */
/*   Updated: 2021/11/25 14:56:40 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(char **env)
{
	char	*pwd;

	(void)env;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		free(pwd);
		pwd = NULL;
		__get_var(SETEXIT, 0);
	}
	else
		g_status_code = 130;
	return (1);
}

int	env_c(char **env)
{
	int	i;

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
	__get_var(SETEXIT, 0);
	return (1);
}

int	builtin(t_command *cmd1, char ***env)
{
	char	*cmd;

	cmd = cmd1->fcmd;
	if (!cmd)
		return (0);
	if (!ft_strcmp("echo", cmd))
		return (echoo(cmd1->argument));
	else if (!ft_strcmp("exit", cmd))
		exit(0);
	else if (!ft_strcmp("cd", cmd))
		return (cd(cmd1->argument, env));
	if (!ft_strcmp("pwd", cmd))
		return (pwd(*env));
	else if (!ft_strcmp("export", cmd))
		return (export_unset(cmd1->argument, env, 1));
	else if (!ft_strcmp("unset", cmd))
		return (export_unset(cmd1->argument, env, 2));
	if (!ft_strcmp("env", cmd))
		return (env_c(*env));
	return (0);
}

int	non_builtin(t_command *cmd1, char **env)
{
	if (*cmd1->fcmd)
		cmd_call(cmd1, env);
	return (1);
}

void	execute_pipe(t_tools *tools, t_command *cmd, char ***env)
{
	if (pipe(tools->fd) == -1)
		write(1, "error\n", 7);
	tools->pid[tools->i] = fork();
	if (tools->pid[tools->i] == -1)
		write(1, "error\n", 7);
	if (tools->pid[tools->i] == 0)
	{
		close(tools->fd[0]);
		dup2(tools->fd[1], 1);
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
	}
}
