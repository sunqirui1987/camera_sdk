//#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include "AndroidLog.h"
#define HEADER_SIZE 32
#define RETURN_LOAD_ERROR -2
#define RETURN_ERROR -1
#define RETURN_SUCCESS 0
#define XMP_RESERVED 4040
#define STARTSIGN_LEN 2
#define ENDSIGN_LEN 2
#define DATASTART_LEN 2
#define TYPE_LEN 2
#define LENGTH_LEN 2
#define ZERO_LEN 1

int addXmpToJPEG(char * fileName, int width ,int height,char *date);
