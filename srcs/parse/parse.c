/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 08:05:59 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/28 17:24:18 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_pipe(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	main->cmd = NULL;
	while (i <= main->count)
	{
		ft_lstadd_back1(&main->cmd, new_stack(sub_split(main, i, j)));
		j = main->t[i] + 1;
		i++;
	}
}

int	check_piperror(t_main *main, int i)
{
	int e;

	e = i;
	while (main->line[i + 1] == ' ')
	{
		if (main->line[i + 2] == '\0' && e == -1)
			return (2);
		i++;
	}
	if (main->line[i + 1] == '|')
		return (0);
	if (main->line[i + 1] == '\0')
		return (0);
	return (1);
}

int	parse_pipes(t_main *main)
{
	int	i;
	int	open;
	int	j;

	i = 0;
	open = 0;
	j = 0;
	main->count = 0;
	if (!get_pipe(main, &open, &j, &i))
		return (0);
	if (open != 0)
	{
		write(2, "NOT closed ARE NOT IN SUBJECT\n", 31);
		return (0);
	}
	main->t[j] = i + 1;
	split_pipe(main);
	return (1);
}

int	numb_of_quotes(char *c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (c[i])
	{
		if (c[i] == '\'')
			j++;
		if (c[i] == '\"')
			k++;
		i++;
	}
	if (j % 2 != 0 || k % 2 != 0)
		return (-1);
	return (1);
}

int	exist(t_main *main)
{
	t_command	*cmd;
	t_redirect	*red;

	cmd = main->cmd;
	while (cmd)
	{
		red = cmd->redirect;
		while (red)
		{
			if (red->type == 4)
				return (1);
			red = red->nextred;
		}
		cmd = cmd->nextcmd;
	}
	return (0);
}

int	parse(t_main *main)
{
	int	i;

	i = 0;
	if (!*main->line)
		return (0);
	i = check_piperror(main, -1);
	if (!i)
	{
		write(2, "syntax error\n", 14);
		return (0);
	}
	if (i == 2)
		return (0);
	if (!parse_pipes(main))
		return (0);
	if (!parse_redirection(main->cmd, main->env))
		return (0);
	return (1);
}
