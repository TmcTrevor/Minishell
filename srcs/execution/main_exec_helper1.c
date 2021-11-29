/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec_helper1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 02:20:46 by mbifenzi          #+#    #+#             */
/*   Updated: 2021/11/29 02:48:41 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	all_waits()
{
	int status;

	while (waitpid(-1, &status, 0) != -1);
	if (WIFEXITED(status))
		__get_var(SETEXIT, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		__get_var(SETEXIT, WTERMSIG(status) + 128);
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "QUIT\n", 7);
	}
}

void	execute_lcmd(t_tools *tools, t_command *cmd, char ***env)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmd->redirect)
			redirect_to(cmd, tools);
		if (__get_var(GETEXIT, 0) == -1)
		{
			__get_var(SETEXIT, 1);
			exit(1);
		}
		if (builtin(cmd, env))
		{
			__get_var(SETEXIT, 0);
			exit(0);
		}
		else
			non_builtin(cmd, *env);
	}
}

void	tools_init(int i, t_tools *tools)
{
	tools->i = 0;
	tools->in = -1;
	tools->out = -1;
	tools->pid = (int *)malloc((i + 1) * sizeof(int));
	garbage(&g, tools->pid);
}

void	ft_free_tools(t_tools *tools)
{
	free(tools->pid);
	tools->pid = NULL;
	free(tools);
	tools = NULL;
}

int	echoo(char **args)
{
	int	i;
	int	e;
	int	sa;

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
