// main.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpu_ram_info.h"
#include "ssd1306.h"

int fd_ssd;

// Clear the terminal
void clrscr() {
    system("clear");
    return;
}

int main() {
    int total_mem, free_mem;
    char cpu_info[128];

    static char buffer_ram[32];
    static char uptime_buffer[64];
   
    fd_ssd = OLED_OpenDevFile(); // Initialize the OLED
    OLED_Clear(fd_ssd);          // Clear screen once at the start

    while (1) {
        // Lấy thông tin CPU
        get_cpu_info(cpu_info, sizeof(cpu_info));
        get_ram_info(&total_mem, &free_mem); 
        get_uptime(uptime_buffer, sizeof(uptime_buffer));
       

        OLED_SetCursor(fd_ssd, 0, 1);  // Đặt vị trí hiển thị
        OLED_Display(fd_ssd, cpu_info);  // Hiển thị thông tin CPU

        snprintf(buffer_ram, sizeof(buffer_ram), "RAM: %d/%d kB", total_mem - free_mem, total_mem);
        OLED_SetCursor(fd_ssd, 0, 4);  
        OLED_Display(fd_ssd, buffer_ram);

        OLED_SetCursor(fd_ssd, 0, 6); 
        OLED_Display(fd_ssd, uptime_buffer);  
        
  



        sleep(1);  
    }
    return 0;
}