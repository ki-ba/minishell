#ifndef ERROR_H
# define ERROR_H

enum e_error
{
	ERR_ARGS = 1,
	ERR_PARSING,
	ERR_ALLOC,
	ERR_PRINT
};

void	error_exit(int err);

#endif
