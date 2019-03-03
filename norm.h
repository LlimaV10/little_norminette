#define __NORM_H
#ifdef __NORM_H
# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include "libft/libft.h"

# ifdef _APPLE_
#  define CLEAR_CONSOLE "clear"
# elif _linux_
#  define CLEAR_CONSOLE "clear"
# else
#  define CLEAR_CONSOLE "cls"
#  include <io.h>
#  define open _open
#  define close _close
#  define read _read
#  define write _write
# include <sys/stat.h>
# endif
# include <fcntl.h>



# define MAX_LINE_LEN 80
# define MAX_FUNCTION_LEN 25
#endif