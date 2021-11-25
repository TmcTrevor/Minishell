/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:08:35 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 12:37:02 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	n_digits(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	abss(char **c, long *i)
{
	int	flag;

	flag = 0;
	if (*i < 0)
	{
		*c[0] = '-';
		*i *= -1;
		flag = 1;
	}
	return (flag);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;
	int		j;
	int		flag;
	long	n2;

	i = 0;
	flag = 0;
	n2 = n;
	j = n_digits(n2);
	p = (char *)malloc((j + 1) * sizeof(char));
	if (!p)
		return (0);
	flag = abss(&p, &n2);
	p[j] = '\0';
	while (j-- > flag)
	{
		p[j] = n2 % 10 + '0';
		n2 /= 10;
	}
	return (p);
}
