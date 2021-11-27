/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_time_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:49:37 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/27 19:50:06 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

time_t	ft_thistime(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

void	ft_usleep(t_philist *plist, int time)
{
	int	this_time;

	this_time = ft_thistime() - plist->philosopher->start;
	while (ft_thistime() - plist->philosopher->start < this_time + time)
		usleep(100);
}

void	start_time(t_philist *plist, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		plist->next->philosopher->start = plist->philosopher->start;
		plist = plist->next;
		i++;
	}
}
