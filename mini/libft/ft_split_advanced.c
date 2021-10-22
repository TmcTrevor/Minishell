/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_advanced.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:55:16 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/22 11:58:09 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

static char	**ft_malloc_error(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_nb_words(char const *s, char c)
{
	size_t	i;
	size_t	nb_words;
    int     open;

	if (!s[0])
		return (0);
	i = 0;
	nb_words = 0;
    open = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
        open = check_quotes(s[i], open);
		if (s[i] == c && !open)
		{
			nb_words++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_words++;
	return (nb_words);
}

static void	ft_get_next_word(char **next_word, size_t *next_word_len, char c)
{
	size_t	i;
    int open;

	*next_word += *next_word_len;
	*next_word_len = 0;
	i = 0;
    open = 0;
	while (**next_word && **next_word == c)
		(*next_word)++;
	while ((*next_word)[i])
	{
        open = check_quotes((*next_word)[i], open);
		if ((*next_word)[i] == c && !open)
			return ;
		(*next_word_len)++;
		i++;
	}
}

char	**ft_split1(char const *s, char c)
{
	char	**tab;
	char	*next_word;
	size_t	next_word_len;
	size_t	i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_nb_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	next_word = (char *)s;
	next_word_len = 0;
	while (i < ft_nb_words(s, c))
	{
		ft_get_next_word(&next_word, &next_word_len, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_word_len + 1));
		if (!tab[i])
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_word, next_word_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}