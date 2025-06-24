#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_storage.h"

// Function prototypes for utility functions
void trimWhitespace(char *str);
int stringToInt(const char *str);
void intToString(int num, char *str, size_t size);

#endif // UTILS_H