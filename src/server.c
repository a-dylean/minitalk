/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:44:58 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/15 18:28:53 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	server_is_message_finished(
	t_data *data, pid_t client_pid)
{
	if (data->flag == 1 && data->bit_count == 8)
	{
		data->message[data->index] = data->data;
		data->index++;
		if (data->data == '\0')
		{
			ft_putstr_fd(data->message, STDOUT_FILENO);
			free(data->message);
			data->message = NULL;
			data->flag = 0;
			data->index = 0;
			send_bit(client_pid, 1, 0);
		}
		data->bit_count = 0;
	}
}

static void	server_is_str_length_finished(t_data *data)
{
	if (data->bit_count == sizeof(int) * 8 && data->flag == 0)
	{
		data->flag = 1;
		data->index = 0;
		data->message = malloc(data->data + 1);
		if (data->message == NULL)
			ft_handle_error("Malloc failed\n");
		data->message[data->index] = '\0';
		data->bit_count = 0;
		
	}
}

static void	ft_handle_client_signal(int num, siginfo_t *info, void *context)
{
	static t_data	data;

	usleep(100);
	(void)context;
	(void)info;
	if (data.bit_count == 0)
		data.data = 0;
	if (num == SIGUSR2 && data.flag == 0)
		data.data += 1 << (7 - data.bit_count);
	else if (num == SIGUSR2 && data.flag == 1)
		data.data += 1 << (7 - data.bit_count);
	data.bit_count++;
	server_is_str_length_finished(&data);
	server_is_message_finished(&data, info->si_pid);
	send_bit(info->si_pid, 0, 0);
}

static void	ft_set_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO  | SA_RESTART;
	sa.sa_sigaction = ft_handle_client_signal;
	
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) ==
		-1)
		ft_handle_error("Error setting up signal handler\n");
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
	{
		ft_set_sigaction();
		ft_print_pid();
		while (1)
			pause();
	}
	else
		ft_handle_error("Wrong input!\nCorrect usage: ./server \n");
	return (EXIT_SUCCESS);
}
