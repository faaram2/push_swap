/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reformat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:04:25 by ayeganya          #+#    #+#             */
/*   Updated: 2024/04/08 12:56:25 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	my_exit(void);
void	rf_input_mem_clean(char **rf_input, int size);

int	ft_isspace(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || \
			ch == '\v' || ch == '\f')
		return (1);
	else
		return (0);
}

int	elem_nbr_calc(char *str)
{
	int	i;
	int	rslt;

	i = 0;
	rslt = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && (ft_isspace(str[i + 1]) || !str[i + 1]))
			rslt++;
		i++;
	}
	return (rslt);
}

void	copy_word(char *str, int *sntc_indx, char **rf_input, int *rf_indx)
{
	int	tmp;
	int	k;

	while (ft_isspace(str[*sntc_indx]))
		(*sntc_indx)++;
	if (!str[*sntc_indx])
		return ;
	tmp = *sntc_indx;
	while (!ft_isspace(str[tmp]) && str[tmp])
		tmp++;
	rf_input[*rf_indx] = (char *)malloc((tmp + 1) * sizeof(char));
	if (!rf_input[*rf_indx])
	{
		rf_input_mem_clean(rf_input, *rf_indx);
		my_exit();
	}
	k = 0;
	while (!ft_isspace(str[*sntc_indx]) && str[*sntc_indx] \
			&& ++(*sntc_indx) && ++k)
		rf_input[*rf_indx][k - 1] = str[*sntc_indx - 1];
	rf_input[*rf_indx][k] = 0;
	(*rf_indx)++;
}

void	spliter(char **rf_input, int *rf_indx, char *str )
{
	int	sntc_indx;

	sntc_indx = 0;
	while (str[sntc_indx] != 0)
		copy_word(str, &sntc_indx, rf_input, rf_indx);
}

int	input_reformat(char **argv, int argc, char ***rf_input_p)
{
	int	i;
	int	rf_indx;
	int	elem_nbr;

	i = 1;
	elem_nbr = 0;
	while (i < argc && i++)
		elem_nbr += elem_nbr_calc(argv[i - 1]);
	*rf_input_p = (char **)malloc(elem_nbr * sizeof(char *));
	if (!(*rf_input_p))
		my_exit();
	i = 1;
	rf_indx = 0;
	while (i < argc)
	{
		spliter(*rf_input_p, &rf_indx, argv[i]);
		i++;
	}
	return (elem_nbr);
}
/*
#include <stdio.h>
int main(int argc, char *argv[])
{
	char **rf_input;
	int elem_nbr;
	int i;

	i = 0;
	elem_nbr = input_reformat(argv, argc, &rf_input);
	while (i < elem_nbr && ++i)
		printf("%s\n", rf_input[i - 1]);
	printf("\n%d\n", elem_nbr);

}*/
