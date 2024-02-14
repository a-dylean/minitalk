/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:43:01 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/14 13:21:14 by atonkopi         ###   ########.fr       */
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
t_data	*ft_init_struct(int pid)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_putstr_fd("Error allocating memory\n", 1);
		exit(EXIT_FAILURE);
	}
	ft_init_queue(data);
	ft_init_data(data, pid);
	return (data);
}

void	ft_init_data(t_data *data, pid_t pid)
{
	int	i;

	if (data == NULL)
		return ;
	if (data->str != NULL)
		free(data->str);
	data->str = NULL;
	data->client_pid = pid;
	data->str_len = 0;
	data->power = 0;
	ft_init_queue(data);
	i = 0;
	while (i < CHAR_BIT)
	{
		data->buffer[i] = -1;
		i++;
	}
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

char	ft_binary_to_char(t_data *data)
{
	char	result;
	int		i;
	int		bit;

	i = CHAR_BIT - 1;
	result = 0;
	bit = 0;
	while (i >= 0)
	{
		bit = ft_dequeue(data);
		if (bit == 1)
			result += ft_pow(2, CHAR_BIT - 1 - i);
		i--;
	}
	return (result);
}

void	ft_extend_str(t_data *data)
{
	int		power;
	char	*newstr;
	int		len;

	power = data->power + 1;
	len = ft_pow(2, power);
	newstr = malloc(len);
	if (!newstr)
		exit(EXIT_FAILURE);
	ft_bzero(newstr, len);
	ft_memcpy(newstr, data->str, data->str_len);
	free(data->str);
	data->str = newstr;
	data->power = power;
	data->str_len = ft_pow(2, power);
}

void	ft_add_buffer_to_str(t_data *data)
{
	char c;
	int i;

	if (!data)
		return ;
	if (data->str == NULL)
		ft_extend_str(data);
	if (data->str[data->str_len - 1] != '\0')
		ft_extend_str(data);
	c = ft_binary_to_char(data);
	i = 0;
	while (data->str[i] != '\0')
		i++;
	data->str[i] = c;
	ft_init_queue(data);
	if (c == '\0')
	{
		ft_putstr_fd(data->str, 1);
		free(data->str);
		data->str = NULL;
		data->str_len = 0;
		data->power = 0;
	}
}