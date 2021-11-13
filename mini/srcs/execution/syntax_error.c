/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:07:32 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/13 00:46:39 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syn_error(char *c)
{
	write(2, "mokhames: ", 11);
	write(2, "export: ", 7);
	write(2, "`", 1);
	write(2, c, ft_strlen(c));
	write(2, "'", 1);
	write(2, ": ", 2);
	write(2, "not a valid identifier", 22);
	write(2, "\n", 1);
	g_status_code = 1;
}

int	check_syntax(char *arg)
{
	int i;

	i = 0;
	if (arg[0] == '=')
	{
		syn_error(arg);
		return (1);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalpha(arg[i]) || arg[i] == '_')
			i++;
		else if ((ft_isdigit(arg[i]) && i != 0))
			i++;
		else
		{
			syn_error(arg);
			return (1);
		}
	}
	return (0);
}