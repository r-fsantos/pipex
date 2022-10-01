/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:46:03 by rfelicio          #+#    #+#             */
/*   Updated: 2022/10/01 13:32:02 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include "stdio.h"

/*
** Launched in case of error on srt assignment
** on the **arr. It frees all memory already
** allocated from the previous strings.
*/
static char	**ft_free(char **arr, int arrsize)
{
	int	i;

	i = 0;
	while (i < arrsize)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

/*
** Gets the word number/strings that can be splitted
** away from the original char const *s, delimited by
** the char separator c. 
** It RETURNS the int word_nbr.
*/
static int	ft_getwords(char const *s, char c)
{
	int	i;
	int	is_word;
	int	word_nbr;

	i = 0;
	is_word = 0;
	word_nbr = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			is_word = 0;
		if (s[i] != c && !is_word)
		{
			is_word = 1;
			++word_nbr;
		}
		++i;
	}
	return (word_nbr);
}

/*
** Gets the wordlen/strlen from the char pointed
** by char const *s, ending with the char separator c
** It RETURNS the int i/word_len.
*/
static int	ft_getwordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

/*
** It allocates and returns an array of strings (**split)
** obtained by splitting the char const *s using the
** character c as delimiter. The array must be endded by a
** NULL pointer.
*/
char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		words;
	char	**split;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = ft_getwords(s, c);
	split = (char **)ft_calloc((words + 1), sizeof(char *));
	if (!split)
		return (NULL);
	while (i < words)
	{
		while (s[j] == c && s[j] != '\0')
			j++;
		split[i] = ft_substr(&s[j], 0, ft_getwordlen(&s[j], c));
		if (!split[i])
			return (ft_free(split, i));
		j += ft_getwordlen(&s[j], c);
		i++;
	}
	return (split);
}

/**
 * DESCRIPTION: Pre-parse commands and options, in such a way to be
 * possible to use in awk and other programms. Has a workaround to
 * not suppress spaces and single or double quotes.
 * It replaces spaces by an especial character, so in this way it
 * is not removed from the array on the split function. Later on its
 * removed and replaced by a space character.
 *
 * Example:
 * INPUT:
 * 		tr 'a' ' ' ->
 * 		tr 'a' 'BLUEPRINT_CHARACTER' ->
 * 		{"tr", "a", "BLUEPRINT_CHARACTER"} -> 
 * OUTPUT:
 * 		{"tr", "a", " "}
 **/
char	**ft_split_arg_and_options(char *arg)
{
	int		i;
	int		second_terminator;
	char	terminator;

	i = -1;
	second_terminator = false;
	terminator = 0;
	while (arg[++i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && arg[i + 1] == ' ')
		{
			arg[i + 1] = BLUEPRINT_CHARACTER;
			if (arg[i + 2] && arg[i + 2] == ' ' && !second_terminator)
			{
				arg[i + 2] = arg[i];
				second_terminator = i + 2;
				terminator = arg[i];
			}
		}
	}
	if (second_terminator)
		ft_remove_second_terminator(&(arg[second_terminator + 1]),
			terminator);
	return (ft_split_and_remove_blueprint_from(arg));
}
