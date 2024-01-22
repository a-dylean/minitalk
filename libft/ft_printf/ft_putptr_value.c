/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:03:44 by atonkopi          #+#    #+#             */
/*   Updated: 2023/12/06 10:42:53 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_ptr(unsigned long long ptr)
{
	int			len;

	len = 0;
	if (ptr >= 16)
		len += print_ptr(ptr / 16);
	len += ft_putchar_value("0123456789abcdef"[ptr % 16]);
	return (len);
}

int	ft_putptr_value(void *ptr)
{
	if (!ptr)
		return (ft_putstr_value("(nil)"));
	ft_putstr_value("0x");
	return (print_ptr((unsigned long long)ptr) + 2);
}
