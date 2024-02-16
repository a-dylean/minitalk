/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:51 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/16 12:58:14 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	ft_handle_server_signal(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
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
static void	ft_set_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handle_server_signal;
	
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) ==
		-1 || sigaction(SIGINT, &sa, NULL) == -1)
		ft_handle_error("Error setting up signal handler\n");
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;

	if (argc == 3 && argv[2][0])
	{
		server_pid = ft_atoi(argv[1]);
		if (kill(server_pid, 0) == -1 || server_pid <= 0)
			ft_handle_error("Invalid server PID\n");
		ft_set_sigaction();
		ft_send_str(server_pid, argv[2]);
	}
	else
		ft_handle_error("Wrong input!\nCorrect usage: ./client [SERVER PID] [MESSAGE TO SEND]\n");
	return (0);
}
