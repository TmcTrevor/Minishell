/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:01:39 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/20 12:02:21 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**getter(t_redirect **red, int i, char c, int *e)
{
    char **a;
    int j;
    j = 1;
    if ((*red)->line[1] == '>' || (*red)->line[1] == '<')
        j = 2;
	if (i == 0 && (c== '>' || c == '<'))
    {
        a = ft_split1((*red)->line + j, ' ');
        (*red)->file = ft_strdup(ignore_quotes(a[0]));
        a++;
        *e = 1; 
    }
    else
    {
		if (((*red)->line[0] == '>' || (*red)->line[0] == '<'))
		{
			a = ft_split1((*red)->line + j, ' ');
			(*red)->file = ft_strdup(ignore_quotes(a[0]));
			a++;
            *e = 2;
		}
		else
		{
            (*red)->file = ft_strdup("");
			a = ft_split1((*red)->line, ' ');
			*e = 3;
		}
    }
    return a;
}

int		get_argv(t_command *cmd, t_env *env)
{
	int i;
    int c;
    char **a;
    char **b;
	int j;
    int k;
    t_redirect *l;

	i = 0;
    k = 0;
    c = 0;
	j = 0;
    a = NULL;
    l = cmd->redirect;
	while (i <= cmd->count)
	{
		b = getter(&cmd->redirect, i, cmd->cmd[0], &c);
        j = 0;
        cmd->argument = ignore_quotes1(strdjoin(cmd->argument, b), env);
        cmd->redirect = cmd->redirect->nextred;
		i++;
	}
    cmd->fcmd = cmd->argument[0];
    cmd->argument++;
    cmd->redirect = l;
    //printf("line = %s\n",cmd->redirect->line);
	return (1);
}