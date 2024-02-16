/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:43:01 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/16 16:40:47 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	ft_print_pid(void)
{
	char	*server_pid;

	server_pid = ft_itoa(getpid());
	ft_putstr_fd("Server PID: ", STDOUT_FILENO);
	ft_putstr_fd(server_pid, STDOUT_FILENO);
	free(server_pid);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_putstr_fd("Waiting for the client...\n", STDOUT_FILENO);
}

void	ft_send_signal(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
		ft_handle_error("Error sending signal\n");
}
t_data	*ft_init_struct(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_handle_error("Malloc failed\n");
	ft_init_queue(data);
	ft_init_data(data);
	return (data);
}

void	ft_init_data(t_data *data)
{
	int	i;

	if (data == NULL)
		return ;
	if (data->str != NULL)
		free(data->str);
	data->str = NULL;
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

// void	ft_print_queue(t_data *data)
// {
// 	for (int i = 0; i < CHAR_BIT; i++)
// 	{
// 		printf("Buffer[%d]: %d\n", i, data->buffer[i]);
// 	}
// }

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

void	ft_allocate_memory(t_data *data)
{
	int		power;
	char	*newstr;
	int		len;

	power = data->power + 1;
	len = ft_pow(2, power);
	newstr = malloc(len);
	if (!newstr)
		ft_handle_error("Malloc failed\n");
	ft_bzero(newstr, len);
	ft_memcpy(newstr, data->str, data->str_len);
	free(data->str);
	data->str = newstr;
	data->power = power;
	data->str_len = ft_pow(2, power);
}

void	ft_add_buffer_to_str(t_data *data)
{
	char	c;
	int		i;

	if (!data)
		return ;
	if (data->str == NULL)
		ft_allocate_memory(data);
	if (data->str[data->str_len - 1] != '\0')
		ft_allocate_memory(data);
	c = ft_binary_to_char(data);
	i = 0;
	while (data->str[i] != '\0')
		i++;
	data->str[i] = c;
	if (c == '\0')
	{
		ft_putstr_fd(data->str, STDOUT_FILENO);
		free(data->str);
		data->str = NULL;
		data->str_len = 0;
		data->power = 0;
	}
	ft_init_queue(data);
}

void	ft_handle_error(char *error_message)
{
	ft_putstr_fd(error_message, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}