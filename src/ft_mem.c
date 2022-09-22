/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:12:37 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/22 06:26:19 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_malloc(t_env *env)
{
	ft_bzero(env, sizeof(t_env));
}

void	ft_mdealloc(t_env *env)
{
	if (env->paths)
		ft_doublefree(env->paths);
	ft_putendl_fd("NOT IMPLEMENTED ERROR: Memory deallocation!",
		e_ft_std_err);
}

void	ft_bzero(void *s, size_t n)
{
	if (n != 0)
		ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}

void	ft_doublefree(char **arr)
{
	while (*arr++)
	{
		free(*arr);
		*arr = NULL;
	}
	arr = NULL;
}
