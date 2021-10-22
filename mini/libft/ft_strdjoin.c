/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:33:35 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/22 12:47:46 by mokhames         ###   ########.fr       */
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

void	ft_fres(char **b)
{
	int i;

	i = 0;
	while (b[i])
	{
		free(b[i]);
		b[i] = NULL;
		i++;
	}
	//free(b);
	b = NULL;
}

char        **strdjoin(char **a, char **b)
{
    int		sa;
    int		sb;
   	int		sc;
	int		i;
    char	**c;
    
	//printf("s === %s\n", *b);
	if (!a)
		return b;
	if (!b)
		return a;
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
			c[i] = ft_strdup(b[i - sa]);
		i++;
	}
	
	c[i] = NULL;
	ft_fres(a);
	ft_fres(b);
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