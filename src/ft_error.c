/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:37:22 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/22 06:20:47 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	ft_mclean(char *buf, t_env *env);

void	ft_error(int error_code, t_env *env)
{
	char	*msg;

	msg = NULL;
	ft_putstr_fd("bash: ", e_ft_std_err);
	if (error_code == e_bad_input)
		ft_putendl_fd(BAD_INPUT USAGE_MSG, e_ft_std_err);
	if (error_code == e_env_prep)
	{
		msg = ft_strjoin(env->infile, FILE_NOT_ACCESSIBLE_MSG);
		ft_putendl_fd(msg, e_ft_std_err);
	}
	ft_mclean(msg, env);
	exit(-1);
}

static void	ft_mclean(char *buf, t_env *env)
{
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	if (env)
		ft_mdealloc(env);
}
