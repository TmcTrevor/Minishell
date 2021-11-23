/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:57:19 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/23 15:10:52 by mokhames         ###   ########.fr       */
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

	
	if (!a || (!ft_strchr(a,'\'') && !ft_strchr(a,'\"')))
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

		}
	}
	if (e == 0)
	{	
		free(a);
		a = NULL;
	}
	return (c);

}

char        **downgrad(char **s, int i, int sa)
{
    int        j;
    int        k;
    char		**new_s;
    
    j = 0;
    k = 0;
    new_s = (char **)malloc(sa * sizeof(char *));
	garbage(&g, new_s);
    while (j < sa - 1)
    {
        if (j == i)
          k++;
        new_s[j] = ft_strdup(s[k]);
        j++;
        k++;
    }
    new_s[j] = NULL;
   // ft_fres(s, 1);
    return (new_s);    
}

char        **ignore_quotes1(char **s, char **env)
{
	int		i;
	int		e;
	
	e = ft_strdlen(s);
	i = 0;
	while (s[i])
	{
		s[i] = dollar_check(s[i], env);
		if (!s[i])
		{
			s = downgrad(s, i, e);
			e--;
			continue;
		}
		s[i] = ignore_quotes(s[i], 0);
		i++;
	}
	return (s);
}
