CC=arm-none-eabi-gcc
MACH=cortex-m3
CFLAGS=-c -mcpu=$(MACH) -mthumb -std=gnu11 -O0
LDFLAGS=-nostdlib -T STM32_LS.ld -Wl,-Map=final.map

all: final.elf

final.elf: main.o STM32_startup.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -o $@ $<

STM32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $<
	
clean:
	rm -f *.o *.elf *.map