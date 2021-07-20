/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:48:54 by ccommiss          #+#    #+#             */
/*   Updated: 2021/07/20 16:48:59 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_quit(void)
{
	perror("Erreur");
	exit(1);
}

void	get_file(int file[2], char **argv, int ac)
{
	file[INFILE] = open(argv[1], O_RDWR);
	if (file[INFILE] == -1)
		error_quit();
	file[OUTFILE] = open(argv[ac - 1], O_RDWR | O_CREAT);
	if (file[OUTFILE] == -1)
		error_quit();
}

void	pipe_fds(int ***fd, int pipes)
{
	int	j;

	j = 0;
	*fd = malloc(sizeof(int *) * pipes);
	while (j < pipes)
	{
		fd[0][j] = malloc(sizeof(int) * 2);
		pipe(fd[0][j]);
		j++;
	}
}
