/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 04:28:49 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 09:54:50 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**helfer(t_redirect **red, char	***arg, int j)
{
	char	**a;

	a = NULL;
	if (((*red)->line[0] == '>' || (*red)->line[0] == '<'))
	{
		(*red)->flag = 0;
		return (arg_fill(red, arg, j));
	}
	else
	{
		(*red)->file = ft_strdup("");
		a = ft_split1((*red)->line, ' ');
		(*red)->flag = 0;
		return (a);
	}
}

char	*ignore_loop(char *a, char *c)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (a[i])
	{
		open = check_quotes1(a[i], open);
		while (a[i] && !open)
		{
			open = check_quotes1(a[i], open);
			c = ft_joinchar(c, a[i]);
			i++;
		}
		if (open == 1 || open == 2)
			c = join(a, c, &open, &i);
	}
	return (c);
}

void	garbage(t_garbage **garbage, void *address)
{
	t_garbage	*new;

	new = (t_garbage *)malloc(sizeof(t_garbage));
	new->next = *(garbage);
	new->garb = address;
	*garbage = new;
}

char	**strdup21(char **b)
{
	int		i;
	int		j;
	char	**c;

	j = 0;
	if (!b)
		return (NULL);
	i = ft_strdlen(b);
	c = malloc((i + 1) * sizeof(char *));
	garbage(&g, c);
	while (j < i)
	{
		c[j] = ft_strdup(b[j]);
		j++;
	}
	c[i] = NULL;
	return (c);
}
