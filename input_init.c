/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:44:09 by ayeganya          #+#    #+#             */
/*   Updated: 2024/04/12 13:37:54 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		my_atoi(char *str, int *nbr);
void	rf_input_mem_clean(char **rf_input, int size);
void	my_exit(void);

void	check_for_dups(int *f_stack, int elem_nbr, char **rf_input)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < elem_nbr - 1)
	{
		while (j < elem_nbr)
		{
			if (f_stack[i] == f_stack[j])
			{
				free (f_stack);
				rf_input_mem_clean(rf_input, elem_nbr);
				my_exit();
			}
			j++;
		}
		i++;
		j = i + 1;
	}
}

void	sorted_init(const int *f_stack, int *sorted, int size)
{
	int	i;
	int	j;
	int	temp;
	int	min_id;

	i = 0;
	while (i < size && ++i)
		sorted[i - 1] = f_stack[i - 1];
	i = 0;
	j = 0;
	while (i < size - 1)
	{
		min_id = i;
		while (++j && j < size)
			if (sorted[min_id] > sorted[j])
				min_id = j;
		temp = sorted[i];
		sorted[i] = sorted[min_id];
		sorted[min_id] = temp;
		i++;
		j = i;
	}
}

void	memory_init(int *f_stack, int ***ptr_cache, int elem_nbr)
{
	int	i;

	*ptr_cache = (int **)malloc(CACHE_LINES_NBR * sizeof(int *));
	if (!*ptr_cache)
	{
		free(f_stack);
		my_exit();
	}
	i = 0;
	if (elem_nbr < 7)
		elem_nbr = 7;
	while (i < CACHE_LINES_NBR)
	{
		(*ptr_cache)[i] = (int *)malloc((elem_nbr + 1) * sizeof(int));
		if ((*ptr_cache)[i] == 0)
		{
			while (i > 0)
				free((*ptr_cache)[--i]);
			free(*ptr_cache);
			free(f_stack);
			my_exit();
		}
		i++;
	}
}

void	input_init(int elem_nbr, char **rf_input, int *f_stack)
{
	int	i;

	i = 0;
	while (i < elem_nbr)
	{
		if (my_atoi(rf_input[i], &(f_stack[i])) == -1)
		{
			free (f_stack);
			rf_input_mem_clean(rf_input, elem_nbr);
			my_exit();
		}
		i++;
	}
	if (elem_nbr < 2)
	{
		free(f_stack);
		rf_input_mem_clean(rf_input, elem_nbr);
		exit(0);
	}
	check_for_dups(f_stack, elem_nbr, rf_input);
	rf_input_mem_clean(rf_input, elem_nbr);
}

void	swap2(int *stack, int size)
{
	int	temp;

	if (size < 2)
		return ;
	temp = stack[0];
	stack[0] = stack[1];
	stack[1] = temp;
}
