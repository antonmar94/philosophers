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
