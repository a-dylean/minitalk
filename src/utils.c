/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:43:01 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/09 19:01:50 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	ft_print_pid(void)
{
	char	*server_pid;

	server_pid = ft_itoa(getpid());
	ft_putstr_fd("Server PID: ", 1);
	ft_putstr_fd(server_pid, 1);
	free(server_pid);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Waiting for the client...\n", 1);
}

void	ft_send_signal(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		ft_putstr_fd("Error sending signal\n", 1);
		exit(EXIT_FAILURE);
	}
}
t_data	*ft_init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_putstr_fd("Error allocating memory\n", 1);
		exit(EXIT_FAILURE);
	}
	// for (int i = 0; i < CHAR_BIT; i++) {
	// 	data->buffer[i] = -1;
	// }
	return (data);
}
void	ft_init_queue(t_data *data)
{
	data->start = 0;
	data->end = 0;
}

int	ft_dequeue(t_data *data)
{
	return (data->buffer[data->start++]);
}

void	ft_enqueue(t_data *data, int bit)
{
	data->buffer[data->end] = bit;
	data->end++;
}

int	ft_queue_is_empty(t_data *data)
{
	return (data->start == data->end);
}
int	ft_queue_is_full(t_data *data)
{
	return (data->end == CHAR_BIT);
}

void	ft_print_queue(t_data *data)
{
	for (int i = 0; i < CHAR_BIT; i++)
	{
		printf("Buffer[%d]: %d\n", i, data->buffer[i]);
	}
}

int	ft_pow(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_pow(nb, power - 1));
}

void ft_reverse_buffer(int *buffer)
{
	int i;
	int j;
	int temp;

	i = 0;
	j = CHAR_BIT - 1;
	while (i < j)
	{
		temp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = temp;
		i++;
		j--;
	}
}
char	ft_binary_to_char(int *buffer)
{
	char result;
	int i;
	
	i = 7;
	result = 0;
	//ft_reverse_buffer(buffer);
	while (i >= 0)
	{
		if (buffer[i] == 1)
			result += ft_pow(2, CHAR_BIT - 1 - i);
		i--;
	}
	return (result);
}