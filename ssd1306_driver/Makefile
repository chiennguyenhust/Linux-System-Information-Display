
BBB_KERNEL := /home/chiennguyen/working_space/bbb/bb-kernel/KERNEL
TOOLCHAIN := /home/chiennguyen/working_space/bbb/bb-kernel/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

EXTRA_CFLAGS=-Wall
obj-m := ssd1306_oled_driver.o
ssd1306_oled_driver-objs = ssd1306_lib.o ssd1306_driver.o

all:
	make ARCH=arm CROSS_COMPILE=$(TOOLCHAIN) -C $(BBB_KERNEL) M=$(shell pwd) modules
	
clean:
	make -C $(BBB_KERNEL) M=$(shell pwd) clean


copy:
	scp ssd1306_oled_driver.ko debian@192.168.0.100:/home/debian
