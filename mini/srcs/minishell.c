#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"

void    clear_all(t_main *main)
{
		int i = 0;
        free(main->line);
        while (main->cmd)
        {
                while(main->cmd->redirect)
                {
                        free(main->cmd->redirect->line);
						if (main->cmd ->redirect->file)
							free (main->cmd ->redirect->file);
                        main->cmd->redirect = main->cmd->redirect->nextred;
                }
                free(main->cmd->redirect);
				if (main->cmd->argument)
				{
					while (main->cmd->argument[i++])
						free(main->cmd->argument[i]);
					free(main->cmd->argument);
				}
                free(main->cmd->cmd);
                main->cmd = main->cmd->nextcmd;
        }
        free(main->cmd);
}

int main(int ac, char **argv, char **envm)
{
        //char *inpt;
        //char **cmd;
       // pid_t pid;
		(void)ac;
		(void)argv;
		(void)envm;
        int i = 1;
        t_main  *main;
        main   = malloc(sizeof(t_main));
        while (i)
        {
			/*if (i == 0)
				main->line = "ls | ls";
			if (i == 1)
				main->line = "exit";*/
                main->line = readline("mokhamaes > ");
               //cmd = ft_split(main->line,' ');
                parse(main);
               //char *cmd[] = {"ls", "", NULL};
                //check_cmd(main->line, cmd, envm);
                if (!ft_strncmp(main->line,"exit",4))
					i = 0;
                add_history(main->line);
              //  clear_all(main);
        } 
		//clear_all(main);
		system("leaks minishell");
        return 0;

}