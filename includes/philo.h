/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 14:56:41 by smiller       #+#    #+#                 */
/*   Updated: 2022/03/11 12:29:58 by swaanmiller   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR -1
# define TRUE 1
# define FALSE 0
# define EATING 2

typedef struct s_data
{
	int					num;
	int					philo_died;
	int					full_philos;
	int					error;
	int					res;
	int					must_eat;
	unsigned long long	start_time;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	pthread_mutex_t		*fork;
	pthread_mutex_t		full_mutex;
	pthread_mutex_t		status_mutex;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					eaten;
	pthread_t			th;
	int					res;
	unsigned long long	time_started_eating;
	struct s_data		*data;
}						t_philo;

/* simulation.c */
void				*simulation(void *data);

/* ft.c */
int					ft_is_whitespace(int c);
int					ft_is_digit(int c);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
int					ft_strlen(char *str);

/* utils.c */
int					print_lock(t_philo *philo, char *str,
						unsigned long long status);
int					timer(unsigned long long ms);
unsigned long long	get_time(void);
int					unlock(pthread_mutex_t *mutex, int error);
void				join_and_destroy(t_data *data, t_philo *philo);

/* parse_init.c */
int					parse_input(int argc, char **argv, t_data *philo);
t_philo				*init(t_data *data);

/* error_free.c */
int					print_error(char *str);
t_philo				*free_all(t_philo *philo);
t_philo				*free_and_destroy_forks(t_philo *philo, int i);
int					thread_failure(t_data *data, t_philo *philo, int i);

#endif
