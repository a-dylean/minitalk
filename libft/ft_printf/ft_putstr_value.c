/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:03:47 by atonkopi          #+#    #+#             */
/*   Updated: 2023/12/05 14:28:03 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_value(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr_value("(null)"));
	while (str[i])
		ft_putchar_value(str[i++]);
	return (i);
}
