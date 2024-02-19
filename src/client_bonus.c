/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:51 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/16 16:39:46 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	ft_handle_server_signal(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr_fd("\e[33m > ACK signal received from server\n\e[0m",
			STDOUT_FILENO);
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd("\e[92m > end of message signal received from server\n\e[0m",
			STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}
static void	ft_send_char(pid_t pid, char c)
{
	int		shift;
	char	bit;

	shift = (sizeof(char) * 8) - 1;
	while (shift >= 0)
	{
		bit = (c >> shift) & 1;
		send_bit(pid, bit, 1);
		shift--;
	}
}

static void	ft_send_int(pid_t pid, int num)
{
	int		shift;
	char	bit;

	shift = (sizeof(int) * 8) - 1;
	while (shift >= 0)
	{
		bit = (num >> shift) & 1;
		send_bit(pid, bit, 1);
		shift--;
	}
}

static void	client_send_message(int server_pid, char *str)
{
	int	i;

	i = 0;
	{
		ft_send_int(server_pid, ft_strlen(str));
		while (str[i] != '\0')
			ft_send_char(server_pid, str[i++]);
		ft_send_char(server_pid, '\0');
	}
}
static void	ft_set_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ft_handle_server_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) ==
		-1)
		ft_handle_error("Error setting up signal handler\n");
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc == 3 && argv[2][0])
	{
		server_pid = ft_atoi(argv[1]);
		if (kill(server_pid, 0) == -1 || server_pid <= 0)
			ft_handle_error("Invalid server PID\n");
		ft_set_sigaction();
		client_send_message(server_pid, argv[2]);
	}
	else
		ft_handle_error("Wrong input!\nCorrect usage: ./client [SERVER PID] [MESSAGE TO SEND]\n");
	return (EXIT_SUCCESS);
}
