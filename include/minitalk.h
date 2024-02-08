/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:16:29 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/08 14:44:31 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>

void				ft_send_signal(pid_t pid, int signal);

typedef struct t_node
{
	int			bit;
	struct t_node	*next;
}					t_node;

t_node	*ft_init_queue(void);
int ft_dequeue (t_node *symbol);
t_node *ft_enqueue (int i, t_node *head_symbol);
int ft_queue_is_empty(t_node *queue);
void ft_print_queue(t_node *queue);

#endif