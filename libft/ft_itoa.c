/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:01:41 by atonkopi          #+#    #+#             */
/*   Updated: 2023/11/27 15:57:14 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_str_len(int n)
{
	int		size;
	long	nb;

	size = 1;
	nb = (long)n;
	if (n < 0)
	{
		nb = -nb;
		size++;
	}
	while (nb >= 10)
	{
		size++;
		nb = nb / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	i = get_str_len(n);
	str = malloc((i + 1) * sizeof(char));
	nb = (long)n;
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		str[i] = '0';
	if (n < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	while (i >= 0 && nb > 0)
	{
		str[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	return (str);
}
