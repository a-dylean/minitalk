/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:43:52 by atonkopi          #+#    #+#             */
/*   Updated: 2023/12/05 14:32:43 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_conversion(va_list args, const char c)
{
	if (c == 'c')
		return (ft_putchar_value(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr_value(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putptr_value(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_value(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putunsigned_value(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_puthex_value(va_arg(args, unsigned int), 'L'));
	else if (c == 'X')
		return (ft_puthex_value(va_arg(args, unsigned int), 'U'));
	else if (c == '%')
		return (ft_putchar_value('%'));
	return (0);
}
