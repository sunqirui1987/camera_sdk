#pragma once
#define inline __inline

# if defined(_MSC_VER)
#include <stdint.h>
# ifndef _CRT_SECURE_NO_DEPRECATE
# define _CRT_SECURE_NO_DEPRECATE (1)
# endif
# pragma warning(disable : 4996)
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
# endif
