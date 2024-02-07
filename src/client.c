/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:44:36 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/07 18:49:28 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	ft_send_bit(pid_t pid, char c)
{
	int	bit;
	int	signal;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if ((1 & (c >> bit)) != 0)
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		ft_send_signal(pid, signal);
		usleep(100);
		bit++;
	}
}

static void	ft_send_str(pid_t pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_send_bit(pid, str[i]);
		i++;
	}
	ft_send_bit(pid, '\n');
}

static void	ft_validate_input(int argc, char **argv)
{
	if (argc != 3 || !ft_str_isnumeric(argv[1]) || !argv[2][0])
	{
		ft_putstr_fd("Wrong input!\n", 1);
		ft_putstr_fd("Usage: ./client [SERVER PID] [MESSAGE TO SEND]\n", 1);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;

	ft_validate_input(argc, argv);
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0)
	{
		ft_putstr_fd("Invalid server PID\n", 1);
		exit(EXIT_FAILURE);
	}
	ft_send_str(server_pid, argv[2]);
	return (0);
}
