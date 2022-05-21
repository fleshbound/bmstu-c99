#ifndef __ERRORS_H__

#define __ERRORS_H__

#define ERR_EMPTY -1
#define ERR_IO 1
#define ERR_ARGS 2
#define ERR_READ 3
#define ERR_WRITE 4
#define ERR_DATA 5
#define ERR_PATH 6

void show_err(const int code);

#endif // #ifndef __ERRORS_H__
