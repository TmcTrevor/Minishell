/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:01:39 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/05 10:12:18 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		sizedoublp(char **a)
{
	int i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}
char	**arg_fill(t_redirect **red, char ***arg, int j)
{
	char **a;
	
	a = ft_split1((*red)->line + j, ' ');
	(*red)->file = ft_strdup(ignore_quotes(a[0], 0));
	free(a[0]);
	a[0] = NULL;
	*arg = a;
	a++;
	if (sizedoublp(a) > 0)
		return (a);
	return (NULL);
}

char	**getter(t_redirect **red, int i, char c, char ***arg)
{
	char **a;

	int j;
	
	j = 1;
	a = NULL;
	if ((*red)->line[1] == '>' || (*red)->line[1] == '<')
		j = 2;
	if (i == 0 && (c== '>' || c == '<'))
	{
		(*red)->flag = 1;
		return (arg_fill(red, arg, j));
	}
	else
	{
		if (((*red)->line[0] == '>' || (*red)->line[0] == '<'))
		{
			(*red)->flag = 0;
			return (arg_fill(red, arg, j));
		}
		else
		{
			(*red)->file = ft_strdup("");
			a = ft_split1((*red)->line, ' ');
			return (a);
		}
	}
	return (0);
}

void	ft_fres1(char **b)
{
	int i;

	i = 0;
	while (b[i])
	{
		free(b[i]);
		b[i] = NULL;
		i++;
	}
	free(b);
	b = NULL;
}

int		get_argv(t_command *cmd, t_env *env)
{
	int i;
	char **b;
	t_redirect *l;

	i = 0;
	cmd->fcmd = NULL;
	cmd->argument = NULL;
	l = cmd->redirect;
	b = NULL;
	while (i <= cmd->count)
	{
		if (cmd->cmd)
		{
			b = getter(&cmd->redirect, i, cmd->cmd[0], &cmd->fakearg);

			if (b)
				cmd->argument = ignore_quotes1(strdjoin(cmd->redirect->flag,cmd->argument, b), env);
			free(cmd->fakearg);
			cmd->fakearg = NULL;
			cmd->redirect = cmd->redirect->nextred;
			i++;
		}
	}
	cmd->fcmd = cmd->argument[0];
	cmd->redirect = l;
	return (1);
}
