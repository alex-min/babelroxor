#ifndef PORTABLELIBRARY_H
#define PORTABLELIBRARY_H

#ifdef WIN32
# define OS_WINDOWS
#else
# define OS_UNIX
#endif

#define PACKED __attribute__((packed))


#endif // PORTABLELIBRARY_H
