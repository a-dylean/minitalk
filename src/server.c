/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/01/30 14:17:06 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int signum)
{
	ft_printf("Received SIGINT %d!\n", signum);
	exit(0);
}
int	main(void)
{
	__pid_t	pid;

	pid = getpid();
	ft_printf("Server pid: %d\n", pid);
	// signal(SIGINT, signal_handler);
	// while (1)
	// {
	// 	ft_printf("hello");
	// 	sleep(1);
	// }
}
