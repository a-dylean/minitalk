/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:51 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/06 13:22:30 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

// //int			g_bit_received;

// void	ft_send_bit(pid_t pid, int bit)
// {
// 	int	signal;

// 	if (bit == 1)
// 		signal = SIGUSR1;
// 	else
// 		signal = SIGUSR2;
// 	if (kill(pid, signal) == -1)
// 		exit(ft_printf("Error sending signal\n"));
// }

// void	ft_send_char(pid_t pid, char c)
// {
// 	int	i;

// 	i = 7;
// 	while (i >= 0)
// 	{
// 		//g_bit_received = 0;
// 		ft_send_bit(pid, (c >> i) & 1);
// 		// while (!g_bit_received)
// 		// 	;
// 		i--;
// 	}
// }

// static void	ft_send_str(pid_t pid, char *msg)
// {
// 	int	i;

// 	i = 0;
// 	if (!msg)
// 		return ;
// 	while (msg[i])
// 	{
// 		ft_send_char(pid, msg[i]);
// 		i++;
// 	}
// 	ft_send_char(pid, '\0');
// }

static void	ft_handle_server_signal(int signal)
{
	if (signal == SIGUSR1)
		ft_putstr_fd("Message received by the server\n", 1);
	exit (0);
}

static void	ft_send_bit(pid_t pid, char input)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((input & (1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

static void	ft_send_str(pid_t pid, char input[])
{
	int	i;

	i = 0;
	while (input[i])
	{
		ft_send_bit(pid, input[i]);
		i++;
	}
	ft_send_bit(pid, '\n');
	ft_send_bit(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	struct sigaction	sa;

	if (argc == 3 && ft_str_isnumeric(argv[1]) && argv[2][0])
	{
		server_pid = ft_atoi(argv[1]);
		if (kill(server_pid, 0) == -1 || server_pid == 0)
		{
			ft_printf("Invalid server PID: %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		ft_bzero(&sa, sizeof(struct sigaction));
		sa.sa_handler = &ft_handle_server_signal;
		if (sigaction(SIGUSR1, &sa, NULL) == -1)
			exit(ft_printf("Error setting up signal handler\n"));
		ft_send_str(server_pid, argv[2]);
		ft_send_str(server_pid, "\n");
		ft_printf("String sent\n");
	}
	else
	{
		exit(ft_printf("Wrong input! Correct usage: ./client \
		[SERVER PID] [MESSAGE TO SEND]\n"));
	}
	return (0);
}