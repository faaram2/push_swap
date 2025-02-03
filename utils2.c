/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:10:29 by ayeganya          #+#    #+#             */
/*   Updated: 2024/04/10 10:36:17 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	module(int value);

int	max(int val1, int val2)
{
	if (val1 >= val2)
		return (val1);
	else
		return (val2);
}

int	max_indx_calc(int *stack, int size)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	while (i < size)
	{
		if (stack[i] > stack[result])
			result = i;
		i++;
	}
	return (result);
}

int	min_indx_calc(int *stack, int size)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	while (i < size)
	{
		if (stack[i] < stack[result])
			result = i;
		i++;
	}
	return (result);
}

int	index_transformer(int indx, int size)
{
	int	result;

	if (indx <= size / 2)
		result = indx;
	else
		result = indx - size;
	return (result);
}

int	rev_wgt(int nbr, int size)
{
	int	sgn;

	sgn = 1;
	if (nbr < 0)
		sgn = -1;
	return (sgn * (module(nbr) - size));
}
