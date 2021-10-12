/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manu_list_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:52:26 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/11 09:29:00 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirect  *new_stack_red(char *a, int i)
{
	t_redirect *stack;

	stack = (t_redirect *)malloc(sizeof(t_redirect));
	if (!stack)
		return (0);
	else
	{
		stack->line = ft_strdup(a);
		stack->type = i;
		stack->nextred = NULL;
	}
	return (stack);
}

int	ft_lstsize2(t_redirect *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->nextred;
	}
	return (i);
}

void	ft_lstadd_front2(t_redirect **alst, t_redirect *new)
{
	if (*alst != NULL)
		new->nextred = *alst;
	*alst = new;
}

void	ft_lstadd_back2(t_redirect **alst, t_redirect *new)
{
	t_redirect *t;

	t = *alst;
	if (*alst == 0)
	{
		*alst = new;
		new->nextred = NULL;
	}
	else
	{
		while (t->nextred)
			t = t->nextred;
		t->nextred = new;
		new->nextred = NULL;
	}
}

t_redirect *delete_first2(t_redirect *a)
{
	if (a == NULL)
		return (0);
	t_redirect *tmp;

	tmp = a;
	a = a->nextred;
	free(tmp);
	return a;
}