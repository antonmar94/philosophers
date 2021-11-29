/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:49:37 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/29 16:05:49 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	ft_thistime(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

void	ft_usleep(t_philist *plist, int time)
{
	int	this_time;

	this_time = ft_thistime() - plist->philo->start;
	while (ft_thistime() - plist->philo->start < this_time + time)
		usleep(100);
}

int	dead_counter(t_philist *plist, pthread_t philo, int time)
{
	int		time_over;
	time_t	start;
	time_t	sum;

	time_over = time;
	while (time_over > 0)
	{
		start = ft_thistime();
		ft_usleep(plist, 1);
		sum = ft_thistime() - start;
		*plist->philo->time_left += sum;
		if (ft_killp(plist, philo) == 1)
			return (0);
		time_over--;
	}
	return (1);
}

void	start_time(t_philist *plist, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		plist->next->philo->start = plist->philo->start;
		plist = plist->next;
		i++;
	}
}

int	ft_waiter(t_philist *plist, pthread_t philo, int time)
{
	int		time_over;
	time_t	start;
	time_t	sum;

	time_over = time;
	while (time_over > 0)
	{
		start = ft_thistime();
		usleep(10);
		sum = ft_thistime() - start;
		*plist->philo->time_left += sum;
		if (ft_killp(plist, philo) == 1)
			return (0);
		time_over--;
	}
	return (1);
}
