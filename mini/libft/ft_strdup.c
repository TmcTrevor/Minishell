/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:50:29 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/29 20:12:28 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
		i++;
	dest = (char *)malloc((i + 1) * sizeof(char));
	if (!dest)
		return (0);
	ft_strcpy(dest, src);
	return (dest);
}
