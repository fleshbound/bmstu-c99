#ifndef __ARGCH_H__

#define __ARGCH_H__

#define ARGC_F 4
#define ARGC_NOF 3

#define STR_KEY_F "f"
#define LEN_KEY_F 1

#define NO_CODE 0
#define F_CODE 1

int check_args(const int argc, char *const argv[], int *const mode_code);

#endif // #ifndef __ARGCH_H__
