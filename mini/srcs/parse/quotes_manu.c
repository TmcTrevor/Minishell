/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:57:19 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/29 19:48:17 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *ignore_quotes(char *a, int e)
{
	char *c;
	int i;
	int open;
	int j;

	i = 0;
	open = 0;
	j = 0;


	if (!ft_strchr(a,'\'') && !ft_strchr(a,'\"'))
		return (a); 
	c = ft_strdup("");
	while (a[i])
	{
		while (a[i] && !(open = check_quotes1(a[i], open)))
		{
			c = ft_joinchar(c, a[i]);
			i++;
		}
		if (open == 1)
		{
			i++;
			while (a[i] && (open = check_quotes1(a[i],open) == 1))
			{

				c = ft_joinchar(c, a[i]);
				i++; 
			}
			i++;
		}

		if (open == 2)
		{
			i++;
			while (a[i] && (open = check_quotes1(a[i],open)) == 2)
			{
				c = ft_joinchar(c, a[i]);
				i++; 
			}
			i++;

		}
	}
	if (e == 0)
	{	
		free(a);
		a = NULL;
	}
	return (c);

}

char        **ignore_quotes1(char **s, t_env *env)
{
	int i;
	char *c;

	i = 0;
	(void)env;
	while (s[i])
	{
		c = ft_strdup(s[i]);
		s[i] = ignore_quotes(s[i], 0);
		s[i] = dollar_check(c, s[i], env);
		free(c);
		c = NULL;
		i++;
	}
	//printf("c1 = %p\n",c);
	return (s);
}
