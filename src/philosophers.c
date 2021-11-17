/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:53:10 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/17 17:07:58 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"



int	main(int argc, char **argv)
{
	t_philist			*list;
	pthread_t			philosopher;
	int					i;
	int					size;
	//struct timeval	start;
	//struct timeval	end;
	i = 0;
	if (argc < 5 || argc > 6)
	{
		write(1, "Error, wrong number of arguments\n", 34);
		exit (-1);
	}
	if (!ft_test_error(argv))
	{
		write(1, "Error, wrong argument\n", 25);
		exit (-1);
	}
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
	i = 0;
	pthread_join(philosopher, NULL);
	/*gettimeofday(&start, NULL); //lo del tiempo no se como funciona
	printf("tiempo: %0.2f Philosopher %i is eating\n", ft_difftime(&start, &end), list->philosopher->number);
	gettimeofday(&end, NULL);*/
	return (0);
}
