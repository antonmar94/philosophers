/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:53:10 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/19 18:15:37 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_dead_counter(void *element)
{
	t_philosopher 	*philo;
	struct timeval	start;
	struct timeval	end;
	int				imdead;

	philo = (t_philosopher *)element;
	imdead = philo->time;
	philo->exit = 0;
	philo->time_left = philo->time_to_die;
	//printf("cuenta atras %i\n", philo->time);
	//printf("cuenta atras %i\n", philo->time_left);
	while (philo->exit == 0)
	{
		gettimeofday(&start, NULL);
		usleep(1000);
		gettimeofday(&end, NULL);
		philo->time_left -= ft_difftime(&start, &end);
		imdead += ft_difftime(&start, &end);
		//printf("cuenta atras %i", philo->time_left);
		//printf("cuenta atras %i", philo->time_left);

		//printf("cuenta atras %i\n", philo->time);
		if (philo->time_left <= 0)
		{
			printf("\033[0m%i \033[0;35mPhilosopher %i died\n",
			imdead, philo->number);
			exit(0);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{ 
	t_philist			*list;
	pthread_t			philosopher;
	int					i;
	int					size;

	i = 0;
	if (!ft_test_error(argc, argv))
		exit (-1);
	size = ft_atoi(argv[1]);
	list = create_plist(argv, size);
	print_plist(list, size);
	while (i < size)
	{
		if (list->philosopher->turn)
			pthread_create(&philosopher, NULL, ft_phil_turnthread, list);
		else
			pthread_create(&philosopher, NULL, ft_phil_no_turnthread, list);
		list = list->next;
		i++;
	}
	pthread_join(philosopher, NULL);
	return (0);
}
