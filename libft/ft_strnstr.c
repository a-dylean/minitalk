/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:39:46 by atonkopi          #+#    #+#             */
/*   Updated: 2023/11/13 14:13:02 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;
	int				j;

	i = 0;
	if (!*s2)
		return ((char *)s1);
	if (n <= 0)
		return (NULL);
	while (i < n && s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j])
		{
			if ((s2[j + 1] == 0) && ((j + i) < n))
				return ((char *)s1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
