/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:43:01 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/20 11:31:52 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	ft_send_signal(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
		ft_handle_error("Error sending signal\n");
}

void	ft_send_bit(pid_t pid, char bit, char flag_to_pause)
{
	if (bit)
		ft_send_signal(pid, SIGUSR1);
	else
		ft_send_signal(pid, SIGUSR2);
	if (flag_to_pause != 0)
		pause();
}

void	ft_send_int(pid_t pid, int num)
{
	int		i;
	char	bit;

	i = INT_SIZE_IN_BITS - 1;
	while (i >= 0)
	{
		bit = (num >> i) & 1;
		ft_send_bit(pid, bit, 1);
		i--;
	}
}

void	ft_send_char(pid_t pid, char c)
{
	int		i;
	char	bit;

	i = CHAR_SIZE_IN_BITS - 1;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		ft_send_bit(pid, bit, 1);
		i--;
	}
}

void	ft_handle_error(char *error_message)
{
	ft_putstr_fd(error_message, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}
