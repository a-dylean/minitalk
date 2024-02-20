/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:44:58 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/20 11:49:39 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_data		g_data;

static void	ft_check_str(t_data *g_data, pid_t client_pid)
{
	if (g_data->bit_count == CHAR_SIZE_IN_BITS && g_data->flag == 1)
	{
		g_data->str[g_data->index] = g_data->data;
		g_data->index++;
		if (g_data->data == '\0')
		{
			ft_putstr_fd(g_data->str, STDOUT_FILENO);
			free(g_data->str);
			g_data->str = NULL;
			g_data->flag = 0;
			g_data->index = 0;
			ft_send_bit(client_pid, 0, 0);
		}
		g_data->bit_count = 0;
	}
}

static void	ft_check_length(t_data *g_data)
{
	if (g_data->bit_count == INT_SIZE_IN_BITS && g_data->flag == 0)
	{
		g_data->flag = 1;
		g_data->index = 0;
		g_data->str = malloc(g_data->data + 1);
		if (g_data->str == NULL)
			ft_handle_error("Malloc failed\n");
		g_data->str[g_data->index] = '\0';
		g_data->bit_count = 0;
	}
}

static void	ft_handle_client_signal(int signal, siginfo_t *info, void *context)
{
	usleep(SLEEP_TIME);
	(void)context;
	(void)info;
	if (g_data.bit_count == 0)
		g_data.data = 0;
	if (signal == SIGUSR1)
		g_data.data += 1 << (7 - g_data.bit_count);
	g_data.bit_count++;
	ft_check_length(&g_data);
	ft_check_str(&g_data, info->si_pid);
	ft_send_bit(info->si_pid, 1, 0);
}

static void	ft_set_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handle_client_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL)
		== -1)
		ft_handle_error("Error setting up signal handler\n");
}

int	main(int argc, char **argv)
{
	char	*server_pid;

	(void)argv;
	if (argc == 1)
	{
		ft_set_sigaction();
		server_pid = ft_itoa(getpid());
		ft_putstr_fd("Server PID: ", STDOUT_FILENO);
		ft_putstr_fd(server_pid, STDOUT_FILENO);
		free(server_pid);
		ft_putchar_fd('\n', STDOUT_FILENO);
		ft_putstr_fd("Waiting for the client...\n", STDOUT_FILENO);
		while (1)
			pause();
	}
	else
		ft_handle_error("Wrong input!\nCorrect usage: ./server \n");
	return (EXIT_SUCCESS);
}
