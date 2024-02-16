/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/16 16:27:40 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_data	*g_data;

void	ft_update_data(pid_t client_pid, int signal)
{
	(void)client_pid;
	// if (data->client_pid != client_pid)
	// 	data->client_pid = client_pid;
	ft_enqueue(g_data, signal);
	if (ft_queue_is_full(g_data))
		ft_add_buffer_to_str(g_data);
	if (signal)
		ft_send_signal(client_pid, SIGUSR1);
	else
		ft_send_signal(client_pid, SIGUSR2);
}

void	ft_handle_client_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (signal == SIGUSR1)
		ft_update_data(info->si_pid, 1);
	else if (signal == SIGUSR2)
		ft_update_data(info->si_pid, 0);
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
		g_data = ft_init_struct();
		ft_print_pid();
		while (1)
			pause();
	}
	else
		ft_handle_error("Wrong input!\nCorrect usage: ./server \n");
	return (EXIT_SUCCESS);
}
