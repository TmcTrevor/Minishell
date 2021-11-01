/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:21:15 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/01 20:16:12 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_index(char *c, char w)
{
	int i;

	i = 0;
	while (c[i])
	{
		if (c[i] == w || c[i] == ' ' || c[i] == '\'' || c[i] == '\"')
			return (i);
		i++;
	}
	return (-1);
}

char *check_env(char *c, char *res, t_env *env)
{
	char *tmp;
	
	tmp = ft_strdup(res);
	while (env)
	{
		if (!(ft_strncmp(env->value, c, ft_strlen(c))) && env->value[ft_strlen(c)] == '=')
		{
			res = ft_strjoin(tmp, env->value + ft_strlen(c) + 1);
			return (res);
		}
		env = env->next;
	}
	free(tmp);
	tmp = NULL;
	return (res);
}
char	*odd_dollar(char *s, int k, int *i)
{
	int j;
	char *res;
	
	j  = get_index(s + (*i) + k, '$');
	if (j == -1)
		j = ft_strlen(s + (*i));
	res = ft_substr(s + (*i), 0, j);
	(*i) += j;
	return (res);	
}

char	*even_dollar(char *s, char *res, int k , int i)
{
	int j;
	int a;
	
	a = k;
	while (a-- > 1)
		res = ft_joinchar(res, '$');
	j = get_index(s + (i) + k, '$');
	if (j == -1)
		j = ft_strlen(s + (i));
	return (res);
}

int	skip_dollar(char *s, int *k, int i)
{
	int a;

	a = 0;
	while (s[(i)] == '$')
	{
		a++;
		(*k)++;
		i++;
	}
	if (a % 2 == 0)
		return (1);
	return (0);
}

char	*random_join(char *res,int a)
{
	int e;

	e = a;
	while (a-- > 1)
		res = ft_joinchar(res, '$');
	return (res);
}

char *dollar_cases(char *res, char *s, t_env *env, int *i)
{
	int j;
	int k;
	char *sub;
	
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

char	*dollar_small_case(char *c, char *s)
{
	
}

char *dollar_check(char *c, char *s, t_env *env)
{
	int i;
	char *sub;
	char *res;
	t_env *env1;

	i = 0;
	env1 = env;
	if (!ft_strchr(s, '$'))
		return (s);
	while (c[i])
		i++;
	sub = ft_substr(c, 1, i - 2);
	if (c[0] == '\'' && c[i - 1] == '\'' && !(strcmp(sub, s)))
	{
		free(sub);
		return (s);
	}
	free(sub);
	sub = NULL;
	i = 0;
	res = NULL;
	while (s[i])
	{
		if (s[i] == '$')
		{
			env1 = env;
			res = dollar_cases(res, s, env1, &i);
		}
		else if (s[i])
		{
			res = ft_joinchar(res, s[i]);
			i++;
		}
		if (i > ft_strlen(s))
			break;
	}
	free(sub);
	sub = NULL;
	free(s);
	s = NULL;
	return (res);
}
