/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/13 14:42:47 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_data	*data;

void	ft_add_char_to_str(t_data *data, char c)
{
	if (c == '\0')
	{
		//printf("str: %s\n", data->str);
		ft_putstr_fd(data->str, 1);
		free(data->str);
		data->str_len = 0;
		ft_init_queue(data);
	}
	if (data->str_len == 0)
	{
		ft_strlcpy(data->str, &c, 2);
		data->str_len++;
	}
	else
	{
		char *new_str = malloc((data->str_len + 2));
		if (new_str)
		{
			if (data->str)
			{
				ft_strlcpy(new_str, data->str, data->str_len + 2);
				
			}
			//printf("new_str1: %s\n", new_str);
			new_str[data->str_len] = c;
			new_str[data->str_len + 1] = '\0';
			//free(data->str);
			data->str = new_str;
			//printf("new_str2: %s\n", data->str);
			data->str_len++;
			//free(new_str);
		}
	}
}

	static void ft_update_data(int signal)
	{
		char temp_char;
		// ft_print_queue(data);
		ft_enqueue(data, signal);
		if (ft_queue_is_full(data))
		{
			temp_char = ft_binary_to_char(data);
			//printf("temp_char: %c\n", temp_char);
			ft_add_char_to_str(data, temp_char);
			ft_init_queue(data);
		}
		if (signal)
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		//ft_send_signal(data->client_pid, signal);
		usleep(100);
	}

	static void ft_handle_client_signal(int signal, siginfo_t *info,
		void *context)
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

	int main(int argc, char **argv)
	{
		struct sigaction sa;

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
