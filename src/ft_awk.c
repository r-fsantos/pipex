/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_awk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 09:39:49 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/29 21:59:38 by rfelicio         ###   ########.fr       */
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

void	ft_parsing_awk(t_env *env)
{
	char	**parsed_args;
	char	*bin;

	bin = env->bin;
	parsed_args = ft_calloc(AWK_ARGS_QUANTITY, sizeof(*parsed_args));
	parsed_args[0] = ft_strdup(bin);
	parsed_args[1] = ft_cleaning_awk_args(env);
	env->cmd.args = parsed_args;
}

// TODO: Refactor ft_pathjoin to be more readable. Mainly for thi context.
char	*ft_cleaning_awk_args(t_env *env)
{
	char	**args;
	char	*buffer;
	char	*cleaned_args;
	char	*tmp;
	int		i;

	args = env->cmd.args;
	buffer = NULL;
	i = 0;
	while (args[++i])
	{
		tmp = ft_strjoin(args[i], " ");
		buffer = ft_pathjoin(buffer, tmp);
		ft_singlefree((void *)tmp);
	}
	cleaned_args = ft_strtrim(buffer, "' \"");
	ft_singlefree(buffer);
	return (cleaned_args);
}

static int	has_awk_string_on(char *str)
{
	return (str && (ft_strncmp(str, "awk", 4) == 0));
}

static int	option_is_single_or_double_quoted(char *str)
{
	return (str && (*str == '\'' || *str == '"'));
}
