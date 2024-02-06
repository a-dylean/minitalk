/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/06 13:26:16 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

// void	signal_handler(int signum, siginfo_t *siginfo, void *context)
// {
// 	pid_t		client_pid;
// 	static char	character = 0;
// 	static int	bit_count = 0;

// 	(void)context;
// 	client_pid = siginfo->si_pid;
// 	if (signum == SIGUSR1)
// 		character = character | 1;
// 	bit_count++;
// 	if (bit_count == 8)
// 	{
// 		write(1, &character, 1);
// 		bit_count = 0;
// 		character = 0;
// 	}
// 	character = character << 1;
// 	if (kill(client_pid, SIGUSR1) == -1)
// 		exit(ft_printf("Error sending signal\n"));
// }

static void	signal_handler(int signal, siginfo_t *info, void *s)
{
	static int	bit;
	static char	tmp;
	pid_t		pid;

	(void)s;
	pid = info->si_pid;
	if (signal == SIGUSR1)
		tmp |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (tmp != '\0')
			ft_putchar_fd(tmp, 1);
		else
			kill(pid, SIGUSR1);
		bit = 0;
		tmp = 0;
	}
}

// int	main(int argc, char **argv)
// {
// 	struct sigaction	sig;
// 	pid_t				pid;

// 	(void)argv;
// 	if (argc != 1)
// 	{
// 		ft_putstr_fd("Error: worng format.\n", 1);
// 		ft_putstr_fd("Try: ./server\n", 1);
// 		return (0);
// 	}
// 	sig.sa_flags = SA_SIGINFO;
// 	sig.sa_sigaction = &ft_handler;
// 	sigemptyset(&sig.sa_mask);
// 	pid = getpid();
// 	ft_pid_print(pid);
// 	sigaction(SIGUSR1, &sig, NULL);
// 	sigaction(SIGUSR2, &sig, NULL);
// 	while (1)
// 		pause();
// 	return (0);
// }

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	//sigset_t			block_mask;

	(void)argv;
	if (argc != 1)
		exit(ft_printf("Wrong input! Correct usage: ./server \n"));
	ft_bzero(&sa, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	// sigaddset(&block_mask, SIGINT);
	// sigaddset(&block_mask, SIGQUIT);
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	//sa.sa_mask = block_mask;
	sa.sa_sigaction = &signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
	sigaction(SIGUSR2, &sa, NULL) == -1)
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