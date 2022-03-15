/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 14:57:24 by smiller       #+#    #+#                 */
/*   Updated: 2022/03/01 14:57:30 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_is_whitespace(int c)
{
	return ((c >= 8 && c <= 13) || c == 32);
}

int	ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int					sign;
	int					value;
	int					i;

	sign = 1;
	value = 0;
	i = 0;
	while (ft_is_whitespace(str[i])
		|| (str[i] == '+' && ft_is_digit(str[i + 1])))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_is_digit(str[i]))
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	return (value * sign);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, '\0', size * count);
	return (ptr);
}
