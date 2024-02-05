/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:51 by atonkopi          #+#    #+#             */
/*   Updated: 2024/01/31 19:06:45 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minitalk.h"

static void	ft_send_char(pid_t pid, char c)
{
	int		i;
	char	bit;

	i = 8;
	while (i--)
	{
		bit = (c >> i) & 1;
		if (bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		pause();
		usleep(100);
	}
}

static void	ft_send_msg(pid_t pid, char *msg)
{
	if (!msg)
		return ;
	while (*msg != '\0')
	{
		ft_send_char(pid, *msg);
		msg++;
	}
	ft_send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_str_isnumeric(argv[1]))
	{
		ft_printf("ERROR\n");
		return (0);
	}
	//ft_printf("Client pid: %d\n", getpid());
	// signal(SIGUSR1, ft_handle_signal);
	// signal(SIGUSR2, ft_handle_signal);
	// ft_send_msg(spid, msg);
	while (1)
		pause();
}