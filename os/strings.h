#ifndef _STRINGS_H
#define _STRINGS_H

#if defined(_MSC_VER)
#include <string.h>

#define strncasecmp _strnicmp
#define strcasecmp _stricmp

#endif
#endif