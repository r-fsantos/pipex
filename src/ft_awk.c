/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_awk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 09:39:49 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/29 09:46:20 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	has_awk_string_on(char *str);
static int	option_is_single_or_double_quoted(char *str);

int	is_awk(t_env *env)
{
	char	**cmd;

	cmd = env->cmd.args;
	if (has_awk_string_on(cmd[0]) && option_is_single_or_double_quoted(cmd[1]))
		return (true);
	return (false);
}

static int	has_awk_string_on(char *str)
{
	return (str && (ft_strncmp(str, "awk", 4) == 0));
}

static int	option_is_single_or_double_quoted(char *str)
{
	return (str && (*str == '\'' || *str == '"'));
}
