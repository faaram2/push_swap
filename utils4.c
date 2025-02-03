/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:18:55 by ayeganya          #+#    #+#             */
/*   Updated: 2024/04/12 13:52:06 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		max_indx_calc(int *stack, int size);

void	index_creator(int *variant, int *sorted, int *index, int lngt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < lngt)
	{
		while (j < lngt)
		{
			if (variant[i] == sorted[j])
				break ;
			j++;
		}
		index[i] = j;
		j = 0;
		i++;
	}
}

void	array_clone(int *dst, int *src, int size)
{
	int	i;

	i = 0;
	while (i < size && ++i)
		dst[i - 1] = src[i - 1];
}

void	swap(int *stack)
{
	int	temp;

	temp = stack[0];
	stack[0] = stack[1];
	stack[1] = temp;
}

void	s_to_f(int *f_stack, int **cache)
{
	int	i;

	i = f_stack[0];
	i = 0;
	cache[MISC][ACTION] = max_indx_calc(cache[S_STACK], cache[MISC][SSIZE]);
	if (cache[MISC][ACTION] <= cache[MISC][SSIZE] / 2)
		while (i < cache[MISC][ACTION] && ++i)
			write(1, "rb\n", 3);
	else
		while (i < cache[MISC][SSIZE] - cache[MISC][ACTION] && ++i)
			write(1, "rrb\n", 4);
	i = 0;
	while (i < cache[MISC][ISIZE] && ++i)
		write(1, "pa\n", 3);
}

int	module(int value)
{
	if (value >= 0)
		return (value);
	else
		return (-value);
}
