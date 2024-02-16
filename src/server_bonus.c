/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/16 12:59:39 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_data	*data;

void	ft_update_data(pid_t client_pid, int signal)
{
	if (data->client_pid != client_pid)
		data->client_pid = client_pid;
	ft_enqueue(data, signal);
	if (ft_queue_is_full(data))
		ft_add_buffer_to_str(data);
	// if (signal)
	// 	// ft_send_signal(data->client_pid, SIGUSR1);
	// 	kill(data->client_pid, SIGUSR1);
	// else
	// 	// ft_send_signal(data->client_pid, SIGUSR2);
	// 	kill(data->client_pid, SIGUSR2);
	//usleep(100);
	// usleep(100);
}

void	ft_handle_client_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (signal == SIGUSR1)
	{
		ft_update_data(info->si_pid, 1);
		ft_send_signal(data->client_pid, SIGUSR1);
	}
	else if (signal == SIGUSR2)
	{
		ft_update_data(info->si_pid, 0);
		ft_send_signal(data->client_pid, SIGUSR2);
	}
	else
		ft_handle_error("Error receiving signal\n");
}
static void	ft_set_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handle_client_signal;
	
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) ==
		-1 || sigaction(SIGINT, &sa, NULL) == -1)
		ft_handle_error("Error setting up signal handler\n");
}

int	main(int argc, char **argv)
{
	(void)argv;
	ft_set_sigaction();
	if (argc == 1)
	{
		data = ft_init_struct(-1);
		ft_print_pid();
		while (1)
			pause();
	}
	else
		ft_handle_error("Wrong input!\nCorrect usage: ./server \n");
	return (EXIT_SUCCESS);
}
