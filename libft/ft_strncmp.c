/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:39:44 by atonkopi          #+#    #+#             */
/*   Updated: 2023/11/23 15:26:46 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && j < n)
	{
		i++;
		j++;
	}
	if (j < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
