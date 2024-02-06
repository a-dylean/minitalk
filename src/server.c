/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/06 13:06:38 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	pid_t		client_pid;
	static char	character = 0;
	static int	bit_count = 0;

	(void)context;
	client_pid = siginfo->si_pid;
	if (signum == SIGUSR1)
		character = character | 1;
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &character, 1);
		bit_count = 0;
		character = 0;
	}
	character = character << 1;
	if (kill(client_pid, SIGUSR1) == -1)
		exit(ft_printf("Error sending signal\n"));
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
		exit(ft_printf("Wrong input! Correct usage: ./server \n"));
	sigset_t			block_mask;
	ft_bzero(&sa, sizeof(struct sigaction));
	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = block_mask;
	sa.sa_sigaction = &signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) ==
		-1)
		exit(ft_printf("Error setting up signal handler\n"));
	ft_printf("Server PID: %d\n", getpid());
	ft_printf("Waiting for the client...\n");
	while (1)
	{
		// sleep(1);
		pause();
	}
	return (0);
}
