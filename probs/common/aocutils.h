#ifndef UTILS_H
#define UTILS_H

void process(int (*solve)(const char *, int *, int *), const char *target);

void long_process(long int (*solve)(const char *, long int *, long int *), const char *target);

#endif