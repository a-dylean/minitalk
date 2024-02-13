/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:51 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/13 14:18:36 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

// static void	ft_handle_server_signal(int signal)
// {
// 	if (signal == SIGUSR1)
// 		ft_putstr_fd("Bit received by the server\n", 1);
// 	if (signal == SIGUSR2)
// 		ft_putstr_fd("Whole message printed by the server\n", 1);
// }

static void	ft_handle_server_signal(int signal)
{
	if (signal == SIGUSR1)
		ft_putstr_fd("Received 1\n", 1);
	if (signal == SIGUSR2)
		ft_putstr_fd("Received 0\n", 1);
}

static void	ft_send_bits(pid_t pid, char c)
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
		//pause();
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
		ft_send_bits(pid, str[i]);
		i++;
	}
	ft_send_bits(pid, '\n');
	ft_send_bits(pid, '\0');
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
	struct sigaction	sa;

	ft_validate_input(argc, argv);
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0)
	{
		ft_putstr_fd("Invalid server PID\n", 1);
		exit(EXIT_FAILURE);
	}
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &ft_handle_server_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa,
			NULL) == -1)
	{
		ft_putstr_fd("Error setting up signal handler\n", 1);
		exit(EXIT_FAILURE);
	}
	ft_send_str(server_pid, argv[2]);
	return (0);
}
