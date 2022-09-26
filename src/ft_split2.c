/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:47:41 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/26 09:48:43 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (!len || start > slen)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len > (slen - start))
		len = slen - start;
	str = (char *)ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	return ((char *)ft_memmove((void *)str, (void *)(s + start), len));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dststart;
	unsigned char	*srcstart;

	if (!dst && !src)
		return (NULL);
	dststart = (unsigned char *)dst;
	srcstart = (unsigned char *)src;
	if (dststart <= srcstart)
		ft_memcpy(dststart, srcstart, len);
	else
	{
		while (len--)
			*(dststart + len) = *(srcstart + len);
	}
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	s1len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	s1len = ft_strlen(s1);
	while (s1[start] && (ft_strchr(set, s1[start])))
		++start;
	while (s1len && (ft_strchr(set, s1[s1len])))
		--s1len;
	return (ft_substr(s1, start, s1len - start + 1));
}
