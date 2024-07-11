#pragma once

#include "../cram/cram.h"
#include "../htslib/sam.h"
#include "../htslib/vcf.h"
#include "../htslib/hts_log.h"
#include "../htslib/hfile.h"


htsFile* sd_hts_open(const char* fn, const char* mode, void *ext_input);
htsFile* sd_hts_open_format(const char* fn, const char* mode, const void* fmt);
hFILE* sd_hopen(const char* fname, const char* mode, ...);
static hFILE* sd_hopen_fd(const char* filename, const char* mode);