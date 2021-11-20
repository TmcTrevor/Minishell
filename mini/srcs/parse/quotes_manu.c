/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:57:19 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/21 00:02:50 by mokhames         ###   ########.fr       */
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

char		**downgrad(char **s, int i)
{
	int j;
	int sa;

	j = i + 1;
	sa = ft_strdlen(s);
	//free(s[i - 1])")
	while (i < sa)
	{
		free(s[i]);
		s[i] = NULL;
		s[i] = ft_strdup(s[i + 1]);
		i++;
	}
	free(s[i]);
	s[i] = NULL;
	return (s);	
}

char        **ignore_quotes1(char **s, char **env)
{
	int i;
	char *c;
	char **a;

	i = 0;
	(void)env;
	while (s[i])
	{
		c = ft_strdup(s[i]);
		s[i] = dollar_check(s[i], env);
		if ((ft_strncmp(c, s[i], ft_strlen(c))) && ft_strncmp(s[0], "echo", 4))
		{
			a = ft_split1(s[i], ' ');
			s = strdjoin(1 ,s, a);
			s = downgrad(s, i);
			ft_fres(a,1);
		}
		s[i] = ignore_quotes(s[i], 0);
		free(c);
		c = NULL;
		i++;
	}
	i = 0;
	return (s);
}
