/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:12:28 by ayeganya          #+#    #+#             */
/*   Updated: 2024/06/17 16:26:29 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	my_exit(void);
void	s_to_f(int *f_stack, int **cache);
int		module(int value);
int		max(int val1, int val2);
int		max_indx_calc(int *stack, int size);
int		min_indx_calc(int *stack, int size);
int		index_transformer(int indx, int size);
int		rev_wgt(int nbr, int size);
void	print_actions2(int **cache);
void	print_actions(int **cache, int i);
void	rotate(int *stack, int action, int size, int i);
void	misc_update(int **cache, int stage);
void	move(int *f_stack, int **cache, int stage, int ssize);
void	small_sort(int *f_stack, int **cache);

void	w2_calc(int *f_stack, int **cache, int i)
{
	int	j;
	int	max_indx;
	int	min_indx;

	max_indx = max_indx_calc(cache[S_STACK], cache[MISC][SSIZE]);
	min_indx = min_indx_calc(cache[S_STACK], cache[MISC][SSIZE]);
	if (f_stack[i] > cache[S_STACK][max_indx] || \
			f_stack[i] < cache[S_STACK][min_indx])
		cache[W2][i] = index_transformer(max_indx, cache[MISC][SSIZE]);
	else if (f_stack[i] > cache[S_STACK][0] && \
			f_stack[i] < cache[S_STACK][cache[MISC][SSIZE] - 1])
		cache[W2][i] = 0;
	else
	{
		j = 0;
		while (++j && j < cache[MISC][SSIZE])
			if (f_stack[i] > cache[S_STACK][j] && \
					f_stack[i] < cache[S_STACK][j - 1])
				break ;
		cache[W2][i] = index_transformer(j, cache[MISC][SSIZE]);
	}
}

void	weight_optimizer(int **cache, int i)
{
	int	rwgt1;
	int	rwgt2;

	rwgt1 = rev_wgt(cache[W1][i], cache[MISC][SIZE]);
	rwgt2 = rev_wgt(cache[W2][i], cache[MISC][SSIZE]);
	if ((cache[W1][i] >= 0 && cache[W2][i] >= 0) || \
			(cache[W1][i] < 0 && cache[W2][i] < 0))
		return ;
	if (module(cache[W1][i]) <= module(cache[W2][i]))
	{
		if (module(rwgt2) <= module(cache[W1][i]))
			cache[W2][i] = rwgt2;
	}
	else
		if (module(rwgt1) <= module(cache[W2][i]))
			cache[W1][i] = rwgt1;
}

void	action_weight_calc(int *f_stack, int **cache)
{
	int	i;

	i = 0;
	while (i < cache[MISC][SIZE])
	{
		if (i <= cache[MISC][SIZE] / 2)
			cache[W1][i] = i;
		else
			cache[W1][i] = i - cache[MISC][SIZE];
		w2_calc(f_stack, cache, i);
		weight_optimizer(cache, i);
		if ((cache[W1][i] >= 0 && cache[W2][i] >= 0) || \
				(cache[W1][i] < 0 && cache[W2][i] < 0))
			cache[WGT][i] = max(module(cache[W1][i]), module(cache[W2][i]));
		else
			cache[WGT][i] = module(cache[W1][i]) + module(cache[W2][i]);
		i++;
	}
	i = 1;
	cache[MISC][ACTION] = 0;
	while (i < cache[MISC][SIZE] && ++i)
		if (cache[WGT][i - 1] < cache[WGT][cache[MISC][ACTION]])
			cache[MISC][ACTION] = i - 1;
}

void	f_to_s(int *f_stack, int **cache)
{
	int	temp;

	move(f_stack, cache, F_STAGE, 0);
	move(f_stack, cache, F_STAGE, 0);
	write(1, "pb\npb\n", 6);
	if (cache[S_STACK][0] < cache[S_STACK][1])
	{
		temp = cache[S_STACK][0];
		cache[S_STACK][0] = cache[S_STACK][1];
		cache[S_STACK][1] = temp;
		write(1, "sb\n", 3);
	}
	while (cache[MISC][SIZE] != 0)
	{
		action_weight_calc(f_stack, cache);
		print_actions(cache, 0);
		rotate(f_stack, cache[W1][cache[MISC][ACTION]], cache[MISC][SIZE], 0);
		rotate(cache[S_STACK], cache[W2][cache[MISC][ACTION]], \
				cache[MISC][SSIZE], 0);
		move(f_stack, cache, F_STAGE, 0);
	}
}

void	sort_engine(int *f_stack, int **cache)
{
	if (cache[MISC][ISIZE] == 2)
	{
		if (f_stack[0] > f_stack[1])
			write(1, "sa\n", 3);
	}
	else if (cache[MISC][ISIZE] < 6)
		small_sort(f_stack, cache);
	else
	{
		f_to_s(f_stack, cache);
		s_to_f(f_stack, cache);
	}
}
