/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/12 14:45:28 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_data		*data;

static void	ft_update_data(int signal)
{
	data->bit_count++;
	//printf("Queque: %d\n", ft_queue_is_full(data));
	//printf("Bit: %d\n", data->bit_count);
	if (ft_queue_is_full(data))
	{
		// if (data->str == NULL)
		// 	ft_extend_str(data);
		// if (data->str[data->len - 1] != '\0')
		// 	ft_extend_str(data);
		//ft_print_queue(data);
		// data->temp_char = ft_binary_to_char(data->buffer);
		// int i = 0;
		// while (data->str[i] != '\0')
		// 	i++;
		//data->str[i] = data->temp_char;
		//ft_reset_buffer(data->buffer);
		data->temp_char = ft_binary_to_char(data);
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
	//usleep(100);
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
