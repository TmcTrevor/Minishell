/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   export.c	   :+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: mokhames <mokhames@student.42.fr>	  +#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2021/11/12 22:47:40 by mokhames	  #+#	#+#	 */
/*   Updated: 2021/11/24 23:46:05 by mokhames         ###   ########.fr       */
/*	*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_to_export(char *c, char ***env)
{
	char	*s;
	char	*fp;
	int		i;

	i = get_fo_index(c);
	if (i == -1)
	{
		if (!find_path3(c, *env))
			*env = strdup23(*env, c);
		return ;
	}
	fp = ft_substr(c, 0, i);
	s = ft_strchr(c, '=');
	if (find_path3(fp, *env))
		replace(env, fp, s);
	else
		*env = strdup23(*env, c);
	free(fp);
}

void	delete_from_export(char *c, char ***env)
{
	int	sa;

	sa = ft_strdlen(*env);
	if (find_path3(c, *env))
		*env = delete_from_env(sa, c, *env);
}

int	export_unset(char **args, char ***env, int mode)
{
	int	i;
	int	j;

	j = 1;
	i = ft_strdlen(args) - 1;
	if (i == 0)
		add_quotes(*env);
	else if (i > 0)
	{
		while (args[j])
		{
			if (!check_syntax(args[j]))
			{
				if (mode == 1)
					add_to_export(args[j], env);
				if (mode == 2)
					delete_from_export(args[j], env);
			}
			j++;
		}
	}
	__get_var(SETEXIT, 0);
	return (1);
}

char	**return_free(char **env, char **new_env)
{
	ft_fres(env, 1);
	return (new_env);	
}
