/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 14:57:43 by smiller       #+#    #+#                 */
/*   Updated: 2022/03/15 13:25:51 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*set_philo_vars(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = NULL;
	i = 0;
	philo = ft_calloc(data->num, sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	data->fork = ft_calloc(data->num, sizeof(pthread_mutex_t));
	if (data->fork == NULL)
		return (free_all(philo));
	data->start_time = get_time();
	if (data->start_time == 0)
		return (free_all(philo));
	while (i < data->num)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (free_and_destroy_forks(philo, i));
		i++;
	}
	return (philo);
}

t_philo	*init(t_data *data)
{
	t_philo	*philo;

	philo = NULL;
	philo = set_philo_vars(data);
	if (philo == NULL)
		return (NULL);
	if (pthread_mutex_init(&data->full_mutex, NULL) != 0)
		return (free_and_destroy_forks(philo, philo->data->num));
	if (pthread_mutex_init(&data->status_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->full_mutex);
		return (free_and_destroy_forks(philo, philo->data->num));
	}
	return (philo);
}

int	set_data_vars(char **argv, int argc, t_data *data)
{
	int	i;

	i = 0;
	data->num = ft_atoi(argv[1]);
	if (data->num <= 0)
		return (print_error("There must be at least one philosopher"));
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat <= 0)
			return (print_error("No philosophers may eat"));
	}
	return (SUCCESS);
}

int	parse_input(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
		return (print_error("Incorrect number of arguments"));
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_is_digit(argv[i][j]))
				return (print_error("Incorrect argument type"));
			j++;
		}
		i++;
	}
	if (set_data_vars(argv, argc, data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
