/* ************************************************************************** */
/*																		    */
/*														:::      ::::::::   */
/*   quotes_manu.c								      :+:      :+:    :+:   */
/*												    +:+ +:+		 +:+     */
/*   By: mokhames <mokhames@student.42.fr>		  +#+  +:+       +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/10/20 11:57:19 by mokhames		  #+#    #+#		     */
/*   Updated: 2021/11/25 08:02:31 by mokhames		 ###   ########.fr       */
/*																		    */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join(char *a, char *c, int *open, int *i)
{
	int	e;

	e = *open;
	(*i)++;
	*open = check_quotes1(a[*i], *open);
	while (a[*i] && *open == e)
	{
		*open = check_quotes1(a[*i], *open);
		if (*open == e)
		{
			c = ft_joinchar(c, a[*i]);
			(*i)++;
		}
		else
			break ;
	}
	return (c);
}

void	free1(char *a, int e)
{
	if (e == 0)
	{
		free(a);
		a = NULL;
	}
}

char	*ignore_quotes(char *a, int e)
{
	char	*c;
	int		i;
	int		open;

	i = 0;
	open = 0;
	if (!a || (!ft_strchr(a, '\'') && !ft_strchr(a, '\"')))
		return (a);
	c = ft_strdup("");
	c = ignore_loop(a, c);
	if (e == 0)
	{	
		free(a);
		a = NULL;
	}
	return (c);
}

char	**downgrad(char **s, int i, int sa)
{
	int		j;
	int		k;
	char	**new_s;

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
	return (new_s);
}

char	**ignore_quotes1(char **s, char **env)
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
			continue ;
		}
		s[i] = ignore_quotes(s[i], 0);
		i++;
	}
	return (s);
}
