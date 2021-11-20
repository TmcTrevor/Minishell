/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 08:05:59 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/20 02:04:36 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     check_quotes(char c, int open)
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
int     check_quotes1(char c, int open)
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

char    *sub_split(t_main *main, int i, int j)
{
	char *c;
	while (main->line[j] == ' ')
		j++;
	c = ft_substr(main->line, j, main->t[i] - j);
	return c;   
}

void    split_pipe(t_main *main)
{
	int i;
	int j;

	i = 0;
	j = 0;
	main->cmd = NULL;
	while (i <= main->count)
	{
		ft_lstadd_back1(&main->cmd,new_stack(sub_split(main,i,j)));
		j = main->t[i] + 1;
		i++;
	}
}

int		check_piperror(t_main *main, int i)
{
	while (main->line[i + 1] == ' ')
		i++;
	if (main->line[i + 1] == '|')
		return (0);
	if (main->line[i + 1] == '\0')
		return (0);
	return (1);		
}
int    parse_pipes(t_main *main)
{
	int i;
	int open;
	int j;

	i = 0;
	open = 0;
	j = 0;
	main->count = 0;
	while (main->line[i])
	{
		open = check_quotes1(main->line[i], open);
		//printf("open = %d\n", open);
		if (main->line[i] == '|' && !open)
		{
			if (!(check_piperror(main, i)))
			{
				write(1, "syntax error\n", 14);
				return (0);
			}
			main->t[j] = i;
			main->count++;
			j++;
		}
		i++;
		
	}
	if (open != 0)
	{
		write(1, "NOT closed ARE NOT IN SUBJECT\n",31);
		return (0);
	}
	main->t[j] = i + 1;
	split_pipe(main);
	return (1);
}
int     numb_of_quotes(char *c)
{
	int i;
	int j;
	int k;

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

int	parse(t_main *main)
{
	int i;

	i = 0;
	if (!*main->line)
		return (0);
	if (!check_piperror(main,-1))
	{
		write(1, "syntax error\n", 14);
		return (0);
	}
	
	if (!parse_pipes(main))
		return (0);
	if (!parse_redirection(main->cmd, main->env))
		return (0);
	//execute_here_doc(main);
	i = 0;
	/*while (main->files[i])
	{
		printf("%s\n", main->files[i]);
		i++;
	}*/
	
	return (1);
}
