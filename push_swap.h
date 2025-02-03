/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:19:21 by ayeganya          #+#    #+#             */
/*   Updated: 2024/06/17 16:26:32 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

//General
# define F_STAGE 0
# define S_STAGE 1
# define CACHE_LINES_NBR 6

//Cache general lines
# define SORTED 0
# define WGT 4
# define MISC 5

//Cache lines for MORE than 5 element cases
# define S_STACK 1
# define W1 2
# define W2 3

//Cache lines for 5 and LESS element cases
# define INDEX 1
# define TEMP 2

//MISC
# define SIZE 0
# define SSIZE 1
# define ACTION 2
# define ISIZE 3
# define LST_WGT_INDX 4

//COMMANDS
# define SA 0
# define SB 1
# define SS 2
# define PA 3
# define PB 4
# define RA 5
# define RB 6
# define RR 7
# define RRA 8
# define RRB 9
# define RRR 10

typedef struct s_cmd
{
	char			str[4];
	struct s_cmd	*next;
}	t_cmd;

#endif
