/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:13:28 by atonkopi          #+#    #+#             */
/*   Updated: 2023/11/29 12:48:54 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(char const *s1, char const *set)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
	{
		i++;
		size++;
	}
	i = ft_strlen(s1) - 1;
	while (i && ft_strchr(set, s1[i]))
	{
		i--;
		size++;
	}
	return (ft_strlen(s1) - size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		i;
	int		j;
	int		k;
	int		size;

	if (!s1 || !set)
		return (NULL);
	size = get_size(s1, set) + 1;
	if (size <= 0)
		size = 1;
	result = malloc(sizeof(char) * size);
	if (!result)
		return (NULL);
	i = 0;
	while (ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[j]))
		j--;
	k = 0;
	while (i <= j)
		result[k++] = s1[i++];
	result[k] = '\0';
	return (result);
}
