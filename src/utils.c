/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:43:01 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/08 14:56:14 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	ft_send_signal(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		ft_putstr_fd("Error sending signal\n", 1);
		exit(EXIT_FAILURE);
	}
}

t_node	*ft_init_queue(void)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	//new_node->bit = i;
	new_node->next = new_node;
	return (new_node);
}


int ft_dequeue (t_node *symbol) 
{
   t_node *symbol_to_remove;
   int i;
   
   symbol_to_remove = symbol->next;
   i = symbol_to_remove->bit;
   symbol->next = symbol_to_remove->next;
   free (symbol_to_remove);
   return i;  
}

t_node *ft_enqueue (int i, t_node *head_symbol) 
{ 
   t_node *new_symbol;
   
   new_symbol = malloc (sizeof (t_node));
   if (!new_symbol)
	return (NULL);
   new_symbol->next = head_symbol->next;
   head_symbol->next = new_symbol;
   head_symbol->bit = i;
   return new_symbol;
}

int ft_queue_is_empty(t_node *queue)
{
	if (queue->next == queue)
		return (1);
	return (0);
}

void ft_print_queue(t_node *queue)
{
	t_node *current;
	current = queue->next;
	while (current != queue)
	{
		ft_putnbr_fd(current->bit, 1);
		ft_putchar_fd(' ', 1);
		current = current->next;
	}
	ft_putchar_fd('\n', 1);
}