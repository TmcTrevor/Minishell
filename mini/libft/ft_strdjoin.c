/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:33:35 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/15 15:00:56 by mokhames         ###   ########.fr       */
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

char        **strdjoin(char **a, char **b)
{
    int		sa;
    int		sb;
   	int		sc;
	int		i;
    char	**c;
    

    sa = ft_strdlen(a);
    sb = ft_strdlen(b);
	sc = sa + sb;
	i = 0;
	if (!a)
		return NULL;
	if (!b)
		return a;
	c = (char **)malloc(sc + 1 * sizeof(char *));
	while (i < sc)
	{
		if (i < sa)
			c[i] = ft_strdup(a[i]);
		else
			c[i] = ft_strdup(b[i - sa]);
		i++;
	}
	c[i] = NULL;
	return c;
}
