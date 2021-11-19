/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:19:05 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/19 18:05:14 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H
# include <stdio.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <time.h>

typedef struct philosopher
{
	int				number;
	int				turn;
	pthread_mutex_t	right_fork;
	int				time;		
	int				time_to_die;
	pthread_t		phil_die;
	int				time_left;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_toeat;
	int				exit;
}	t_philosopher;
typedef struct philosopher_list
{
	t_philosopher			*philosopher;
	struct philosopher_list	*next;
	struct philosopher_list	*prev;
}	t_philist;
int				ft_test_error(int argc, char **argv);
t_philosopher	*create_phil(char **argv);
t_philist		*create_pnode(char **argv);
t_philist		*create_plist(char **argv, int size);
void			print_plist(t_philist *plist, int size);
int				ft_plist_size(t_philist *plist);
void			ft_take_rightfork(void *thread);
void			ft_take_leftfork(void *thread);
void			ft_eat(void *thread);
void			ft_sleep(void *thread);
void			ft_think(void *thread);
void			ft_die(void *thread);
void			*ft_phil_turnthread(void *element);
void			*ft_phil_no_turnthread(void *element);
float			ft_difftime(struct timeval *start, struct timeval *end);
void			kill_them_all(void *thread);
void			*ft_dead_counter(void *element);
void			asign_parity(t_philist *plist, int size);

#endif        