/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:53:10 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/29 16:05:53 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_plist(t_philist *plist, int size)
{
	int			i;
	t_philist	*aux;

	i = 0;
	aux = plist;
	printf("\n");
	printf("\033[0;31m%65s", " 📚 philo 📚 ");
	printf("\n");
	printf("\033[0;31m%57s", "------------\n");
	while (i < size)
	{
		printf("\033[0mphilo %-3i", i + 1);
		printf("\033[0;32mnumber: \033[0m%-3i",
			aux->philo->number);
		printf("\033[0;35mtime to die: \033[0m[%d] ",
			aux->philo->time_to_die);
		printf("\033[0;33mtime to eat: \033[0m[%i] ",
			aux->philo->time_to_eat);
		printf("\033[0;34mtime to sleep: \033[0m[%i] ",
			aux->philo->time_to_sleep);
		printf("\033[0;36mnumber of times to eat: \033[0m[%i]\n ",
			aux->philo->number_of_times_toeat);
		aux = aux->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philist			*plist;
	pthread_t			philo;
	int					i;
	int					size;

	i = 0;
	if (!ft_test_error(argc, argv))
		return (-1);
	size = ft_atoi(argv[1]);
	if (!size)
		return (-1);
	plist = create_plist(argv, size);
	plist->philo->start = ft_thistime();
	start_time(plist, size);
	while (i < size)
	{
		pthread_create(&philo, NULL, ft_takefork, plist);
		plist = plist->next;
		i++;
	}
	if (!ft_finisher(plist, philo))
		return (0);
	pthread_join(philo, NULL);
	return (0);
}
