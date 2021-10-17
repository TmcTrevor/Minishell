/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 08:05:59 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/15 12:27:26 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     check_quotes(char c, int open)
{
    
    if (c == '\'')
    {
        if (open == 1)
            open = 0;
        else
            open = 1;
    }    
    if (c == '\"')
    {
        if (open == 2)
        {
                open = 0;
        }
        else
                open = 2;   
    }
    return (open);
}
char    *sub_split(t_main *main, int i, int j)
{
    char *c;
    while (main->line[j] == ' ')
        j++;
    c = ft_substr(main->line, j, main->t[i] - j);
    return c;   
}

void    split_pipe(t_main *main)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i <= main->count)
    {
        
        ft_lstadd_back1(&main->cmd,new_stack(sub_split(main,i,j)));
        j = main->t[i] + 1;
        i++;
    }
}

int		check_piperror(t_main *main, int i)
{
	if (main->line[i + 1] == '|')
		return (0);
	while (main->line[i + 1] == ' ')
		i++;
	if (main->line[i + 1] == '\0')
		return (0);
	return (1);		
}
int    parse_pipes(t_main *main)
{
    int i;
    int open;
    int j;

    i = 0;
    open = 0;
    j = 0;
    main->count = 0;
    while (main->line[i])
    {
        open = check_quotes(main->line[i], open);
        if (main->line[i] == '|' && !open)
        {
            if (!(check_piperror(main, i)))
            {  
				printf("syntax error\n");
				return (0);
			}
            main->t[j] = i;
            main->count++;
            j++;
        }
        i++;
    }
    main->t[j] = i + 1;
    split_pipe(main);
    return (1);
}




int    parse(t_main *main)
{
    if (!parse_pipes(main))
     return (0);
   if (!parse_redirection(main->cmd))
        return (0);

   /* while (main->cmd)
    {
      //  printf("%s\n",main->cmd->cmd);
        main->cmd = main->cmd->nextcmd;
    }*/
    return (1);
}