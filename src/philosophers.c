/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:53:10 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/27 18:05:49 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_philist			*plist;
	pthread_t			philosopher;
	int					i;
	int					size;

	i = 0;
	if (!ft_test_error(argc, argv))
		return (-1);
	size = ft_atoi(argv[1]);
	if (!size)
		return (-1);
	plist = create_plist(argv, size);
	plist->philosopher->start = ft_thistime();
	start_time(plist, size);
	while (i < size)
	{
		pthread_create(&philosopher, NULL, ft_think, plist);
		plist = plist->next;
		i++;
	}
	if (ft_checker(plist, philosopher) == 0)
		return (0);
	pthread_join(philosopher, NULL);
	return (0);
}
