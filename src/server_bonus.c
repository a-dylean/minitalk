/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/12 16:34:53 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_data		*data;

static void	ft_update_data(int signal)
{
	char temp_char;
	ft_print_queue(data);
	//ft_send_signal(data->client_pid, SIGUSR1);
	if (ft_queue_is_full(data))
	{
		temp_char = ft_binary_to_char(data);
		if (temp_char != '\0')
		{
			ft_putchar_fd(temp_char, 1);
			signal = SIGUSR1;
		}
		else
			signal = SIGUSR2;
		ft_send_signal(data->client_pid, signal);
		usleep(100);
		ft_init_queue(data);
	} 
	ft_enqueue(data, signal);
}

static void	ft_handle_client_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid)
		data->client_pid = info->si_pid;
	if (signal == SIGUSR1)
		ft_update_data(1);
	else if (signal == SIGUSR2)
		ft_update_data(0);
	else
	{
		ft_putstr_fd("Error receiving signal\n", 1);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc == 1)
	{
		data = ft_init_data();
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
