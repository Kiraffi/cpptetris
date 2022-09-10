#include <stdio.h>
static constexpr int LOG_LEN = 1024;

void printString(const char *);

#if WIN32

#define print(LOG_STRING, ...) do { \
    char debugBuffer[LOG_LEN]; \
    snprintf(debugBuffer, (size_t)LOG_LEN, LOG_STRING, ## __VA_ARGS__); \
    printString(debugBuffer); \
} while(0)

#else
#define print(LOG_STRING, ...) do { \
    printf(LOG_STRING, ## __VA_ARGS__); \
} while(0)
#endif

void *getProcAddress(const char *funcName);
