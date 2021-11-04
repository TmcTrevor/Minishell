/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:33:35 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/04 10:43:55 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_strdlen(char **a)
{
	int i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

void	ft_fres(char **b, int a)
{
	int i;

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
	//b = NULL;
	if (a == 1)
		free(b);
	b = NULL;
}
char		**strdup23(char **a, char *s)
{	
	int 	i;
	int 	sa;
	char	**b;
	
	i = 0;
	if (a == NULL)
	{
		b = malloc(2 * sizeof(char **));
		b[0] = ft_strdup(s);
		b[1] = NULL;
	}
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

char		**strdup2(char **b, int e)
{
	int i;
	int j;
	char **c;

	j = 0;
	if (!b)
		return NULL;
	i = ft_strdlen(b);
	c = malloc((i + 1)* sizeof(char *));
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

char        **strdjoin(int e, char **a, char **b)
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
	while (i < sc)
	{
		if (i < sa)
			c[i] = ft_strdup(a[i]);
		else
			c[i] = ft_strdup(b[i  - sa]);
		i++;
	}
	c[i] = NULL;
	ft_fres(a, 1);
	ft_fres(b, 0);
	return c;
}

// int main(int ac, char **av)
// {
// 	char **c = NULL;
// 	char **b;
// 	int i = 0;
// 	while (i < 9)
// 	{
// 		b = ft_split(av[1], ' ');
// 		c = strdjoin(c,b);
// 		i++;
// 	}
// 	i = 0;
// 	while (c[i])
// 	{
// 		printf("c[%d] = %s\n",i, c[i]);
// 		i++;
// 	}
// }