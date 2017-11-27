avr-gcc -Os -mmcu=atmega328 -S main.c -o main.s
avr-as -mmcu=atmega328 main.s -o main.o
avr-gcc -Os -mmcu=atmega328 main.o -o main.x
avr-objcopy -j .text -j .data -O ihex main.x main.hex
avrdude -C "C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf" -v -patmega328p -carduino -P COM3 -b115200 -D -Uflash:w:main.hex:i
pause