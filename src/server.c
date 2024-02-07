/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:44:58 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/07 14:02:03 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static	void	ft_print_pid(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_putstr_fd("Server PID: ", 1);
	ft_putstr_fd(ft_itoa(server_pid), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Waiting for the client...\n", 1);
}

static void	ft_handle_client_signal(int signal, siginfo_t *info, void *context)
{
	static int	bit_count;
	static char	temp_char;
	pid_t		client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (signal == SIGUSR1)
		temp_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		ft_putchar_fd(temp_char, 1);
		bit_count = 0;
		temp_char = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc == 1)
	{
		ft_bzero(&sa, sizeof(struct sigaction));
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &ft_handle_client_signal;
		if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa,
				NULL) == -1)
		{
			ft_putstr_fd("Error setting up signal handler\n", 1);
			exit(EXIT_FAILURE);
		}
		ft_print_pid();
		while (1)
			pause();
	}
	else
	{
		ft_putstr_fd("Wrong input! Correct usage: ./server \n", 1);
		exit(EXIT_FAILURE);
	}
	return (0);
}
