## Experimental support MSVC compilation in Windows
The support for MSVC compilation in Windows is experimental.
Please use this with care.

## Prerequisite
Htslib makes use of several POSIX features of Linux operating systems and GCC features. 
To make compilation with MSVC possible we had to use ports of several libraries.
The necessary steps are listed below.

1. Install [vcpkg](https://vcpkg.io/en/index.html) package manager.
```
   git clone https://github.com/Microsoft/vcpkg.git
   .\vcpkg\bootstrap-vcpkg.bat   
```
2. Install the necessary packages.
```
  vcpkg install zlib
  vcpkg install bzip2
  vcpkg install pthreads
  vcpkg install getopt
  vcpkg install tre
  vcpkg install curl
  vcpkg install openssl
  vcpkg install dirent
  vcpkg install dlfcn-win32
  vcpkg install liblzma
  vcpkg install gettimeofday
```
3. Make the packages visible for MSVC
```
vcpkg integrate install
```

## Library compilation
Now you should be able to open `htslib-win.sln` solution file in MSVC and build.

## Technicalities
THe port is based on commit [2140d03](https://github.com/samtools/htslib/commits/2140d03).

We tried to limit the changes to a very few places.
The majority of changes is in `os/os_specific.h` and `os/os_specific.c` files.
The header file is included in some htslib cource files, when it is necessary to prodive something MSVC-specific.
When compiled with GCC this files have no effect, so the behavior of the library under Linux should be the same as the original.
In a very few places it was also necessary to use conditional compilation (`#ifdef`).

## Port contents
We ported the `htslib` library and perfomed a limited number of experiments.
The solution contains `test_view` project which 
