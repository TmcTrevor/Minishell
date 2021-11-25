/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdup24.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:57:09 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 13:10:13 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**fillb(char *s)
{
	char **b;

	b = malloc(2 * sizeof(char));
	garbage(&g, b);
	b[0] = ft_strdup(s);
	b[1] = NULL;
	return (b);
}

char	**fillc(char **c, char **a, char **b, int i)
{
	c[i] = NULL;
	ft_fres(a, 1);
	ft_fres(b, 0);
	return (c);
}

char	**strdup24(char **b)
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