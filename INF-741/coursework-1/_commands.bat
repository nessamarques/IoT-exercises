avr-gcc -Os -mmcu=atmega328 -S main.c -o main.s -DF_CPU=16000000
avr-as -mmcu=atmega328 main.s -o main.o
avr-gcc -Os -mmcu=atmega328 main.o -o main.x simple_usart\uart.o
avr-objcopy -j .text -j .data -O ihex main.x main.hex
avrdude -C "C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf" -v -patmega328p -carduino -P/COM3 -b115200 -D -Uflash:w:main.hex:i