/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:16:45 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/02 10:18:46 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_index(char *c, char w)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == w || c[i] == ' ' || c[i] == '\'' || c[i] == '\"')
			return (i);
		i++;
	}
	return (-1);
}

char	*odd_dollar(char *s, int k, int *i)
{
	int		j;
	char	*res;

	j = get_index(s + (*i) + k, '$');
	if (j == -1)
		j = ft_strlen(s + (*i));
	res = ft_substr(s + (*i), 0, j);
	(*i) += j;
	return (res);
}

char	*even_dollar(char *s, char *res, int k, int i)
{
	int	j;
	int	a;

	a = k;
	while (a-- > 1)
		res = ft_joinchar(res, '$');
	j = get_index(s + (i) + k, '$');
	if (j == -1)
		j = ft_strlen(s + (i));
	return (res);
}

int	skip_dollar(char *s, int *k, int i)
{
	int	a;

	a = 0;
	while (s[(i)] == '$')
	{
		a++;
		(*k)++;
		i++;
	}
	if (a % 2 == 0)
		return (1);
	return (0);
}

char	*random_join(char *res, int a)
{
	int	e;

	e = a;
	while (a-- > 1)
		res = ft_joinchar(res, '$');
	return (res);
}
