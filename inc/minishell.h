#ifndef MINISHELL_H
# define MINISHELL_H

/* COMMON DEPENDANCIES */

# include "libft.h"
# include "data_structures.h"

/* EXTERNAL DEPENDANCIES */

// # include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <limits.h>

/* MINISHELL MODULES */

# include "lexing.h"
# include "parsing.h"
# include "exec.h"
# include "builtins.h"
# include "env.h"
# include "signals.h"
# include "history.h"
# include "error.h"

# ifdef __linux__
#  include <readline/readline.h>
#  include <readline/history.h>
# elif __APPLE__
#  include <editline/readline.h>
# endif

# ifndef DEBUG
#  define DEBUG FALSE
# endif

# ifndef HERE_DOC_LEN
#  define HERE_DOC_LEN 8
# endif

extern int	g_signal; // sig_atomic_t

#endif
