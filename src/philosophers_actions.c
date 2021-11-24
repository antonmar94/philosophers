/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:44:07 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/24 19:59:39 by antonmar         ###   ########.fr       */
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
	ft_printer(plist, "\033[0;32mPhilosopher", "has taken a fork");
	ft_take_leftfork(plist);
}

void	ft_take_leftfork(void *thread)
{
	t_philist 	*plist;

	plist = (t_philist *)thread;
	ft_printer(plist, "\033[0;36mPhilosopher", "is thinking");
	plist->philosopher->turn = 0;
	pthread_mutex_lock(&(plist->prev->philosopher->right_fork));
	ft_printer(plist, "\033[0;32mPhilosopher", "has taken a fork");
	ft_eat(plist);
}

void	ft_eat(void *thread)
{
	static	int		philo_fed;
	t_philist 		*plist;

	plist = (t_philist *)thread;
	ft_printer(plist, "\033[0;33mPhilosopher", "is eating");
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
	ft_printer(plist, "\033[0;34mPhilosopher", "is sleeping");
	plist->philosopher->turn = 1;
	usleep(plist->philosopher->time_to_sleep * 1000);
	ft_think(plist);
}

void	*ft_think(void *thread)
{
	t_philist 	*plist;

	plist = (t_philist *)thread;
	ft_printer(plist, "\033[0;36mPhilosopher", "is thinking");
	if (plist->philosopher->turn)
		ft_take_rightfork(plist);
	else
		ft_sleep(plist);
	return (NULL);
}

void	kill_them_all(void *thread) //tengo que matarlos y que pare
{
	t_philist 	*plist;
	plist = (t_philist *)thread;
	pthread_detach(thread);
}

void	*ft_die(void *thread) //tengo que matarlos y que pare
{
	t_philist 	*plist;

	plist = (t_philist *)thread;
	ft_printer(plist, "\033[0;35mPhilosopher", "died");
	pthread_detach(thread);
	kill_them_all(thread);
	return (NULL);
}

void	ft_printer(t_philist *plist, char *str1, char *str2)
{
	static pthread_mutex_t	printing = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&printing);
	printf("%li ", ft_thistime() - plist->philosopher->start);
	printf("%s %i",str1,  plist->philosopher->number);
	printf(" %s\n\033[0m", str2);
	pthread_mutex_unlock(&printing);
}
