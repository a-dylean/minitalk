/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:16:29 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/09 18:55:57 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>

typedef struct t_data
{
	int		buffer[CHAR_BIT];
	int		start;
	int		end;
	int bit_count;
	char	temp_char;
	pid_t	client_pid;
}			t_data;
void		ft_print_pid(void);
void		ft_send_signal(pid_t pid, int signal);
void		ft_init_queue(t_data *data);
t_data		*ft_init_data(void);
int			ft_dequeue(t_data *data);
void		ft_enqueue(t_data *data, int bit);
int			ft_queue_is_empty(t_data *data);
int			ft_queue_is_full(t_data *data);
int			ft_pow(int nb, int power);
char		ft_binary_to_char(int *buffer);
// to remove
void		ft_print_queue(t_data *data);
void ft_reverse_buffer(int *buffer);
#endif