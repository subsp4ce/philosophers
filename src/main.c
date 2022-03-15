/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 14:57:34 by smiller       #+#    #+#                 */
/*   Updated: 2022/03/15 09:43:46 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo, int i)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->status_mutex);
	time = get_time();
	if (time == 0)
		return (ERROR);
	if (time - philo->data->start_time >= philo[i].time_started_eating
		+ philo->data->time_to_die)
	{
		if (philo->data->philo_died == TRUE)
			return (unlock(&philo->data->status_mutex, ERROR));
		time = time - philo->data->start_time;
		if (printf("%lu %d %s\n", time, philo->id, "died") < 0)
			return (unlock(&philo->data->status_mutex, ERROR));
		philo->data->philo_died = TRUE;
		pthread_mutex_unlock(&philo->data->status_mutex);
		return (ERROR);
	}
	pthread_mutex_unlock(&philo->data->status_mutex);
	return (SUCCESS);
}

int	one_philo(t_philo *philo)
{
	if (timer(philo->data->time_to_die) == ERROR)
		return (ERROR);
	printf("%llu %d %s\n", get_time()
		- philo->data->start_time, philo->id, "died");
	return (ERROR);
}

int	monitor_threads(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->num == 1)
		return (one_philo(philo));
	while (i < philo->data->num)
	{
		if (philo->data->must_eat != 0)
		{
			pthread_mutex_lock(&philo->data->full_mutex);
			if (philo->data->full_philos == philo->data->num)
				return (unlock(&philo->data->full_mutex, ERROR));
			pthread_mutex_unlock(&philo->data->full_mutex);
		}
		if (check_death(philo, i) == ERROR)
			return (ERROR);
		i++;
	}
	if (usleep(1500) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	launch_philo(t_data *data, t_philo *philo)
{
	int			i;

	i = 0;
	while (i < data->num)
	{
		philo[i].time_started_eating = data->start_time;
		if (pthread_create(&philo[i].th, NULL, &simulation, &philo[i]) != 0)
			return (thread_failure(data, philo, i));
		i++;
	}
	while (data->res != ERROR)
		data->res = monitor_threads(philo);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	t_philo	*philo;

	philo = NULL;
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (ERROR);
	if (parse_input(argc, argv, data) == ERROR)
	{
		free(data);
		return (ERROR);
	}
	philo = init(data);
	if (philo == NULL)
	{
		free(data);
		return (ERROR);
	}
	if (launch_philo(data, philo) == ERROR)
		return (ERROR);
	join_and_destroy(data, philo);
	free_all(philo);
	return (SUCCESS);
}
