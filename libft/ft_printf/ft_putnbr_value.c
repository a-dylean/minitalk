/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:52:58 by atonkopi          #+#    #+#             */
/*   Updated: 2023/12/06 10:39:47 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_value(int nbr)
{
	int	len;

	len = 0;
	if (nbr == -2147483648)
		len += ft_putstr_value("-2147483648");
	else
	{
		if (nbr < 0)
		{
			len += ft_putchar_value('-');
			nbr *= -1;
		}
		if (nbr > 9)
		{
			len += ft_putnbr_value(nbr / 10);
			len += ft_putnbr_value(nbr % 10);
		}
		else
			len += ft_putchar_value((nbr + '0'));
	}
	return (len);
}
