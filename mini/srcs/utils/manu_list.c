/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manu_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 08:45:39 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/09 08:49:23 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command *new_stack(char *a)
{
	t_command *stack;

	stack = (t_command *)malloc(sizeof(t_command));
	if (!stack)
		return (0);
	else
	{
		stack->cmd = ft_strdup(a);
		stack->nextcmd= NULL;
	}
	return (stack);
}

int	ft_lstsize1(t_command *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->nextcmd;
	}
	return (i);
}

void	ft_lstadd_front1(t_command **alst, t_command *new)
{
	if (*alst != NULL)
		new->nextcmd = *alst;
	*alst = new;
}

void	ft_lstadd_back1(t_command **alst, t_command *new)
{
	t_command *t;

	t = *alst;
	if (*alst == 0)
	{
		*alst = new;
		new->nextcmd = NULL;
	}
	else
	{
		while (t->nextcmd)
			t = t->nextcmd;
		t->nextcmd = new;
		new->nextcmd = NULL;
	}
}

t_command *delete_first(t_command *a)
{
	if (a == NULL)
		return (0);
	t_command *tmp;

	tmp = a;
	a = a->nextcmd;
	free(tmp);
	return a;
}