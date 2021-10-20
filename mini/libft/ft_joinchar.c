/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 09:07:20 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/20 14:09:35 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *ft_joinchar(char *a, char c)
{
    int i;
	char *b;

	i = 0;
	//printf("c in join = %c\n",c);
	while (a[i])
		i++;
	b = malloc((i + 1) * sizeof(char));
	ft_strcpy(b,a);
	b[i] = c;
	b[i + 1] = '\0';
	return (b);
}


/*int main()
{
	char *a = "\'e\"ch\"o\'";
	//char c = '7';
	//char *q = ft_joinchar(a,c);
	//printf("%s\n",ignore_quotes(a));
}*/