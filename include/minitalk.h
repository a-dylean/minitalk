/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:16:29 by atonkopi          #+#    #+#             */
/*   Updated: 2024/02/07 18:45:06 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>

void	ft_send_signal(pid_t pid, int signal);

#endif