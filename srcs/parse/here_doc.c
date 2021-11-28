/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:29:13 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/27 17:03:07 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_fress(char **b, int j)
{
	int	i;

	i = 0;
	if (b)
	{
		while (b[i] && i < j)
		{
			free(b[i]);
			b[i] = NULL;
			i++;
		}
	}
	free(b);
	b = NULL;
}

void	lunch_here_doc(t_main *main, char **tab, int j)
{
	int		i;
	char	*c;
	
	i = 0;
	while (i < j)
	{
		c = readline("here_doc > ");
		if (c)
		{
			if (!ft_strncmp(c, tab[i], ft_strlen(tab[i])))
				i++;
			else
				main->files = strdup23(main->files, c);
			free(c);
			c = NULL;
		}
	}
}

void	execute_here_doc(t_main *main)
{
	t_command	*cmd1;
	t_redirect	*red;
	char		**tab;
	int			j;
	
	cmd1 = main->cmd;
	j = 0;
	tab = NULL;
    while (cmd1)
    {
		red = cmd1->redirect;
		while (red)
		{
			if (red->type == 4)
			{
				tab = strdup23(tab, red->file);
				j++;
			}
			red = red->nextred;
		}
		cmd1 = cmd1->nextcmd;
	}
	if (j > 0)
		lunch_here_doc(main, tab,j);
	ft_fress(tab, j);
}

int	get_index1(char *c, char w, int open)
{
	int	i;

	i = 1;
	if (open == 1)
		w = '\'';
	while (c[i])
	{
		if (c[i] == w)
			return (i);
		i++;
	}
	return (-1);
}
