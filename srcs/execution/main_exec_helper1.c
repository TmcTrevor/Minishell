/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec_helper1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbifenzi <mbifenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 02:20:46 by mbifenzi          #+#    #+#             */
/*   Updated: 2021/11/24 05:22:24 by mbifenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	all_waits(t_main *main, t_tools *tools)
{
	int	i;

	i = 0;
	while (i <= main->count)
	{
		waitpid(tools->pid[i], NULL, 0);
		i++;
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
			exit(0);
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
