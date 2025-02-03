/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:41:52 by ayeganya          #+#    #+#             */
/*   Updated: 2024/04/12 16:02:20 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	my_exit(void);
void	rf_input_mem_clean(char **rf_input, int size);
int		input_reformat(char **argv, int argc, char ***rf_input_p);
void	input_init(int elem_nbr, char **rf_input, int *f_stack);
void	memory_init(int *f_stack, int ***ptr_cache, int elem_nbr);
void	sorted_init(const int *f_stack, int *sorted, int size);
int		command_checker(char *cmd_str);
void	move(int *f_stack, int **cache, int stage, int ssize);
void	rotate(int *stack, int action, int size, int i);
void	swap2(int *stack, int size);
void	mem_clean(int *f_stack, int **cache);

int	get_command(int *f_stack, int **cache)
{
	int		i;
	int		cmd;
	char	cmd_str[5];

	i = 0;
	while (i < 4 && read(0, &(cmd_str[i]), 1) == 1 && ++i)
		if (cmd_str[i - 1] == '\n')
			break ;
	cmd_str[i] = 0;
	if (i == 0)
		return (-1);
	cmd = command_checker(cmd_str);
	if (cmd < 0)
	{
		mem_clean(f_stack, cache);
		my_exit();
	}
	return (cmd);
}

void	command_processor2(int cmd, int *f_stack, int **cache)
{
	if (cmd == RR)
	{
		rotate(f_stack, 1, cache[MISC][SIZE], 0);
		rotate(cache[S_STACK], 1, cache[MISC][SSIZE], 0);
	}
	else if (cmd == RRA)
		rotate(f_stack, -1, cache[MISC][SIZE], 0);
	else if (cmd == RRB)
		rotate(cache[S_STACK], -1, cache[MISC][SSIZE], 0);
	else if (cmd == RRR)
	{
		rotate(cache[S_STACK], -1, cache[MISC][SSIZE], 0);
		rotate(f_stack, -1, cache[MISC][SIZE], 0);
	}
}

void	command_processor(int cmd, int *f_stack, int **cache)
{
	if (cmd == SA && cache[MISC][SIZE] >= 2)
		swap2(f_stack, cache[MISC][SIZE]);
	else if (cmd == SB && cache[MISC][SSIZE] >= 2)
		swap2(cache[S_STACK], cache[MISC][SSIZE]);
	else if (cmd == SS)
	{
		if (cache[MISC][SIZE] >= 2)
			swap2(f_stack, cache[MISC][SIZE]);
		if (cache[MISC][SSIZE] >= 2)
			swap2(cache[S_STACK], cache[MISC][SSIZE]);
	}
	else if (cmd == PA && cache[MISC][SSIZE] > 0)
		move(f_stack, cache, S_STAGE, 0);
	else if (cmd == PB && cache[MISC][SIZE] > 0)
		move(f_stack, cache, F_STAGE, 0);
	else if (cmd == RA)
		rotate(f_stack, 1, cache[MISC][SIZE], 0);
	else if (cmd == RB)
		rotate(cache[S_STACK], 1, cache[MISC][SSIZE], 0);
	else
		command_processor2(cmd, f_stack, cache);
}

void	sorting_processor(int *f_stack, int **cache)
{
	int	cmd;
	int	i;

	cmd = get_command(f_stack, cache);
	while (cmd >= 0)
	{
		command_processor(cmd, f_stack, cache);
		cmd = get_command(f_stack, cache);
	}
	i = 0;
	while (i < cache[MISC][ISIZE])
	{
		if (f_stack[i] != cache[SORTED][i])
		{
			write(1, "KO\n", 3);
			return ;
		}
		i++;
	}
	write(1, "OK\n", 3);
}

int	main(int argc, char *argv[])
{
	int		*f_stack;
	int		**cache;
	int		elem_nbr;
	char	**rf_input;

	elem_nbr = input_reformat(argv, argc, &rf_input);
	f_stack = (int *)malloc(elem_nbr * sizeof(int));
	if (!f_stack || (argc - 1 > elem_nbr))
	{
		if (f_stack)
			free(f_stack);
		rf_input_mem_clean(rf_input, elem_nbr);
		my_exit();
	}
	input_init(elem_nbr, rf_input, f_stack);
	memory_init(f_stack, &cache, elem_nbr);
	sorted_init(f_stack, cache[SORTED], elem_nbr);
	cache[MISC][SIZE] = elem_nbr;
	cache[MISC][SSIZE] = 0;
	cache[MISC][ISIZE] = elem_nbr;
	sorting_processor(f_stack, cache);
	mem_clean(f_stack, cache);
}
