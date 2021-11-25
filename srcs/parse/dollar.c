/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:21:15 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 02:54:15 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_env(char *c, char *res, char **env)
{
	char	*tmp;
	char	*q;
	int		i;

	i = 0;
	tmp = ft_strdup(res);
	if (!ft_strncmp(c, "?", 1))
		return (ft_itoa(__get_var(GETEXIT, 0)));
	while (env[i])
	{
		if (!(ft_strncmp(env[i], c, ft_strlen(c)))
			&& env[i][ft_strlen(c)] == '=')
		{
			q = ft_strdup(env[i] + ft_strlen(c) + 1);
			res = ft_strjoin(tmp, q);
			return (res);
		}
		i++;
	}
	free(tmp);
	tmp = NULL;
	return (res);
}

char	*dollar_cases(char *res, char *s, char **env, int *i)
{
	int		j;
	int		k;
	char	*sub;

	k = 0;
	if (skip_dollar(s, &k, (*i)))
		return (odd_dollar(s, k, i));
	else
	{
		res = random_join(res, k);
		j = get_index(s + (*i) + k, '$');
		if (j == -1)
			j = ft_strlen(s + (*i));
		sub = ft_substr(s + (*i) + k, 0, j);
		res = check_env(sub, res, env);
		(*i) += j + 1;
		free(sub);
		sub = NULL;
	}
	return (res);
}

char	*dollar_prefix(char *s, int *i, char *res, int open)
{
	int		j;
	char	*c;
	char	*tmp;

	j = get_index1(s + (*i), '$', open);
	if (j == -1)
		j = ft_strlen(s + (*i));
	c = ft_substr(s + (*i), 0, j);
	tmp = res;
	res = ft_strjoin(tmp, c);
	free(tmp);
	tmp = NULL;
	free(c);
	c = NULL;
	(*i) += j;
	return (res);
}

char	*dollar_small_case(char *s)
{
	int		i;

	i = 0;
	if (!ft_strchr(s, '$'))
		return (s);
	return (NULL);
}

char	*dollar_check(char *s, char **env)
{
	int		i;
	char	*sub;
	int		open;
	char	*res;

	i = 0;
	open = 0;
	sub = dollar_small_case(s);
	if (sub)
		return (s);
	res = NULL;
	while (i < ft_strlen(s))
	{
		open = check_quotes1(s[i], open);
		if (s[i] == '$' && open != 1)
			res = dollar_cases(res, s, env, &i);
		else if (s[i])
			res = dollar_prefix(s, &i, res, open);
	}
	free(s);
	s = NULL;
	return (res);
}
