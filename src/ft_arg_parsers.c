/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_parsers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 09:51:36 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/30 10:28:22 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*ft_pathjoin(char *s1, char *s2)
{
	char	*bkp;
	char	*ret;

	if (!s1 || !*s1)
		return (ft_strdup(s2));
	bkp = s1;
	ret = ft_strjoin(s1, s2);
	free(bkp);
	bkp = NULL;
	return (ret);
}

char	*ft_get_filepath(t_env *env)
{
	char	**paths;
	char	*filepath;
	int		i;

	paths = env->paths;
	filepath = NULL;
	i = -1;
	while (paths[++i])
	{
		if (filepath)
			free(filepath);
		filepath = ft_strjoin(paths[i], "/");
		filepath = ft_pathjoin(filepath, env->bin);
		if (is_accessible(filepath, env))
			return (filepath);
	}
	free(filepath);
	filepath = NULL;
	return (ft_strdup(""));
}

void	ft_set_executable_path(t_env *env)
{
	char	*path;

	if (is_accessible(env->bin, env))
		path = env->bin;
	else
		path = ft_get_filepath(env);
	env->cmd.path = path;
}

int	ft_parsing_options(t_env *env)
{
	char	**parsed_options;
	char	**options;
	char	options_qtty;
	int		i;

	options = env->cmd.args;
	options_qtty = 0;
	i = -1;
	while (options[++i])
		options_qtty++;
	parsed_options = ft_calloc(options_qtty + 1, sizeof(char *));
	if (!parsed_options)
	{
		env->fl_error = e_calloc_error;
		return (false);
	}
	i = 0;
	parsed_options[i] = ft_strdup(env->cmd.args[i]);
	while (options[++i])
		parsed_options[i] = ft_strtrim(options[i], "'\"");
	ft_doublefree((void **)env->cmd.args);
	env->cmd.args = parsed_options;
	return (true);
}
