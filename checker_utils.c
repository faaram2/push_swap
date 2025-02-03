/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:53:45 by ayeganya          #+#    #+#             */
/*   Updated: 2024/04/12 13:36:10 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	str_cmpr(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str2[i] != 0)
		return (0);
	return (1);
}

int	command_checker(char *cmd_str)
{
	if (str_cmpr(cmd_str, "sa\n"))
		return (SA);
	if (str_cmpr(cmd_str, "sb\n"))
		return (SB);
	if (str_cmpr(cmd_str, "pa\n"))
		return (PA);
	if (str_cmpr(cmd_str, "pb\n"))
		return (PB);
	if (str_cmpr(cmd_str, "ra\n"))
		return (RA);
	if (str_cmpr(cmd_str, "rb\n"))
		return (RB);
	if (str_cmpr(cmd_str, "rr\n"))
		return (RR);
	if (str_cmpr(cmd_str, "ss\n"))
		return (SS);
	if (str_cmpr(cmd_str, "rra\n"))
		return (RRA);
	if (str_cmpr(cmd_str, "rrb\n"))
		return (RRB);
	if (str_cmpr(cmd_str, "rrr\n"))
		return (RRR);
	return (-1);
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
