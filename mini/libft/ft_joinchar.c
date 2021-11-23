/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 09:07:20 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/23 14:23:43 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	half_join_char(char *s, char c, char **str)
{
	if (s == NULL)
	{
		*str = (char *)malloc(2);
		//garbage(g, );
		if (*str == NULL)
			return (0);
		str[0][0] = c;
		str[0][1] = '\0';
		return (1);
	}
	return (-1);
}

char	*ft_joinchar(char *s, char c)
{
	int		i;
	char	*str;
	int		r;

	i = 0;
	r = half_join_char(s, c, &str);
	if (r == 1)
		return (str);
	else if (r == 0)
		return (NULL);
	while (s[i])
		i++;
	str = (char *)malloc(i + 2);
	if (str == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	s = NULL;
	return (str);
}