/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:19:55 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 09:46:07 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_argument(char **argument)
{
	int		i;

	i = -1;
	if (argument)
	{
		while (argument[++i])
		{
			free(argument[i]);
			argument[i] = NULL;
		}
		free(argument);
		argument = NULL;
	}
}

void	free_argument1(char **argument)
{
	int	i;

	i = -1;
	if (argument)
	{
		while (argument[++i])
		{
			free(argument[i]);
			argument[i] = NULL;
		}
		argument = NULL;
	}
}

void	free_cmd(t_main *main)
{
	t_command	*c;

	if (main->cmd)
	{
		while (main->cmd)
		{
			c = main->cmd;
			free_redirect(main->cmd);
			free_argument(main->cmd->argument);
			if (main->cmd->cmd)
			{
				free(main->cmd->cmd);
				main->cmd->cmd = NULL;
			}
			main->cmd = main->cmd->nextcmd;
			free(c);
			c = NULL;
		}
	}
}

void	free_redirect(t_command *cmd)
{
	t_redirect	*r;

	if (cmd->redirect)
	{
		while (cmd->redirect)
		{
			r = cmd->redirect;
			if (cmd->redirect->line)
			{
				free(cmd->redirect->line);
				cmd->redirect->line = NULL;
			}
			if (cmd->redirect->file)
			{
				free (cmd ->redirect->file);
				cmd->redirect->file = NULL;
			}
			free_argument(cmd->redirect->env);
			cmd->redirect = cmd->redirect->nextred;
			free(r);
			r = NULL;
		}
	}
}

void	clear_all(t_main *main)
{
	int	i;

	i = 0;
	free_cmd(main);
}
