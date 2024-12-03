/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:07:08 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/14 12:07:46 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 12) || c == 32)
		return (true);
	return (false);
}

int not_a_digit(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-' || ft_isspace(str[i])))
			return (-1);
		i++;
	}
	return (0);
}

long	ft_atol(char *str)
{
	int	 i;
	int	 sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (not_a_digit(str) == -1)
		return (error(str, E_INVALIDINPT), -1);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		   return (error(str, E_INVALIDINPT), -1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result > INT_MAX)
			return (error(str, E_INVALIDINPT), -1);
	}
	return (result * sign);
}

// skips whitespaces
// checks for negative values
// converts to long and checks for INT_MAX

int is_error(t_table *table)
{
	if (table->nbr_philos == -1)
		return (-1);
	if (table->time_to_die == -1000)
		return (-1);
	if (table->time_to_eat == -1000)
		return (-1);
	if (table->time_to_sleep == -1000)
		return (-1);
	if (table->nbr_meals)
	{
		if (table->nbr_meals == -1)
			return (-1);
	}
	return (0);
}

int is_lower_limit(t_table *table)
{
	if (table->time_to_die < 60000)
		return (error("time_to_die", E_UNDERMINMS), -1);
	if (table->time_to_eat < 60000)
		return (error("time_to_eat", E_UNDERMINMS), -1);
	if (table->time_to_sleep < 60000)
		return (error("time_to_sleep", E_UNDERMINMS), -1);
	return (0);
}

int	parser(t_table *table, char **argv)
{
	table->nbr_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		table->nbr_meals = ft_atol(argv[5]);
	if (is_error(table) == -1)
		return (-1);
	if (is_lower_limit(table) == -1)
		return (-1);
	printf("nbr of philos: %ld\n", table->nbr_philos);
	printf("time_to_die: %ld\n", table->time_to_die);
	printf("time_to_eat: %ld\n", table->time_to_eat);
	printf("time_to_sleep: %ld\n", table->time_to_sleep);
	if (argv[5])
		printf("nbr of meals: %ld\n", table->nbr_meals);
	return (0);
}
