#ifndef _MSVC_H
#define _MSVC_H

// ***************** 
// For MSVC you need tp install https://vcpkg.io/en/index.html. Then you should use vcpkg to install the following packages:
// * zlib
// * bzip2
// * pthreads
// * getopt
// * tre
// * curl
// * openssl
// * dirent
// * dlfcn-win32
// * liblzma
// * gettimeofday
// *****************


#if defined(_MSC_VER)
//*************************************************
// POSIX functions
#define strdup _strdup

// SSIZE_T
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;

#ifndef SSIZE_MAX
#define MAXSIZE_T   ((SIZE_T)~((SIZE_T)0))
#define MAXSSIZE_T  ((SSIZE_T)(MAXSIZE_T >> 1))
#define MINSSIZE_T  ((SSIZE_T)~MAXSSIZE_T)
#define SSIZE_MAX	MAXSSIZE_T
#endif

#ifndef M_LN10
#define M_LN10 2.30258509299404568402 /* log_e 10 */
#endif

#ifndef M_LN2
#define M_LN2 0.69314718055994530942 /* log_e 2 */
#endif

#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880 /* \fBsqrt\fP(2) */
#endif

#ifndef SIGTERM
#include <signal.h>
#ifndef STDIN_FILENO
#define STDIN_FILENO _fileno(stdin)
#endif
#ifndef STDOUT_FILENO
#define STDOUT_FILENO _fileno(stdout)
#endif
#endif

#define R_OK	04

#define HAVE_HMAC	1

// #include <sys/stat.h>
#define _CRT_INTERNAL_NONSTDC_NAMES 1
#include <sys/stat.h>
#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif

#define PLUGIN_EXT "plugin"

#define HTS_STATIC

void usleep(__int64 usec);

#include <gettimeofday.h>

// Defined in a package 
int gettimeofday(struct timeval* tp, struct timezone* tzp);

#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

#pragma warning(disable:4146)

//*************************************************
#else
//*************************************************
#define HTS_STATIC static

//*************************************************
#endif

#endif

