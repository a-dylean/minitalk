/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:16:29 by atonkopi          #+#    #+#             */
/*   Updated: 2024/07/29 18:02:42 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>

# define INT_SIZE_IN_BITS 32
# define CHAR_SIZE_IN_BITS 8

# define SLEEP_TIME 100

typedef struct s_data
{
	int		bit_count;
	unsigned int		data;
	int		flag;
	char	*str;
	int		index;
}			t_data;

void	ft_send_signal(pid_t pid, int signal);
void	ft_send_int(pid_t pid, int num);
void	ft_send_char(pid_t pid, char c);
void	ft_send_bit(pid_t pid, char bit, char flag_to_pause);
void	ft_handle_error(char *error_message);

#endif