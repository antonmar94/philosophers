/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:53:10 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/22 14:11:12 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_counter(void *element)
{
	t_philist 		*plist;
	struct timeval	start;
	struct timeval	end;

	plist = (t_philist *)element;
	while (1)
	{
		gettimeofday(&start, NULL);
		usleep(1000);
		gettimeofday(&end, NULL);
		*plist->philosopher->time_left -= ft_difftime(&start, &end);
		plist->philosopher->time += ft_difftime(&start, &end);
		if (*plist->philosopher->time_left <= 0)
			ft_die(plist);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philist			*plist;
	pthread_t			philosopher;
	pthread_t			time_pth;
	int					i;
	int					size;

	i = 0;
	
	if (!ft_test_error(argc, argv))
		exit (-1);
	size = ft_atoi(argv[1]);
	plist = create_plist(argv, size);
	print_plist(plist, size);
	while (i < size)
	{
		pthread_create(&philosopher, NULL, ft_phil_turnthread, plist);
		plist = plist->next;
		i++;
	}
	pthread_join(philosopher, NULL);
	return (0);
}
