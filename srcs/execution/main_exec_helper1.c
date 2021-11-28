/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec_helper1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 02:20:46 by mbifenzi          #+#    #+#             */
/*   Updated: 2021/11/28 21:26:37 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	all_waits(t_main *main, t_tools *tools)
{
	int	i;
	int stat;

	i = 0;
	while (i <= main->count)
	{
		waitpid(tools->pid[i], &stat, 0);
		i++;
	}
	if (i > 1)
	{
		if (WIFEXITED(stat))
			__get_var(SETEXIT, WEXITSTATUS(stat));
		else if (WIFSIGNALED(stat))
		{
			__get_var(SETEXIT, WTERMSIG(stat) + 128);
			if (WTERMSIG(stat) == SIGQUIT)
				write(2, "QUIT\n", 6);
		}
	}
}

void	execute_lcmd(t_tools *tools, t_command *cmd, char ***env)
{
	tools->pid[tools->i] = fork();
	if (tools->pid[tools->i] == 0)
	{
		if (cmd->redirect)
			redirect_to(cmd, tools);
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
