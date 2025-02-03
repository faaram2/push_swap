/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:54:59 by ayeganya          #+#    #+#             */
/*   Updated: 2024/04/12 15:53:54 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rf_input_mem_clean(char **rf_input, int size)
{
	int	i;

	i = 0;
	while (i < size && ++i)
		free(rf_input[i - 1]);
	free(rf_input);
}

void	my_exit(void)
{
	write(2, "Error\n", 6);
	exit (1);
}

int	my_atoi(char *str, int *nbr)
{
	int		i;
	int		sgn;
	long	result;

	i = 0;
	sgn = 1;
	result = 0;
	if (*str == 0)
		return (-1);
	if (*str == '-' && str++)
		sgn = -1;
	while (str[i] || (i == 0 && sgn == -1))
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + str[i] - '0';
		if (++i && result > INT_MAX)
		{
			if (result - 1 == INT_MAX && sgn == -1)
				continue ;
			return (-1);
		}
	}
	*nbr = (int)(result * sgn);
	return (0);
}

void	already_sorted(int *f_stack, int elem_nbr, char **rf_input)
{
	int	i;

	i = 0;
	while (i < elem_nbr - 1)
	{
		if (f_stack[i] > f_stack[i + 1])
			return ;
		i++;
	}
	free(f_stack);
	rf_input_mem_clean(rf_input, elem_nbr);
	exit(0);
}

void	mem_clean(int *f_stack, int **cache)
{
	int	i;

	free(f_stack);
	i = 0;
	while (i < CACHE_LINES_NBR)
	{
		free(cache[i]);
		i++;
	}
	free(cache);
}
