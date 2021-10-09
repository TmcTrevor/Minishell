#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"



int main(int ac, char **argv, char **envm)
{
        char *inpt;
        char **cmd;
        pid_t pid;

        int i = 0;
        t_main  *main;
        main   = malloc(sizeof(t_main));
        while (1)
        {
                main->line = readline("mokhamaes > ");
               //cmd = ft_split(main->line,' ');
                parse(main);
               //char *cmd[] = {"ls", "", NULL};
                //check_cmd(main->line, cmd, envm);
                add_history(main->line);
        }
        return 0;

}