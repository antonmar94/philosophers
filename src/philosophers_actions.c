/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:44:07 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/18 18:25:15 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_phil_turnthread(void *element)
{
	t_philist 	*plist;

	plist = (t_philist *)element;
	ft_take_rightfork(plist);
	return (NULL);
}

void	*ft_phil_no_turnthread(void *element)
{
	t_philist 	*plist;

	plist = (t_philist *)element;
	ft_sleep(plist);
	return (NULL);
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void	ft_take_rightfork(void *thread)
{
	struct timeval	start;
	struct timeval	end;
	t_philist 	*plist;

	plist = (t_philist *)thread;
	gettimeofday(&start, NULL);
	while (pthread_mutex_lock(&(plist->philosopher->right_fork)) != 0)
	{
		usleep(1000);
		plist->philosopher->time_left--;
		if (plist->philosopher->time_left == 0)
			ft_die(plist);
	}
	gettimeofday(&end, NULL);
	plist->philosopher->time += ft_difftime(&start, &end);
	printf("\033[0m%i \033[0;32mPhilosopher %i has taken a fork\n",
	plist->philosopher->time, plist->philosopher->number);
	ft_take_leftfork(plist);
}

void	ft_take_leftfork(void *thread)
{
	struct timeval	start;
	struct timeval	end;
	t_philist 	*plist;

	plist = (t_philist *)thread;
	gettimeofday(&start, NULL);
	while (pthread_mutex_lock(&(plist->prev->philosopher->right_fork)) != 0)
	{
		usleep(1000);
		plist->philosopher->time_left--;
		if (plist->philosopher->time_left == 0)
			ft_die(plist);
	}
	gettimeofday(&end, NULL);
	plist->philosopher->time += ft_difftime(&start, &end);
	printf("\033[0m%i \033[0;32mPhilosopher %i has taken a fork\n",
	plist->philosopher->time, plist->philosopher->number);
	ft_eat(plist);
}

void	ft_eat(void *thread)
{
	struct timeval	start;
	struct timeval	end;
	static	int		philo_fed;
	t_philist 	*plist;

	plist = (t_philist *)thread;
	printf("\033[0m%i \033[0;33mPhilosopher %i is eating\n",
	plist->philosopher->time, plist->philosopher->number);
	gettimeofday(&start, NULL);
	plist->philosopher->time_left = plist->philosopher->time_to_die;
	usleep(plist->philosopher->time_to_eat * 1000);
	plist->philosopher->number_of_times_toeat--;
	if (plist->philosopher->number_of_times_toeat == 0)
		philo_fed++;
	if (philo_fed == ft_plist_size(plist))
		exit(0);
	pthread_mutex_unlock(&(plist->philosopher->right_fork));
	pthread_mutex_unlock(&(plist->prev->philosopher->right_fork));
	gettimeofday(&end, NULL);
	plist->philosopher->time += ft_difftime(&start, &end);
	ft_sleep(plist);
}

void	ft_sleep(void *thread)
{
	struct timeval	start;
	struct timeval	end;
	int				i;
	t_philist 	*plist;

	plist = (t_philist *)thread;
	i = 0;
	printf("\033[0m%i \033[0;34mPhilosopher %i is sleeping\n",
	plist->philosopher->time, plist->philosopher->number);
	gettimeofday(&start, NULL);
	while (i < plist->philosopher->time_to_sleep)
	{
		usleep(1000);
		plist->philosopher->time++;
		plist->philosopher->time_left--;
		if (plist->philosopher->time_left == 0)
			ft_die(plist);
		i++;
	}
	gettimeofday(&end, NULL);
	plist->philosopher->time += ft_difftime(&start, &end);
	ft_think(plist);
}

void	ft_think(void *thread)
{
	t_philist 	*plist;

	plist = (t_philist *)thread;
	printf("\033[0m%i \033[0;36mPhilosopher %i is thinking\n",
	plist->philosopher->time, plist->philosopher->number);
	ft_phil_turnthread(&plist->philosopher);
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
	printf("\033[0m%i \033[0;35mPhilosopher %i died\n",
	plist->philosopher->time, plist->philosopher->number);
	kill_them_all(thread);
}
