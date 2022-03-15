/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_free.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 14:57:08 by smiller       #+#    #+#                 */
/*   Updated: 2022/03/11 12:43:09 by swaanmiller   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	return (ERROR);
}

t_philo	*free_and_destroy_forks(t_philo *philo, int i)
{
	while (i)
	{
		i--;
		pthread_mutex_destroy(&philo->data->fork[i]);
	}
	return (free_all(philo));
}

int	thread_failure(t_data *data, t_philo *philo, int i)
{
	while (i)
	{
		i--;
		pthread_join(philo[i].th, NULL);
	}
	pthread_mutex_destroy(&data->full_mutex);
	pthread_mutex_destroy(&data->status_mutex);
	free_and_destroy_forks(philo, philo->data->num);
	return (ERROR);
}

t_philo	*free_all(t_philo *philo)
{
	if (philo->data->fork != NULL)
		free(philo->data->fork);
	if (philo->data != NULL)
		free(philo->data);
	if (philo != NULL)
		free(philo);
	return (NULL);
}
