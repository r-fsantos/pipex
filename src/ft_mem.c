/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:12:37 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/28 09:39:49 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

/**
 * TODO: Handle pipe dealloc
 **/
void	ft_mdealloc(t_env *env)
{
	if (env->paths)
		ft_doublefree((void **)env->paths);
	if (env->pfd)
		ft_doublefree((void **)env->pfd);
	if (env->cmd.args)
		ft_doublefree((void **)env->cmd.args);
	if (env->cmd.path)
		ft_singlefree((void *)env->cmd.path);
}

void	ft_singlefree(void *arr)
{
	free(arr);
	arr = NULL;
}

void	ft_doublefree(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_mclean(char *buf, t_env *env)
{
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	if (env)
		ft_mdealloc(env);
}
