/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:16:29 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/12 14:46:02 by atonkopi         ###   ########.fr       */
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
	int len;
	int power;
	int bit_count;
	char	temp_char;
	char *str;
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
char		ft_binary_to_char(t_data *data);
void	ft_extend_str(t_data *data);
// to remove
void		ft_print_queue(t_data *data);
#endif