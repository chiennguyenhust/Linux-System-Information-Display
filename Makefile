# Trình biên dịch cross-compile
CC := /home/chiennguyen/working_space/bbb/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
CFLAGS := -Wall -O2 -I./inc  # Bao gồm các file header trong thư mục inc/
LDFLAGS := -lpthread          # Liên kết với pthread để hỗ trợ đa luồng

# Thư mục
SRCDIR := src
INCDIR := inc
OBJDIR := obj
BINDIR := bin

# Tên các file và mục tiêu
TARGET := $(BINDIR)/cpu_ram_info
SRCS := $(wildcard $(SRCDIR)/*.c)  # Bao gồm tất cả file .c trong src/
SRCS += main.c                     # Chỉ định main.c nằm ngoài src
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Tạo các thư mục cần thiết nếu chưa tồn tại
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

# Mục tiêu biên dịch
all: $(OBJDIR) $(BINDIR) $(TARGET)

# Liên kết các file đối tượng thành file thực thi cuối cùng
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Biên dịch từng file .c thành .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Xóa các file object và binary
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/*

# Copy file binary sang BeagleBone Black
copy:
	scp $(TARGET) debian@192.168.0.100:/home/debian
