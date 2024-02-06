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

int			g_bit_received;

void	send_bit(pid_t pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
		exit(ft_printf("Error sending signal\n"));
}

void	ft_send_char(pid_t pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_bit_received = 0;
		send_bit(pid, (c >> i) & 1);
		while (!g_bit_received)
			;
		i--;
	}
}

static void	ft_send_msg(pid_t pid, char *msg)
{
	int	i;

	i = 0;
	if (!msg)
		return ;
	while (msg[i])
	{
		ft_send_char(pid, msg[i]);
		i++;
	}
	ft_send_char(pid, '\0');
}

void	handle_server_signal(int signum)
{
	if (signum == SIGUSR1)
		g_bit_received = 1;
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	struct sigaction	sa;

	if (argc != 3 || !ft_str_isnumeric(argv[1]))
		exit(ft_printf("Wrong input! Correct usage: ./client \
		[server's PID] [message to send]\n"));
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0)
		exit(ft_printf("Invalid PID: %s\n", argv[1]));
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &handle_server_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(ft_printf("Error setting up signal handler\n"));
	ft_send_msg(server_pid, argv[2]);
	ft_send_msg(server_pid, "\n");
	ft_printf("String sent\n");
	return (0);
}
