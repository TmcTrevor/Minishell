/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:21:15 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/02 10:23:21 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_env(char *c, char *res, t_env *env)
{
	char	*tmp;

	tmp = ft_strdup(res);
	while (env)
	{
		if (!(ft_strncmp(env->value, c, ft_strlen(c)))
			&& env->value[ft_strlen(c)] == '=')
		{
			free(res);
			res = ft_strjoin(tmp, env->value + ft_strlen(c) + 1);
			return (res);
		}
		env = env->next;
	}
	free(tmp);
	tmp = NULL;
	return (res);
}

char	*dollar_cases(char *res, char *s, t_env *env, int *i)
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

char	*dollar_prefix(char *s, int *i, char *res)
{
	int	j;

	j = get_index(s + (*i), '$');
	if (j == -1)
		j = ft_strlen(s + (*i));
	res = ft_substr(s + (*i), 0, j);
	(*i) += j;
	return (res);
}

char	*dollar_small_case(char *c, char *s)
{
	int		i;
	char	*sub;

	i = 0;
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
	return (NULL);
}

char	*dollar_check(char *c, char *s, t_env *env)
{
	int		i;
	char	*sub;
	char	*res;
	t_env	*env1;

	i = 0;
	env1 = env;
	sub = dollar_small_case(c, s);
	if (sub)
		return (sub);
	res = NULL;
	while (i < ft_strlen(s))
	{
		if (s[i] == '$')
		{
			env1 = env;
			res = dollar_cases(res, s, env1, &i);
		}
		else if (s[i])
			res = dollar_prefix(s, &i, res);
	}
	free(s);
	s = NULL;
	return (res);
}
