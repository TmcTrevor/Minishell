/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:19:55 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/04 12:35:34 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_argument(char **argument)
{
	int i;

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

void	free_cmd(t_main *main)
{
	t_command *c;

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
	t_redirect *r;

	if (cmd->redirect)
	{
		while(cmd->redirect)
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
			cmd->redirect = cmd->redirect->nextred; 
			free(r);
			r = NULL;
		}
	}
}

void    clear_all(t_main *main)
{
	t_env *v;

	free_cmd(main);
	while (main->env)
	{
		v = main->env;
		free(main->env->value);
		main->env->value = NULL;
		main->env = main->env->next;
		//free_argument(main->files);
		free(v);
		v = NULL;
	}
}