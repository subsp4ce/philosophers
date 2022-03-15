/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 14:57:50 by smiller       #+#    #+#                 */
/*   Updated: 2022/03/15 09:43:33 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	unlock_forks(t_philo *philo, int right, int left)
{
	pthread_mutex_unlock(&philo->data->fork[left]);
	pthread_mutex_unlock(&(philo->data->fork[right]));
	return (ERROR);
}

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->status_mutex);
	if (philo->data->philo_died == FALSE)
		return (unlock(&philo->data->status_mutex, TRUE));
	pthread_mutex_unlock(&philo->data->status_mutex);
	return (FALSE);
}

int	eating(t_philo *philo, int right, int left)
{
	pthread_mutex_lock(&philo->data->fork[left]);
	if (print_lock(philo, "has taken a fork", 0) == ERROR)
		return (unlock(&philo->data->fork[left], ERROR));
	if (philo->data->num == 1)
		return (unlock(&philo->data->fork[left], ERROR));
	pthread_mutex_lock(&(philo->data->fork[right]));
	if (print_lock(philo, "has taken a fork", 0) == ERROR)
		return (unlock_forks(philo, right, left));
	if (print_lock(philo, "is eating", 2) == ERROR)
		return (unlock_forks(philo, right, left));
	if (timer(philo->data->time_to_eat) == ERROR)
		return (unlock_forks(philo, right, left));
	if (is_alive(philo) == FALSE)
		return (unlock_forks(philo, right, left));
	return (SUCCESS);
}

int	philo_eats(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->data->num;
	if (eating(philo, right, left) == ERROR)
		return (ERROR);
	philo->eaten += 1;
	pthread_mutex_unlock(&philo->data->fork[left]);
	pthread_mutex_unlock(&(philo->data->fork[right]));
	if (philo->eaten == philo->data->must_eat)
	{
		pthread_mutex_lock(&philo->data->full_mutex);
		philo->data->full_philos += 1;
		pthread_mutex_unlock(&philo->data->full_mutex);
		return (ERROR);
	}
	return (SUCCESS);
}

void	*simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!(philo->id % 2))
		timer(philo->data->time_to_eat);
	while (1)
	{
		if (philo_eats(philo) == ERROR
			|| print_lock(philo, "is sleeping", 0) == ERROR
			|| timer(philo->data->time_to_sleep) == ERROR
			|| print_lock(philo, "is thinking", 0) == ERROR
			|| is_alive(philo) == FALSE)
			return (NULL);
	}
	return (NULL);
}
