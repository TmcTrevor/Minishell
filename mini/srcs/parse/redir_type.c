/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reder_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:59:15 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/20 12:00:11 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_next(char *c)
{
    int type;
	type = 0;
    if (c[0] == '>' && c[1] != '>')
       type = 1;
    if (c[0] == '>' && c[1] == '>')
        type = 2;
   if (c[0] == '<' && c[1]!= '<')
        type  = 3;
    if (c[0] == '<' && c[1] == '<')
        type = 4;
   type = check_eol(c, type);
   return (type);
}

int      redirect(t_command *cmd, int i)
{
    char *c;
 
    int a;
    
    c = ft_substr(cmd->cmd,cmd->t[i], cmd->t[i+1] - cmd->t[i]);
	a = 0;
    if (i == 0 && (cmd->cmd[0] == '>' || cmd->cmd[0] == '<'))
    {
        a = check_next(c);
        if (a == 0)
    	{
            printf("syntax error\n");
			return (0);
     	  }

    }
	if (i != 0)
    {
        a = check_next(c);
        if (a == 0)
    	{
            printf("syntax error\n");
			return (0);
     	  }
    }
	ft_lstadd_back2(&cmd->redirect, new_stack_red(c,a));
	return (1);
}

int    get_type(t_command *cmd)
{
    int i;

    i = 0;
    while (i <= cmd->count)
    {
        if (!redirect(cmd, i))
			return (0);
        i++;
    }  
	return (1); 
}
