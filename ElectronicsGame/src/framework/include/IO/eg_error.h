#ifndef EG_ERROR_H
#define EG_ERROR_H

#include <stdlib.h>
#include <stdio.h>

#define EG_ERROR(f) {\
    {f;};\
    getchar();\
    exit(-1);\
}

#endif