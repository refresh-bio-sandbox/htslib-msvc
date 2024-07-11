#include "ext_features.h"
#include <os_specific.h>

typedef struct {
    hFILE base;
    int fd;
    // !!! SD - need to modify to allow extra input
    //    unsigned is_socket:1, is_shared:1;
    unsigned is_socket : 1, is_shared : 1, is_extra_input : 1;
} hFILE_fd;

/****************************/
htsFile* sd_hts_open(const char* fn, const char* mode, void* ext_input) {
    if(ext_input == NULL)
        return hts_open_format(fn, mode, NULL);
    else
        return sd_hts_open_format(fn, mode, ext_input);
}

/****************************/
htsFile* sd_hts_open_format(const char* fn, const char* mode, const void* fmt)
{
    char smode[101], * cp, * cp2, * mode_c, * uncomp = NULL;
    htsFile* fp = NULL;
    hFILE* hfile = NULL;
    char fmt_code = '\0';
    // see enum htsExactFormat in htslib/hts.h
    const char format_to_mode[] = "\0g\0\0b\0c\0\0b\0g\0\0\0\0\0Ff\0\0";

    strncpy(smode, mode, 99);
    smode[99] = 0;
    if ((cp = strchr(smode, ',')))
        *cp = '\0';

    // Migrate format code (b or c) to the end of the smode buffer.
    for (cp2 = cp = smode; *cp; cp++) {
        if (*cp == 'b')
            fmt_code = 'b';
        else if (*cp == 'c')
            fmt_code = 'c';
        else {
            *cp2++ = *cp;
            // Cache the uncompress flag 'u' pos if present
            if (!uncomp && (*cp == 'u')) {
                uncomp = cp2 - 1;
            }
        }
    }
    mode_c = cp2;
    *cp2++ = fmt_code;
    *cp2++ = 0;

#if 0       // !!! SD
    // Set or reset the format code if opts->format is used
    if (fmt && fmt->format > unknown_format
        && fmt->format < sizeof(format_to_mode)) {
        *mode_c = format_to_mode[fmt->format];
    }
#endif

    // Uncompressed bam/bcf is not supported, change 'u' to '0' on write
    if (uncomp && *mode_c == 'b' && (strchr(smode, 'w') || strchr(smode, 'a'))) {
        *uncomp = '0';
    }

#if 0       // !! SD
    // If we really asked for a compressed text format then mode_c above will
    // point to nul.  We set to 'z' to enable bgzf.
    if (strchr(mode, 'w') && fmt && fmt->compression == bgzf) {
        if (fmt->format == sam || fmt->format == vcf || fmt->format == text_format)
            *mode_c = 'z';
    }
#endif

    char* rmme = NULL, * fnidx = strstr(fn, HTS_IDX_DELIM);
    if (fnidx) {
        rmme = strdup(fn);
        if (!rmme) goto error;
        rmme[fnidx - fn] = 0;
        fn = rmme;
    }

    hfile = hopen(fn, smode);
    if (hfile == NULL) goto error;

    fp = hts_hopen(hfile, fn, smode);
    if (fp == NULL) goto error;

#if 0           // !!! SD
    // Compensate for the loss of exactness in htsExactFormat.
    // hts_hopen returns generics such as binary or text, but we
    // have been given something explicit here so use that instead.
    if (fp->is_write && fmt &&
        (fmt->format == bam || fmt->format == sam ||
            fmt->format == vcf || fmt->format == bcf ||
            fmt->format == bed || fmt->format == fasta_format ||
            fmt->format == fastq_format))
        fp->format.format = fmt->format;

    if (fmt && fmt->specific)
        if (hts_opt_apply(fp, fmt->specific) != 0)
            goto error;
#endif

    if (rmme) free(rmme);
    return fp;

error:
    hts_log_error("Failed to open file \"%s\"%s%s", fn,
        errno ? " : " : "", errno ? strerror(errno) : "");
    if (rmme) free(rmme);

    if (hfile)
        hclose_abruptly(hfile);

    return NULL;
}

/****************************/
hFILE* sd_hopen(const char* fname, const char* mode, ...)
{
    return sd_hopen_fd(fname, mode);
}


/****************************/
static hFILE* sd_hopen_fd(const char* filename, const char* mode)
{
    struct hFILE_fd* fp = NULL;
/*    int fd = open(filename, hfile_oflags(mode), 0666);
    if (fd < 0) goto error;

    fp = (hFILE_fd*)hfile_init(sizeof(hFILE_fd), mode, blksize(fd));
    if (fp == NULL) goto error;

    fp->fd = fd;
    fp->is_socket = 0;
    fp->is_shared = 0;
    fp->base.backend = &fd_backend;
    return &fp->base;

error:
    if (fd >= 0) { int save = errno; (void)close(fd); errno = save; }
    hfile_destroy((hFILE*)fp);*/
    return NULL;
}

/****************************/
static ssize_t sd_fd_read(hFILE* fpv, void* buffer, size_t nbytes)
{
/*    hFILE_fd* fp = (hFILE_fd*)fpv;
    ssize_t n;
    do {
        n = fp->is_socket ? recv(fp->fd, buffer, nbytes, 0)
            : read(fp->fd, buffer, nbytes);
    } while (n < 0 && errno == EINTR);
    return n;*/

    return 0;
}

