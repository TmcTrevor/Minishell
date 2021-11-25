/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:33:35 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 13:08:04 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strdlen(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

void	ft_fres(char **b, int a)
{
	int	i;

	i = 0;
	if (b)
	{
		while (b[i])
		{
			free(b[i]);
			b[i] = NULL;
			i++;
		}
	}
	if (a == 1)
		free(b);
	b = NULL;
}

char	**strdup23(char **a, char *s)
{	
	int		i;
	int		sa;
	char	**b;

	i = 0;
	if (a == NULL)
		b = fillb(s);
	else
	{
		sa = ft_strdlen(a);
		b = malloc((sa + 2) * sizeof(char **));
		while (i < sa)
		{
			b[i] = ft_strdup(a[i]);
			i++;
		}
		b[i++] = ft_strdup(s);
		b[i] = NULL;
	}
	ft_fres(a, 1);
	return (b);
}

char	**strdup2(char **b, int e)
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
	if (e == 0)
		ft_fres(b, 1);
	else
		ft_fres(b, 0);
	return (c);
}

char	**strdjoin(int e, char **a, char **b)
{
	int		sa;
	int		sb;
	int		sc;
	int		i;
	char	**c;

	if (!a)
		return (strdup2(b, e));
	if (!b)
		return (strdup2(a, e));
	sa = ft_strdlen(a);
	sb = ft_strdlen(b);
	sc = sa + sb;
	i = 0;
	c = (char **)malloc((sc + 1) * sizeof(char *));
	garbage(&g, c);
	while (i < sc)
	{
		if (i < sa)
			c[i] = ft_strdup(a[i]);
		else
			c[i] = ft_strdup(b[i - sa]);
		i++;
	}
	return (fillc(c, a, b, i));
}
