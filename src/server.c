/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/01/30 15:07:44 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	character = 0;
	static int				bit_count = 0;
	static __pid_t			client_pid = 0;

	(void)context;
	if (client_pid != info->si_pid)
	{
		bit_count = 0;
		character = 0;
	}
	client_pid = info->si_pid;
	character = character << 1;
	if (signum == SIGUSR1)
		character = character | 1;
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &character, 1);
		bit_count = 0;
		character = 0;
	}
	kill(client_pid, SIGUSR2);
}
int	main(void)
{
	__pid_t	pid;
	struct sigaction sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = 0;
	pid = getpid();
	ft_printf("Server pid: %d\n", pid);
	// if (sigaction(SIGINT, &sa, NULL) == -1)
	// {
	// 	ft_printf("Error");
	// 	exit(1);
	// }
	printf("Waiting for the client...\n");
	// signal(SIGINT, signal_handler);
	while (1)
	{
		//ft_printf("hello");
		sleep(1);
	}
	return (0);
}
