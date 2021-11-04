/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:29:13 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/04 12:01:38 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_fress(char **b, int j)
{
	int i;

	i = 0;
	if (b)
	{
		while (b[i] && i < j)
		{
			free(b[i]);
			b[i] = NULL;
			i++;
		}
	}
	b = NULL;
}

void	lunch_here_doc(t_main *main, char **tab, int j)
{
	int i;
	char *c;

	i = 0;
	int e = ft_strlen(tab[i]);
	e  = 0;
	while (i < j)
	{
		c = readline("here_doc > ");
		//get_next_line(0, &c);
		if (c)
		{
			if (!ft_strncmp(c, tab[i], ft_strlen(tab[i])))
				i++;
			else
				main->files = strdup23(main->files, c);
			//free(c);
		}
	}
}

void	execute_here_doc(t_main *main)
{
	t_command	*cmd1;
	t_redirect	*red;
	char		**tab;
	int			j;
	
	cmd1 = main->cmd;
	j = 0;
	tab = NULL;
    while (cmd1)
    {
		red = cmd1->redirect;
		while (red)
		{
			if (red->type == 4)
			{
				tab = strdup23(tab, red->file);
				j++;
			}
			red = red->nextred;
		}
		cmd1 = cmd1->nextcmd;
	}
	lunch_here_doc(main, tab,j);
	//ft_fress(tab, j);
}

//#include "../includes/pipex.h"

// C program to illustrate
// pipe system call in C
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #define MSGSIZE 16
// char* msg1 = "hello, world #1";
// char* msg2 = "hello, world #2";
// char* msg3 = "hello, world #3";
  
// int main()
// {
//     char inbuf[MSGSIZE];
//     int p[2], i;
// 	pid_t id;
  
//     if (pipe(p) < 0)
//         exit(1);
  
//     /* continued */
//     /* write pipe */
// 	id = fork();
// 	if (id == 0)
// 	{
// 		close(p[0]);
//     	write(p[1], msg1, MSGSIZE);
//     	write(p[1], msg2, MSGSIZE);
//    	 	write(p[1], msg3, MSGSIZE);
// 		exit(0);
// 	}
// 	else
// 	{
// 		close(p[1]);
// 		dup2(p[0], 0);
// 		wait(NULL);
// 	}
// 	pid_t id1;
// 	int p2[2];
// 	pipe(p2);
// 	id1 = fork();
// 	if (id1 == 0)
// 	{
// 		close (p2[0]);
// 		dup2(p2[1], 1);
// 		system("cat");
// 	}
// 	else
// 	{
// 		close(p2[1]);
// 		dup2(p2[0], 0);
// 		waitpid(id1, NULL, 0);
// 	}
// 	int pw = open("456", O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	dup2(pw, 1);

// 	system("cat");
//   /*  for (i = 0; i < 3; i++) {
//         read(0, inbuf, MSGSIZE);
//         printf("%s\n", inbuf);
//     }*/
//     return 0;
// }