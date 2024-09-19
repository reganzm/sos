
#include "apps/libc/types.h"
#include "include/vesa.h"


void sleep(long ms);
void* shm_open(const uint8_t* name);
void get_mode_info(struct mode_info* mode_info);