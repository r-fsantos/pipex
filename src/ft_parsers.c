/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:32:50 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/26 09:51:58 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static char	*has_occurrence(const char *s1, const char *s2, size_t len)
{
	return (ft_strnstr(s1, s2, len));
}

char	**filter(char **env, char *match)
{
	int	i;
	int	match_len;

	i = 0;
	match_len = ft_strlen(match);
	while (env[i])
	{
		if (has_occurrence(env[i], match, match_len))
			return (ft_split(env[i] + match_len, ':'));
		i++;
	}
	return (NULL);
}

// Could be simplified, but is more readable in this approach (?)
int	cmd_has_any_options(char *str)
{
	if (str)
		return (true);
	return (false);
}

int	single_or_double_quotes(char *str)
{
	return (ft_strchr(str, '\'') || ft_strchr(str, '"'));
}
