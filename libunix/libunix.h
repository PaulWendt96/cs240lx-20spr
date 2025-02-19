// engler, cs140e/cs240lx
// 
//    DO NOT MODIFY!!!  Add your prototypes to libunix-extra.h
//    DO NOT MODIFY!!!  Add your prototypes to libunix-extra.h
//    DO NOT MODIFY!!!  Add your prototypes to libunix-extra.h
//    DO NOT MODIFY!!!  Add your prototypes to libunix-extra.h
//    DO NOT MODIFY!!!  Add your prototypes to libunix-extra.h
//    DO NOT MODIFY!!!  Add your prototypes to libunix-extra.h
//
// prototypes for different useful unix utilities.  we also mix in
// some pi-specific unix-side routines since it's easier to keep them
// in one place.
//
#ifndef __LIB_UNIX_H__
#define __LIB_UNIX_H__
#include <stdint.h>
#include <sys/types.h>

// bunch of useful macros for debugging/error checking.
#include "demand.h"

// looks in /dev for a ttyusb device. 
// returns:
//  - device name.
// panic's if 0 or more than 1.
char *find_ttyusb(void);
char *find_ttyusb_first(void);
char *find_ttyusb_last(void);

// read and echo the characters from the pi's usbtty to unix
// and from unix to pi until the ttyusb disappears (the hardware got
// pulled out) or we see a <DONE!!!> string, used to indicate 
// a clean shutdown.
void pi_echo(int unix_fd, int pi_fd, const char *portname);

// hack-y state machine to indicate when we've seen the special string
// 'DONE!!!' from the pi telling us to shutdown.  pass in the null
// terminated string read from the pi.
int pi_done(unsigned char *s);

// overwrite any unprintable characters with a space.
// otherwise terminals can go haywire/bizarro.
// note, the string can contain 0's, so we send the
// size.
void remove_nonprint(uint8_t *buf, int n);
#define HANDOFF_FD 21

// read in file <name>
// returns:
//  - pointer to the code.  pad code with 0s up to the
//    next multiple of 4.  
//  - bytes of code in <size>
//
// fatal error open/read of <name> fails.
void *read_file(unsigned *size, const char *name);

// same as above, but returns 0 if can't open.
void *read_file_canfail(unsigned *size, const char *name);

// read file, expect it to be <size> bytes.
int read_file_noalloc(const char *name, void *buf, unsigned maxsize);

//
// we give you the following.  
//

// opens the ttyusb <device> and returns file descriptor.
int open_tty(const char *device);
int open_tty_n(const char *device, int maxattempts);


// used to set a tty to the 8n1 protocol needed by the tty-serial.
int set_tty_to_8n1(int fd, unsigned speed, double timeout);

// returns 1 if the tty is not there, 0 otherwise.
// used to detect when the user pulls the tty-serial device out.
int tty_gone(const char *ttyname);

// close all open descriptors other than stdin=0, stdout=1, stderr=2
void close_open_fds(void);

// <close_open_fds> except we skip <fd> too: probably want a more general 
// implementation with a list.
void close_open_fds_except(int fd);

// return current number of usec --- probably better to make a larger datatype.
// makes printing kinda annoying however.
typedef unsigned time_usec_t;
time_usec_t time_get_usec(void);


#define close_nofail(fd) no_fail(close(fd))

// roundup <x> to a multiple of <n>: taken from the lcc compiler.
#define roundup(x,n) (((x)+((n)-1))&(~((n)-1)))

// run program <cmd ...>
void run_system(const char *cmd, ...);

uint32_t our_crc32(const void *buf, unsigned size);
// our_crc32_inc(buf,size,0) is the same as our_crc32 
uint32_t our_crc32_inc(const void *buf, unsigned size, uint32_t crc);


// create file <name>: truncates if already exists.
int create_file(const char *name);
FILE *fcreate_file(const char *name);


/********************************************************************************
 * implement these for lab 5
 */

// create a socket pair, 
//    fork/exec program described in <argv> c
//    dup the socket to be <to_fd>
// return the other end to the client.
// write pid of forked process to <pid>
int exec_server_socket(int *pid, char **argv, int to_fd);


int child_exit_noblk(int pid, int *status);
int child_clean_exit(int pid, int *status);
int child_clean_exit_noblk(int pid, int *status);

int write_exact_can_fail(int fd, const void *data, unsigned n);
int write_exact(int fd, const void *data, unsigned n);
int read_exact(int fd, void *data, unsigned n);
int read_timeout(int fd, void *data, unsigned n, unsigned timeout);


void start_watchdog(int watch_pid);

// waits for <usec>
int can_read_timeout(int fd, unsigned usec);
// doesn't block.
int can_read(int fd);

int open_fake_tty(char **fake_dev_name);

// fill in <fmt,..> using <...> and strcat it to <dst>
char *strcatf(char *dst, const char *fmt, ...);

// return a strdup's string.
char *strdupf(const char *fmt, ...);
char *strcpyf(char *dst, const char *fmt, ...);

// is <fd> open?
int fd_is_open(int fd);

// trivial helper to print out the contents of <argv> with a message.
void argv_print(const char *msg, char *argv[]);

// put your prototypes in here.
#include "libunix-extra.h"

// used to concat prefix to other symbol using cpp eval.
#define concat1(x,y) x ## y
#define prepend_sym(pre, sym) concat1(pre, sym)


// calls handler when we get a control-c
void catch_cntrl_c(void (*handler)(int));

#include <assert.h>
#include "bit-support.h"


// get a random number
unsigned long fake_random(void);
// get a seed.
void fake_random_seed(unsigned x);
// initialization:
unsigned fake_random_init(void);



#endif
