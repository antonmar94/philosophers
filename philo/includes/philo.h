/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:19:05 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/30 14:42:28 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <time.h>

typedef struct fork
{
	int				taken;
	pthread_mutex_t	mutex_fork;
}	t_fork;

typedef struct philo
{
	int				number;
	int				numeat;
	t_fork			*right_fork;
	int				dead;
	int				time_to_die;
	time_t			start;
	int				*time_left;
	int				count;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_toeat;
}	t_philo;
typedef struct philo_list
{
	t_philo				*philo;
	struct philo_list	*next;
	struct philo_list	*prev;
}	t_philist;

t_philo		*create_phil(char **argv);
t_philist	*create_pnode(char **argv);
t_philist	*create_plist(char **argv, int size);
void		print_plist(t_philist *plist, int size);
void		*ft_takefork(void *thread);
void		*ft_eat(void *thread);
void		*ft_sleep(void *thread);
void		*ft_think(void *thread);
void		ft_printer(t_philist *plist, char *str1, char *str2, int ded);
time_t		ft_thistime(void);
void		start_time(t_philist *plist, int size);
void		ft_usleep(t_philist *plist, int time);
int			ft_waiter(t_philist *plist, pthread_t philo, int time);
int			dead_counter(t_philist *plist, pthread_t philo, int time);
int			ft_test_error(int argc, char **argv);
int			ft_atoi(const char *str);
int			ft_plist_size(t_philist *plist);
int			ft_eatchecker(t_philist *plist);
int			ft_finisher(t_philist *plist, pthread_t philo);
int			ft_killp(t_philist *plist, pthread_t philo);
int			ft_take_leftfork(t_philist *plist);
int			ft_take_rightfork(t_philist *plist);

#endif        