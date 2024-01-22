/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:13:26 by atonkopi          #+#    #+#             */
/*   Updated: 2023/11/30 16:58:28 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_handle_conversion(va_list args, const char c);
int	ft_putchar_value(char c);
int	ft_putstr_value(char *str);
int	ft_putptr_value(void *ptr);
int	ft_putnbr_value(int nbr);
int	ft_putunsigned_value(unsigned int nbr);
int	ft_puthex_value(unsigned int nbr, char format);

#endif