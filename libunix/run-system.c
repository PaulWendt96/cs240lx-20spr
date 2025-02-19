#include <stdarg.h>
#include <stdlib.h>
#include "libunix.h"

#if 0
int run_system_can_fail(const char *fmt, ...) {
    char buf[4096];

    va_list args;
    va_start(args, fmt);
        vsprintf(buf, fmt, args);
    va_end(args);
    int res;
    if((res = system(buf)) != 0) {
        debug("system <%s> failed with %d\n", buf, res);
        return 0;
    }
    debug("SUCCESS: child is done running <%s>!\n", buf);
    return 1;
}
#endif

// should grab the output?
void run_system(const char *fmt, ...) {
    char buf[4096];

    va_list args;
    va_start(args, fmt);
        vsprintf(buf, fmt, args);
    va_end(args);
    int res;
    if((res = system(buf)) != 0)
        panic("system <%s> failed with %d\n", buf, res);

    // not sure if we should have a verbose version?
//    debug("SUCCESS: child is done running <%s>!\n", buf);
}
