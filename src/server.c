/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:34:45 by atonkopi          #+#    #+#             */
/*   Updated: 2024/01/29 16:20:16 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <signal.h>

void	signal_handler(int signum)
{
	ft_printf("Received SIGINT!\n", signum);
	exit(0);
}

int	main(void)
{
	__pid_t	pid;

	pid = getpid();
	ft_printf("Server pid: %d\n", pid);
    sleep(10);
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
}
