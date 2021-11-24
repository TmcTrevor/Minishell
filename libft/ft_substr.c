/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:26:39 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/23 14:28:01 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*p;
	unsigned int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if (start > i)
		len = 0;
	i = 0;
	p = (char *)malloc(len + 1 * sizeof(char));
	garbage(&g,p);
	if (!p)
		return (NULL);
	while (len--)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}
