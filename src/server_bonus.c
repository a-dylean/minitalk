/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/13 16:52:07 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_data		*data;

static void	ft_update_data(pid_t client_pid, int signal)
{
	//char	temp_char;
	if(data == NULL)
		data = ft_init_struct(client_pid);
	if (data->client_pid != client_pid)
		ft_init_data(data, client_pid);
	ft_enqueue(data, signal);
	if (ft_queue_is_full(data))
		ft_add_buffer_to_str(data);
	usleep(100);
	if (signal)
		//signal = SIGUSR1;
		kill(data->client_pid, SIGUSR1);
	else
		//signal = SIGUSR2;
		kill(data->client_pid, SIGUSR2);
	//ft_send_signal(data->client_pid, signal);
}

static void	ft_handle_client_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	// if (info->si_pid)
	// 	data->client_pid = info->si_pid;
	if (signal == SIGUSR1)
		ft_update_data(info->si_pid, 1);
	else if (signal == SIGUSR2)
		ft_update_data(info->si_pid, 0);
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
		data = ft_init_struct(-1);
		//ft_bzero(&sa, sizeof(struct sigaction));
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &ft_handle_client_signal;
		sigemptyset(&sa.sa_mask);
		
		ft_print_pid();
		while (1)
		{
			if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1 || sigaction(SIGINT, &sa, NULL) == -1)
			{
				ft_putstr_fd("Error setting up signal handler\n", 1);
				exit(EXIT_FAILURE);
			}
			pause();
		}
			
	}
	else
	{
		ft_putstr_fd("Wrong input! Correct usage: ./server \n", 1);
		exit(EXIT_FAILURE);
	}
	return (0);
}
