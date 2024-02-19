/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/16 16:57:04 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	server_is_message_finished(
	t_protocol *t_server, pid_t client_pid)
{
	int i;
	i = 0;
	if (t_server->bits == 8 && t_server->flag == 1)
	{
		t_server->message[i] = t_server->data;
		i++;
		if (t_server->data == '\0')
		{
			ft_putstr_fd(t_server->message, STDOUT_FILENO);
			free(t_server->message);
			t_server->message = NULL;
			t_server->flag = 0;
			i = 0;
			send_bit(client_pid, 1, 0);
		}
		t_server->bits = 0;
	}
}

static void	server_is_str_length_finished(t_protocol *t_server)
{
	if (t_server->bits == sizeof(int) * 8 && t_server->flag == 0)
	{
		t_server->flag = 1;
		ft_putnbr_fd(t_server->data, STDOUT_FILENO);
		t_server->message = ft_calloc(t_server->data + 1, sizeof(char));
		if (t_server->message == NULL)
			ft_handle_error("Malloc failed\n");
		t_server->message[t_server->data] = '\0';
		t_server->bits = 0;
	}
}

static void	ft_handle_client_signal(int signal, siginfo_t *info, void *context)
{
	static t_protocol	t_server;

	usleep(100);
	(void)context;
	(void)info;
	// printf("BITS: %d\n", t_server.bits);
	// printf("DATA: %d\n", t_server.data);
	// printf("message: %s\n", t_server.message);
	if (t_server.bits == 0)
		t_server.data = 0;
	if (signal == SIGUSR2 && t_server.flag == 0)
		t_server.data |= 1 << (((sizeof(int) * 8) - 1) - t_server.bits);
	else if (signal == SIGUSR2 && t_server.flag == 1)
		t_server.data |= 1 << (((sizeof(char) * 8) - 1) - t_server.bits);
	t_server.bits++;


	server_is_str_length_finished(&t_server);
	server_is_message_finished(&t_server, info->si_pid);
	send_bit(info->si_pid, 0, 0);
}
static void	ft_set_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handle_client_signal;
	
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) ==
		-1)
		ft_handle_error("Error setting up signal handler\n");
}

int	main(int argc, char **argv)
{
	(void)argv;
	ft_set_sigaction();
	if (argc == 1)
	{
		ft_print_pid();
		while (1)
			pause();
	}
	else
		ft_handle_error("Wrong input!\nCorrect usage: ./server \n");
	return (EXIT_SUCCESS);
}
