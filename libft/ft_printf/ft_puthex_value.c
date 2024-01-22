/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:28:34 by atonkopi          #+#    #+#             */
/*   Updated: 2023/12/05 14:32:50 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_value(unsigned int nbr, char format)
{
	int	len;

	len = 0;
	if (nbr >= 16)
		len += ft_puthex_value((nbr / 16), format);
	if (format == 'L')
		len += ft_putchar_value("0123456789abcdef"[nbr % 16]);
	else if (format == 'U')
		len += ft_putchar_value("0123456789ABCDEF"[nbr % 16]);
	return (len);
}
