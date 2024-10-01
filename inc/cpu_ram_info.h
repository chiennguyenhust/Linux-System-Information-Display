// cpu_ram_info.h

#ifndef CPU_RAM_INFO_H
#define CPU_RAM_INFO_H

#include "ssd1306.h"


void get_cpu_info(char* cpu_info, size_t len);
void get_ram_info(int* total_mem, int* free_mem);
void get_uptime(char* buffer, size_t len);

#endif  // CPU_RAM_INFO_H
