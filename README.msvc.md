## Experimental support MSVC compilation in Windows
The support for MSVC compilation in Windows is experimental.
Please use this with care at your own risk.

## Prerequisites
Htslib makes use of several features of Linux operating system and GCC compiler. 
To make MSVC compilation possible we had to use ports of several libraries.
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
3. Make the packages visible for MSVC.
```
vcpkg integrate install
```

## Library compilation
Now you should be able to open `htslib-win.sln` solution file in MSVC and build it.
As a result you should get `htslib-win.lib` file that can be used in your project.

## Technicalities
The port is based on commit [2140d03](https://github.com/samtools/htslib/commits/2140d03).

We tried to limit the changes to a very few places.
The majority of changes is in `os/os_specific.h` and `os/os_specific.c` files.
The header file is included in some htslib source files, when it is necessary to provide something MSVC-specific.
When compiled with GCC these files have no effect, so the behavior of the library under Linux should be the same as the original one.
In a very few places it was also necessary to use conditional compilation (`#ifdef`).

## Port contents
We ported the `htslib` library and perfomed a limited number of experiments.

The solution contains `test_view` project which is MSVC project wrapping htslib's `test/test_view.c` file.
You can use this program to view SAM/BAM/CRAM files and check how this works when compiled using MSVC.

The solution contains also `cpp_headers` project that just wraps `test/usepublic.c` file to check that all public headers can be compiled with C++ compiler.
Notice, that here we check just the compilation.
The liniking fails as no `myread` function is provided.

## Limitations
Unfortunately several of the used libraries, e.g., `getopt` does not allow static compilation. 
Thus, you will need to distribute a few DLLs toghether with you MSVC-compiled project.
Fortunately, the compilation with GCC under Linux is unchanged, so no extra libraries are necesssary.

Under Linux, the first step when compiling the library is usually to run `./configure` stript which checks what is present at the current platform.
It prepares `config.h` file with some `#define`'s.
In the port we do not use this stript. 
Instead, we just use the `config.h` file in our project.
It is compatibile with the packages mentioned in Prerequisites.

The current port can be compiled using MSVC 2022.
It should be able to use the port with older MSVC version (e.g., MSVC 2019) but we did not perform such tests.

