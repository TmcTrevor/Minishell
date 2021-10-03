/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 11:26:17 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/03 19:47:14 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

/*typedef struct s_env
{
    
};*/

void	error(void);
char	*find_path(char *cmd, char **envp);

void	cmd_call(char *argv, char **envm);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(const char *str, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
/* Bonus functions */
int		open_file(char *argv, int i);
void	arg_err(void);
void    check_cmd(char *inpt, char **cmd, char **envm);

#endif