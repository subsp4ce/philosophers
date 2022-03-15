/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 14:57:58 by smiller       #+#    #+#                 */
/*   Updated: 2022/03/11 11:12:51 by swaanmiller   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	join_and_destroy(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num)
	{
		pthread_join(philo[i].th, NULL);
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->full_mutex);
	pthread_mutex_destroy(&data->status_mutex);
}

int	unlock(pthread_mutex_t *mutex, int value)
{
	pthread_mutex_unlock(mutex);
	return (value);
}

int	print_lock(t_philo *philo, char *str, unsigned long long status)
{
	unsigned long long	time;

	pthread_mutex_lock(&philo->data->status_mutex);
	if (philo->data->philo_died == TRUE)
		return (unlock(&philo->data->status_mutex, ERROR));
	else
	{
		time = get_time();
		if (time == 0)
			return (unlock(&philo->data->status_mutex, ERROR));
		time = time - philo->data->start_time;
		if (printf("%llu %d %s\n", time, philo->id, str) < 0)
			return (unlock(&philo->data->status_mutex, ERROR));
		if (status == EATING)
			philo->time_started_eating = time;
		pthread_mutex_unlock(&philo->data->status_mutex);
	}
	return (SUCCESS);
}

unsigned long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == ERROR)
		return (0);
	return (((time.tv_sec) * 1000) + ((time.tv_usec) / 1000));
}

int	timer(unsigned long long ms)
{
	unsigned long long	time;

	time = get_time();
	if (time == 0)
		return (ERROR);
	while ((get_time() - time) < ms)
	{
		if (usleep(500) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
