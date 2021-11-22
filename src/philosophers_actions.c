/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:44:07 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/22 13:56:49 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_phil_turnthread(void *element)
{
	t_philist 	*plist;

	plist = (t_philist *)element;
	pthread_create(&plist->philosopher->phil_die, NULL, ft_counter, plist);
	ft_think(plist);
	return (NULL);
}

void	ft_take_rightfork(void *thread)
{
	t_philist 	*plist;

	plist = (t_philist *)thread;
	pthread_mutex_lock(&(plist->philosopher->right_fork));
	printf("%i \033[0;32mPhilosopher %i has taken a fork\n\033[0m",
	plist->philosopher->time, plist->philosopher->number);
	ft_take_leftfork(plist);
	
}

void	ft_take_leftfork(void *thread)
{
	t_philist 	*plist;

	plist = (t_philist *)thread;
	printf("%i \033[0;36mPhilosopher %i is thinking\n\033[0m",
	plist->philosopher->time, plist->philosopher->number);
	plist->philosopher->turn = 0;
	pthread_mutex_lock(&(plist->prev->philosopher->right_fork));
	printf("%i \033[0;32mPhilosopher %i has taken a fork\n\033[0m",
	plist->philosopher->time, plist->philosopher->number);
	ft_eat(plist);
}

void	ft_eat(void *thread)
{
	static	int		philo_fed;
	t_philist 		*plist;

	plist = (t_philist *)thread;
	printf("%i \033[0;33mPhilosopher %i is eating\n\033[0m",
	plist->philosopher->time, plist->philosopher->number);
	*plist->philosopher->time_left = plist->philosopher->time_to_die;
	usleep(plist->philosopher->time_to_eat * 1000);
	plist->philosopher->number_of_times_toeat--;
	if (plist->philosopher->number_of_times_toeat == 0)
		philo_fed++;
	if (philo_fed == ft_plist_size(plist))
		exit(0);
	pthread_mutex_unlock(&(plist->philosopher->right_fork));
	pthread_mutex_unlock(&(plist->prev->philosopher->right_fork));
	ft_sleep(plist);
}

void	ft_sleep(void *thread)
{
	t_philist 	*plist;

	plist = (t_philist *)thread;
	printf("%i \033[0;34mPhilosopher %i is sleeping\n\033[0m",
	plist->philosopher->time, plist->philosopher->number);
	plist->philosopher->turn = 1;
	usleep(plist->philosopher->time_to_sleep * 1000);
	ft_think(plist);
}

void	*ft_think(void *thread)
{
	t_philist 	*plist;

	plist = (t_philist *)thread;
	printf("%i \033[0;36mPhilosopher %i is thinking\n\033[0m",
	plist->philosopher->time, plist->philosopher->number);
	if (plist->philosopher->turn)
		ft_take_rightfork(plist);
	else
		ft_sleep(plist);
	return (NULL);
}

void	kill_them_all(void *thread)
{
	t_philist 	*plist;

	plist = (t_philist *)thread;
	pthread_detach(thread);
	exit(0);
}

void	ft_die(void *thread)
{
	t_philist 	*plist;

	plist = (t_philist *)thread;
	printf("%i \033[0;35mPhilosopher %i died\n\033[0m",
	plist->philosopher->time, plist->philosopher->number);
	kill_them_all(thread);
	exit (0);
}
