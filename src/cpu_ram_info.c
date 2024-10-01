#include <stdio.h>    // Thư viện cho nhập xuất tiêu chuẩn
#include <stdlib.h>   // Thư viện cho các hàm tiêu chuẩn như malloc, free
#include <string.h>   // Thư viện cho các hàm xử lý chuỗi
#include <unistd.h>   // Thư viện cho các hàm liên quan đến hệ điều hành, như sleep
#include <time.h>     // Thư viện cho làm việc với thời gian
#include "cpu_ram_info.h"  // Thư viện tùy chỉnh cho thông tin CPU và RAM


void get_cpu_info(char* cpu_info, size_t len) {
    FILE* file = fopen("/proc/cpuinfo", "r");
    if (file == NULL) {
        perror("Cannot open /proc/cpuinfo");
        strncpy(cpu_info, "Error reading CPU info", len);  // Ghi lỗi vào chuỗi
        return;
    }
    
    char buffer[256];    // Khởi tạo mảng kí tự (chuỗi)
    cpu_info[0] = '\0';  // Khởi tạo chuỗi trống
    
    // Đọc và lưu các dòng liên quan đến "model name" và "cpu MHz"
    while (fgets(buffer, sizeof(buffer), file)) { // Đọc 1 dòng từ file và lưu vào buffer
        if (strncmp(buffer, "model name", 10) == 0) { // Hàm so sánh 2 chuỗi
            // Loại bỏ ký tự xuống dòng cuối mỗi dòng
            buffer[strcspn(buffer, "\n")] = '\0'; // Tìm ra vị trí của ký tự xuống dòng và thay thế nó bằng ký tự kết thúc chuỗi
            strcat(cpu_info, buffer); // nối chuỗi cpu_info + buffer
        }
    }
    fclose(file);
}

void get_ram_info(int* total_mem, int* free_mem) {
    FILE* file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        perror("Cannot open /proc/meminfo");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, "MemTotal", 8) == 0) {
            sscanf(buffer, "MemTotal: %d kB", total_mem);
        } else if (strncmp(buffer, "MemFree", 7) == 0) {
            sscanf(buffer, "MemFree: %d kB", free_mem);
        }
    }
    fclose(file);
}

void get_uptime(char* buffer, size_t len) {
    FILE* file = fopen("/proc/uptime", "r");
    if (file == NULL) {
        perror("Cannot open /proc/uptime");
        snprintf(buffer, len, "Error reading uptime");  // Ghi lỗi vào chuỗi
        return;
    }

    double uptime;
    fscanf(file, "%lf", &uptime);
    fclose(file);
    
    int hours = uptime / 3600;
    int minutes = (uptime - (hours * 3600)) / 60;
    int seconds = (int)uptime % 60;

    // Định dạng chuỗi để hiển thị
    snprintf(buffer, len, "Uptime: %d:%02d:%02d", hours, minutes, seconds);
}

