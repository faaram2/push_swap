/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:52:36 by ayeganya          #+#    #+#             */
/*   Updated: 2024/04/09 10:05:21 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_actions2(int **cache)
{
	int	i;

	i = 0;
	if (cache[W1][cache[MISC][ACTION]] > 0)
	{
		while (i < cache[W1][cache[MISC][ACTION]] && ++i)
			write (1, "ra\n", 3);
		i = 0;
		while (i > cache[W2][cache[MISC][ACTION]] && --i)
			write (1, "rrb\n", 4);
	}
	else
	{
		while (i > cache[W1][cache[MISC][ACTION]] && --i)
			write (1, "rra\n", 4);
		i = 0;
		while (i < cache[W2][cache[MISC][ACTION]] && ++i)
			write (1, "rb\n", 3);
	}
}

void	print_actions(int **cache, int i)
{
	if (cache[W1][cache[MISC][ACTION]] >= 0 && \
			cache[W2][cache[MISC][ACTION]] >= 0)
	{
		while (i < cache[W1][cache[MISC][ACTION]] && \
				i < cache[W2][cache[MISC][ACTION]] && ++i)
			write (1, "rr\n", 3);
		while (i < cache[W1][cache[MISC][ACTION]] && ++i)
			write (1, "ra\n", 3);
		while (i < cache[W2][cache[MISC][ACTION]] && ++i)
			write (1, "rb\n", 3);
	}
	else if (cache[W1][cache[MISC][ACTION]] <= 0 && \
			cache[W2][cache[MISC][ACTION]] <= 0)
	{
		while (i > cache[W1][cache[MISC][ACTION]] && \
				i > cache[W2][cache[MISC][ACTION]] && --i)
			write (1, "rrr\n", 4);
		while (i > cache[W1][cache[MISC][ACTION]] && --i)
			write (1, "rra\n", 4);
		while (i > cache[W2][cache[MISC][ACTION]] && --i)
			write (1, "rrb\n", 4);
	}
	else
		print_actions2(cache);
	write(1, "pb\n", 3);
}

void	rotate(int *stack, int action, int size, int i)
{
	int	j;
	int	temp;

	if (action > 0)
	{
		while (i < action && ++i)
		{
			j = 0;
			temp = stack[0];
			while (j < size - 1 && ++j)
				stack[j - 1] = stack[j];
			stack[j] = temp;
		}
	}
	else if (action < 0)
	{
		while (i < -action && ++i)
		{
			j = size - 1;
			temp = stack[j];
			while (j > 0 && j--)
				stack[j + 1] = stack[j];
			stack[j] = temp;
		}
	}
}

void	misc_update(int **cache, int stage)
{
	if (stage == F_STAGE)
	{
		cache[MISC][SIZE]--;
		cache[MISC][SSIZE]++;
	}
	else
	{
		cache[MISC][SIZE]++;
		cache[MISC][SSIZE]--;
	}
}

void	move(int *f_stack, int **cache, int stage, int ssize)
{
	int	i;
	int	*from;
	int	*to;

	if (stage == F_STAGE)
	{
		from = f_stack;
		to = cache[S_STACK];
		i = cache[MISC][SSIZE];
	}
	else
	{
		from = cache[S_STACK];
		to = f_stack;
		i = cache[MISC][SIZE];
	}
	ssize = cache[MISC][ISIZE] - i;
	if (i != 0)
		while (i--)
			to[i + 1] = to[i];
	to[0] = from[0];
	i = 0;
	while (i < ssize - 1 && ++i)
		from[i - 1] = from[i];
	misc_update(cache, stage);
}
