/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:19:05 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/17 17:05:31 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H
# include <stdio.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>
# include <time.h>

typedef struct philosopher
{
	int				number;
	int				turn;
	pthread_mutex_t	right_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_toeat;
}	t_philosopher;
typedef struct philosopher_list
{
	t_philosopher			*philosopher;
	struct philosopher_list	*next;
	struct philosopher_list	*prev;
}	t_philist;
int				ft_test_error(char **argv);
t_philosopher	*create_phil(char **argv);
t_philist		*create_pnode(char **argv);
t_philist		*create_plist(char **argv, int size);
void			print_plist(t_philist *plist, int size);
void			ft_take_rightfork(t_philist *plist);
void			ft_take_leftfork(t_philist *plist);
void			ft_eat(t_philist *plist);
void			ft_sleep(t_philist *plist);
void			ft_think(t_philist *plist);
void			*ft_die(void *philosopher);
void			*ft_phil_turnthread(void *element);
void			*ft_phil_no_turnthread(void *element);
float			ft_difftime(struct timeval *start, struct timeval *end);

#endif        