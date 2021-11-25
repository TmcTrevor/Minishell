/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:36:35 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 12:36:06 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strcpy1(char *c, char *b, int *i)
{
	int	j;
	
	j = 0;
	while (b[j] != '\0')
	{
		c[*i] = b[j];
		(*i)++;
		j++;
	}
	return (c);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	tab = (char *)malloc(sizeof(*tab) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	garbage(&g,tab);
	if (tab == 0)
		return (NULL);
	tab = ft_strcpy1(tab, s1, &i);
	tab = ft_strcpy1(tab, s2, &i);
	tab[i] = '\0';
	return (tab);
}

int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}