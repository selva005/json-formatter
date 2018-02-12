#ifndef JSONF
#define JSONF

#if NDEBUG
#define LOGDEBUG(FORMAT, ...) { }
#else
#define LOGDEBUG(FORMAT, ...) { printf(FORMAT, ##__VA_ARGS__); printf("\n");}
#endif

#endif
