/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:44:36 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/20 11:21:45 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	ft_handle_server_signal(int signal)
{
	if (signal == SIGUSR1)
		return ;
	else if (signal == SIGUSR2)
		exit(EXIT_SUCCESS);
}

static void	ft_send_message(int server_pid, char *str)
{
	int	i;

	i = 0;
	{
		ft_send_int(server_pid, ft_strlen(str));
		while (str[i] != '\0')
		{
			ft_send_char(server_pid, str[i]);
			i++;
		}
		ft_send_char(server_pid, '\n');
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
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL)
		== -1)
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
		ft_send_message(ft_atoi(argv[1]), argv[2]);
	}
	else
		ft_handle_error("Usage:./client [SERVER PID] [MESSAGE TO SEND]\n");
	return (EXIT_SUCCESS);
}
