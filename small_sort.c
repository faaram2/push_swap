/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:28:40 by ayeganya          #+#    #+#             */
/*   Updated: 2024/04/10 11:32:48 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(int *stack, int action, int size, int i);
int		min_indx_calc(int *stack, int size);
void	index_creator(int *variant, int *sorted, int *index, int lngt);
void	array_clone(int *dst, int *src, int size);
void	swap(int *stack);

int	weight_calc(int *stack, int **cache)
{
	int	i;
	int	weight;

	weight = 0;
	i = 0;
	index_creator(stack, cache[SORTED], cache[INDEX], cache[MISC][SIZE]);
	while (i + 1 < cache[MISC][SIZE])
	{
		if (cache[INDEX][i + 1] - cache[INDEX][i] > 0)
			weight += cache[INDEX][i + 1] - cache[INDEX][i] - 1;
		else
			weight += cache[INDEX][i + 1] - cache[INDEX][i] - 1 + \
				cache[MISC][SIZE];
		i++;
	}
	if (cache[INDEX][0] - cache[INDEX][cache[MISC][SIZE] - 1] > 0)
		weight += cache[INDEX][0] - cache[INDEX][cache[MISC][SIZE] - 1] - 1;
	else
		weight += cache[INDEX][0] - cache[INDEX][cache[MISC][SIZE] - 1] - 1 + \
			cache[MISC][SIZE];
	return (weight);
}

void	f_stack_changer(int *f_stack, int **cache)
{
	int	i;

	i = 0;
	if (cache[MISC][LST_WGT_INDX] == 0)
		return ;
	if (cache[MISC][LST_WGT_INDX] % 2 == 0)
	{
		rotate(f_stack, cache[MISC][LST_WGT_INDX] / 2, cache[MISC][SIZE], 0);
		while (i < cache[MISC][LST_WGT_INDX] / 2 && ++i)
			write(1, "ra\n", 3);
	}
	if (cache[MISC][LST_WGT_INDX] % 2 == 1)
	{
		rotate(f_stack, -(cache[MISC][LST_WGT_INDX] / 2), cache[MISC][SIZE], 0);
		while (i < cache[MISC][LST_WGT_INDX] / 2 && ++i)
			write(1, "rra\n", 4);
	}
	swap(f_stack);
	write(1, "sa\n", 3);
}

void	lst_wgt_indx_finder(int **cache)
{
	int	i;

	if (cache[MISC][LST_WGT_INDX] == -1)
	{
		i = 2;
		cache[MISC][LST_WGT_INDX] = 1;
	}
	else
	{
		i = 3;
		cache[MISC][LST_WGT_INDX] = 2;
	}
	if (cache[WGT][0] == 0)
	{
		cache[MISC][LST_WGT_INDX] = 0;
		return ;
	}
	while (i <= cache[MISC][SIZE])
	{
		if (cache[WGT][i] < cache[WGT][cache[MISC][LST_WGT_INDX]])
			cache[MISC][LST_WGT_INDX] = i;
		i++;
	}
}

void	weight_array_init(int *f_stack, int **cache)
{
	int	i;

	cache[WGT][0] = weight_calc(f_stack, cache);
	array_clone(cache[TEMP], f_stack, cache[MISC][SIZE]);
	swap(cache[TEMP]);
	cache[WGT][1] = weight_calc(cache[TEMP], cache);
	i = 1;
	while (i <= cache[MISC][SIZE] / 2)
	{
		array_clone(cache[TEMP], f_stack, cache[MISC][SIZE]);
		rotate(cache[TEMP], i, cache[MISC][SIZE], 0);
		swap(cache[TEMP]);
		cache[WGT][i * 2] = weight_calc(cache[TEMP], cache);
		array_clone(cache[TEMP], f_stack, cache[MISC][SIZE]);
		rotate(cache[TEMP], -i, cache[MISC][SIZE], 0);
		swap(cache[TEMP]);
		cache[WGT][i * 2 + 1] = weight_calc(cache[TEMP], cache);
		i++;
	}
}

void	small_sort(int *f_stack, int **cache)
{
	int	i;

	weight_array_init(f_stack, cache);
	cache[MISC][LST_WGT_INDX] = -1;
	lst_wgt_indx_finder(cache);
	while (cache[WGT][cache[MISC][LST_WGT_INDX]] != 0)
	{
		f_stack_changer(f_stack, cache);
		weight_array_init(f_stack, cache);
		lst_wgt_indx_finder(cache);
	}
	f_stack_changer(f_stack, cache);
	cache[MISC][LST_WGT_INDX] = min_indx_calc(f_stack, cache[MISC][SIZE]);
	i = 0;
	if (cache[MISC][LST_WGT_INDX] <= cache[MISC][SIZE] / 2)
		while (i < cache[MISC][LST_WGT_INDX] && ++i)
			write(1, "ra\n", 3);
	else
		while (i < cache[MISC][SIZE] - cache[MISC][LST_WGT_INDX] && ++i)
			write(1, "rra\n", 4);
}
