#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"

void    clear_all(t_main *main)
{
		int i = -1;
        //t_env   *t;
        t_redirect *r;
        t_command *c;

        free(main->line);
       /*while (main->env)
        {
            t = main->env;
            free(main->env->value);
            main->env = main->env->next;
            free(t);
        }*/
        while (main->cmd)
        {
            c = main->cmd;
                while(main->cmd->redirect)
                {
                    r = main->cmd->redirect;
                        free(main->cmd->redirect->line);
						if (main->cmd ->redirect->file)
							free (main->cmd ->redirect->file);
                        main->cmd->redirect = main->cmd->redirect->nextred;
                    free(r);
                }
				if (main->cmd->argument)
				{
					while (main->cmd->argument[++i])
						free(main->cmd->argument[i]);
				}
                free(main->cmd->cmd);
                main->cmd = main->cmd->nextcmd;
            free(c);
        }
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
        env_init(main, envm);
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
                clear_all(main);
        } 
		//clear_all(main);
		system("leaks minishell");
        return 0;

}