/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:39:35 by atonkopi          #+#    #+#             */
/*   Updated: 2023/11/22 11:54:40 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	size_dst;
	unsigned int	size_src;

	size_src = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (size_src);
	size_dst = ft_strlen(dst);
	if (size <= size_dst)
		return (size_src + size);
	while (src[i] && i + size_dst < size - 1)
	{
		dst[i + size_dst] = src[i];
		i++;
	}
	dst[i + size_dst] = '\0';
	return (size_dst + size_src);
}
