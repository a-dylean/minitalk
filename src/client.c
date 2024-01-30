/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:51 by atonkopi          #+#    #+#             */
/*   Updated: 2024/01/30 14:17:21 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minitalk.h"

// void	error(int pid, char *str)
// {
// 	if (str)
// 		free(str);
// 	ft_printf("server: unexpected error.\n");
// 	kill(pid, SIGUSR2);
// 	exit(EXIT_FAILURE);
// }

int	send_null(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			error(str);
		return (0);
	}
	return (1);
}

int	send_bit(int pid, char *str)
{
	static char	*message = 0;
	static int	s_pid = 0;
	static int	bits = -1;

	if (str)
		message = ft_strdup(str);
	if (!message)
		error(0);
	if (pid)
		s_pid = pid;
	if (message[++bits / 8])
	{
		if (message[bits / 8] & (0x80 >> (bits % 8)))
		{
			if (kill(s_pid, SIGUSR2) == -1)
				error(message);
		}
		else if (kill(s_pid, SIGUSR1) == -1)
			error(message);
		return (0);
	}
	if (!send_null(s_pid, message))
		return (0);
	free(message);
	return (1);
}

int	main(int argc, char **argv)
{
	//handle invalid input with a condition like this:
	// if (argc != 3 || !ft_str_isnumeric(argv[1]))
	ft_printf("%d\n", argc);
	ft_printf("%s\n", argv[0]);
	ft_printf("Client pid: %d\n", getpid());
	// signal(SIGUSR1, handler_sigusr);
	// signal(SIGUSR2, handler_sigusr);
	// send_bit(ft_atoi(argv[1]), argv[2]);
	// while (1)
	// 	pause();
}