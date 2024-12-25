//
// Created by jules on 10/12/2024.
//

#include <close_pipe.h>

int	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (0);
}
