/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:44:36 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/15 18:32:57 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	client_handler(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr_fd("Server received bit\n",
			STDOUT_FILENO);
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd("Server received whole message\n",
			STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

static void	client_send_message(int server_pid, char *str)
{
	int	i;

	i = 0;
	{
		send_int(server_pid, ft_strlen(str));
		while (str[i] != '\0')
			send_char(server_pid, str[i++]);
		send_char(server_pid, '\n');
		send_char(server_pid, '\0');
	}
}
static void	ft_set_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = client_handler;
	
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
		client_send_message(ft_atoi(argv[1]), argv[2]);
	}	
	else
		ft_handle_error("Wrong input!\nCorrect usage: ./client [SERVER PID] [MESSAGE TO SEND]\n");
	return (EXIT_SUCCESS);
}
