/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 03:02:23 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 03:58:37 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	assign(t_command *cmd, int *i, int *j)
{
	if ((*i) != 0)
	{
		cmd->t[(*j)] = (*i);
		cmd->count++;
		(*j)++;
	}
	while (cmd->cmd[(*i) + 1] == '<' || cmd->cmd[(*i) + 1] == '>')
				(*i)++;
}

int	check_quotes(char c, int open)
{
	if (c == '\'')
	{
		if (open == 1)
			open = 0;
		else
			open = 1;
	}
	if (c == '\"')
	{
		if (open == 2)
			open = 0;
		else
			open = 2;
	}
	return (open);
}

int	check_quotes1(char c, int open)
{
	if (c == '\'')
	{
		if (open == 1)
			open = 0;
		else if (open != 2)
			open = 1;
	}
	if (c == '\"')
	{
		if (open == 2)
			open = 0;
		else if (open != 1)
			open = 2;
	}
	return (open);
}

char	*sub_split(t_main *main, int i, int j)
{
	char	*c;

	while (main->line[j] == ' ')
		j++;
	c = ft_substr(main->line, j, main->t[i] - j);
	return (c);
}

int	get_pipe(t_main *main, int *ope, int *j, int *i)
{
	int	open;

	open = 0;
	while (main->line[*i])
	{
		open = check_quotes1(main->line[*i], open);
		if (main->line[*i] == '|' && !open)
		{
			if (!(check_piperror(main, *i)))
			{
				write(2, "syntax error\n", 14);
				return (0);
			}
			main->t[*j] = *i;
			main->count++;
			(*j)++;
		}
		(*i)++;
	}
	*ope = open;
	return (1);
}
