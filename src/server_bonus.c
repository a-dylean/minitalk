/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/09 18:57:21 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_data		*data;

static void	ft_update_data(int signal)
{
	if (ft_queue_is_full(data))
	{
		//ft_print_queue(data);
		data->temp_char = ft_binary_to_char(data->buffer);
		//printf("temp_char: %c\n", data->temp_char);
		if (data->temp_char != '\0')
		{
			ft_putchar_fd(data->temp_char, 1);
			signal = SIGUSR1;
		}
		else
			signal = SIGUSR2;
		ft_send_signal(data->client_pid, signal);
		usleep(100);
		// while (!ft_queue_is_empty(data))
		// 	ft_dequeue(data);
		ft_init_queue(data);
		//data->temp_char = '\0';
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
	
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc == 1)
	{
		data = ft_init_data();
		//int arr[CHAR_BIT] = {0,1,1,0,0,0,0,1};
		//printf("Char: %c\n", ft_binary_to_char(arr));
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
