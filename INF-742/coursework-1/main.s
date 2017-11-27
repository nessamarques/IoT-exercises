	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	set_sleep_mode
	.type	set_sleep_mode, @function
set_sleep_mode:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.size	set_sleep_mode, .-set_sleep_mode
.global	sleep_cpu
	.type	sleep_cpu, @function
sleep_cpu:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* #APP */
 ;  65 "main.c" 1
	sleep
 ;  0 "" 2
/* #NOAPP */
	ret
	.size	sleep_cpu, .-sleep_cpu
.global	initialize_uart
	.type	initialize_uart, @function
initialize_uart:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	call uart_init
	ldi r30,lo8(__iob)
	ldi r31,hi8(__iob)
	ldi r24,lo8(uart_output)
	ldi r25,hi8(uart_output)
	std Z+3,r25
	std Z+2,r24
	ldi r24,lo8(uart_input)
	ldi r25,hi8(uart_input)
	std Z+1,r25
	st Z,r24
	ret
	.size	initialize_uart, .-initialize_uart
.global	setup_timer0
	.type	setup_timer0, @function
setup_timer0:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r24,lo8(1)
	sts 110,r24
	out 0x26,__zero_reg__
	ldi r24,lo8(5)
	out 0x25,r24
	ret
	.size	setup_timer0, .-setup_timer0
.global	setup_watchDogTimer
	.type	setup_watchDogTimer, @function
setup_watchDogTimer:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	in __tmp_reg__,0x34
	sbrs __tmp_reg__,3
	rjmp .L6
	in r24,0x34
	andi r24,lo8(-9)
	out 0x34,r24
	lds r24,96
	ori r24,lo8(24)
	sts 96,r24
	sts 96,__zero_reg__
.L6:
	lds r24,96
	ori r24,lo8(24)
	sts 96,r24
	ldi r24,lo8(64)
	sts 96,r24
	ret
	.size	setup_watchDogTimer, .-setup_watchDogTimer
.global	__vector_6
	.type	__vector_6, @function
__vector_6:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r24
	push r25
	push r26
	push r27
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 7 */
.L__stack_usage = 7
	lds r24,millis
	lds r25,millis+1
	lds r26,millis+2
	lds r27,millis+3
	adiw r24,16
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	sts millis,r24
	sts millis+1,r25
	sts millis+2,r26
	sts millis+3,r27
/* epilogue start */
	pop r27
	pop r26
	pop r25
	pop r24
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_6, .-__vector_6
.global	__vector_16
	.type	__vector_16, @function
__vector_16:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
	push r24
	push r25
	push r26
	push r27
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 8 */
.L__stack_usage = 8
	lds r24,t0millis
	lds r25,t0millis+1
	lds r26,t0millis+2
	lds r27,t0millis+3
	adiw r24,16
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	sts t0millis,r24
	sts t0millis+1,r25
	sts t0millis+2,r26
	sts t0millis+3,r27
	lds r24,t0fraction
	lds r25,t0fraction+1
	subi r24,-128
	sbci r25,-2
	sts t0fraction+1,r25
	sts t0fraction,r24
	lds r24,t0fraction
	lds r25,t0fraction+1
	cpi r24,-24
	sbci r25,3
	brlt .L12
	lds r24,t0fraction
	lds r25,t0fraction+1
	subi r24,-24
	sbci r25,3
	sts t0fraction+1,r25
	sts t0fraction,r24
	lds r24,t0millis
	lds r25,t0millis+1
	lds r26,t0millis+2
	lds r27,t0millis+3
	adiw r24,1
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	sts t0millis,r24
	sts t0millis+1,r25
	sts t0millis+2,r26
	sts t0millis+3,r27
.L12:
/* epilogue start */
	pop r27
	pop r26
	pop r25
	pop r24
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_16, .-__vector_16
.global	get_time_ms
	.type	get_time_ms, @function
get_time_ms:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	lds r22,millis
	lds r23,millis+1
	lds r24,millis+2
	lds r25,millis+3
	ret
	.size	get_time_ms, .-get_time_ms
.global	__floatsisf
.global	__subsf3
.global	__addsf3
.global	__fixsfsi
.global	get_time_interval
	.type	get_time_interval, @function
get_time_interval:
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push r16
	push r17
/* prologue: function */
/* frame size = 0 */
/* stack size = 10 */
.L__stack_usage = 10
	lds r16,millis
	lds r17,millis+1
	lds r18,millis+2
	lds r19,millis+3
	cp r16,r22
	cpc r17,r23
	cpc r18,r24
	cpc r19,r25
	brge .L16
	lds r8,millis
	lds r9,millis+1
	lds r10,millis+2
	lds r11,millis+3
	call __floatsisf
	movw r18,r22
	movw r20,r24
	ldi r22,0
	ldi r23,0
	ldi r24,0
	ldi r25,lo8(79)
	call __subsf3
	ldi r18,0
	ldi r19,0
	ldi r20,lo8(-128)
	ldi r21,lo8(63)
	call __addsf3
	movw r12,r22
	movw r14,r24
	movw r24,r10
	movw r22,r8
	call __floatsisf
	movw r18,r22
	movw r20,r24
	movw r24,r14
	movw r22,r12
	call __addsf3
	call __fixsfsi
	rjmp .L17
.L16:
	lds r16,millis
	lds r17,millis+1
	lds r18,millis+2
	lds r19,millis+3
	movw r12,r16
	movw r14,r18
	sub r12,r22
	sbc r13,r23
	sbc r14,r24
	sbc r15,r25
	movw r24,r14
	movw r22,r12
.L17:
/* epilogue start */
	pop r17
	pop r16
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	ret
	.size	get_time_interval, .-get_time_interval
.global	__floatunsisf
.global	__mulsf3
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"\n\n[INFO] Button Pressed!"
	.text
.global	__vector_1
	.type	__vector_1, @function
__vector_1:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r12
	push r13
	push r14
	push r15
	push r18
	push r19
	push r20
	push r21
	push r22
	push r23
	push r24
	push r25
	push r26
	push r27
	push r30
	push r31
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 19 */
.L__stack_usage = 19
	lds r22,timeSinceBoot
	lds r23,timeSinceBoot+1
	lds r24,timeSinceBoot+2
	lds r25,timeSinceBoot+3
	call get_time_interval
	cpi r22,45
	sbci r23,1
	cpc r24,__zero_reg__
	cpc r25,__zero_reg__
	brlt .L18
	lds r24,millis
	lds r25,millis+1
	lds r26,millis+2
	lds r27,millis+3
	sts timeSinceBoot,r24
	sts timeSinceBoot+1,r25
	sts timeSinceBoot+2,r26
	sts timeSinceBoot+3,r27
	lds r12,t0millis
	lds r13,t0millis+1
	lds r14,t0millis+2
	lds r15,t0millis+3
	in r24,0x26
	mov r22,r24
	ldi r23,0
	ldi r24,0
	ldi r25,0
	call __floatunsisf
	ldi r18,lo8(111)
	ldi r19,lo8(18)
	ldi r20,lo8(-125)
	ldi r21,lo8(61)
	call __mulsf3
	call __fixsfsi
	movw r26,r24
	movw r24,r22
	add r24,r12
	adc r25,r13
	adc r26,r14
	adc r27,r15
	sts activeTime,r24
	sts activeTime+1,r25
	sts activeTime+2,r26
	sts activeTime+3,r27
	ldi r24,lo8(.LC0)
	ldi r25,hi8(.LC0)
	call puts
	ldi r24,lo8(1)
	sts click,r24
.L18:
/* epilogue start */
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r15
	pop r14
	pop r13
	pop r12
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_1, .-__vector_1
	.section	.rodata.str1.1
.LC1:
	.string	"*** Time since boot: %ld ms *** \n"
.global	__divsf3
.LC2:
	.string	"*** Duty cycle: %4.2f *** \n"
	.text
.global	onButtonPush
	.type	onButtonPush, @function
onButtonPush:
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
/* prologue: function */
/* frame size = 0 */
/* stack size = 8 */
.L__stack_usage = 8
	lds r24,timeSinceBoot
	lds r25,timeSinceBoot+1
	lds r26,timeSinceBoot+2
	lds r27,timeSinceBoot+3
	push r27
	push r26
	push r25
	push r24
	ldi r24,lo8(.LC1)
	ldi r25,hi8(.LC1)
	push r25
	push r24
	call printf
	lds r22,activeTime
	lds r23,activeTime+1
	lds r24,activeTime+2
	lds r25,activeTime+3
	lds r8,timeSinceBoot
	lds r9,timeSinceBoot+1
	lds r10,timeSinceBoot+2
	lds r11,timeSinceBoot+3
	call __floatsisf
	movw r12,r22
	movw r14,r24
	movw r24,r10
	movw r22,r8
	call __floatsisf
	movw r18,r22
	movw r20,r24
	movw r24,r14
	movw r22,r12
	call __divsf3
	ldi r18,0
	ldi r19,0
	ldi r20,lo8(-56)
	ldi r21,lo8(66)
	call __mulsf3
	push r25
	push r24
	push r23
	push r22
	ldi r24,lo8(.LC2)
	ldi r25,hi8(.LC2)
	push r25
	push r24
	call printf
	sts click,__zero_reg__
	in r24,__SP_L__
	in r25,__SP_H__
	adiw r24,12
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r25
	out __SREG__,__tmp_reg__
	out __SP_L__,r24
/* epilogue start */
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	ret
	.size	onButtonPush, .-onButtonPush
.global	onReset
	.type	onReset, @function
onReset:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* #APP */
 ;  65 "main.c" 1
	sleep
 ;  0 "" 2
/* #NOAPP */
	ret
	.size	onReset, .-onReset
	.section	.rodata.str1.1
.LC3:
	.string	"\n\n[INFO] Start!"
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* #APP */
 ;  147 "main.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	call initialize_uart
	ldi r24,lo8(-1)
	out 0x4,r24
	out 0x5,__zero_reg__
	cbi 0xa,2
	sbi 0xb,2
	ldi r24,lo8(1)
	out 0x1d,r24
	ldi r24,lo8(3)
	sts 105,r24
	call setup_timer0
	call setup_watchDogTimer
/* #APP */
 ;  65 "main.c" 1
	sleep
 ;  0 "" 2
/* #NOAPP */
	ldi r24,lo8(.LC3)
	ldi r25,hi8(.LC3)
	call puts
/* #APP */
 ;  170 "main.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L23:
	lds r24,click
	tst r24
	breq .L24
	call onButtonPush
	rjmp .L23
.L24:
/* #APP */
 ;  65 "main.c" 1
	sleep
 ;  0 "" 2
/* #NOAPP */
	rjmp .L23
	.size	main, .-main
	.comm	t0fraction,2,1
	.comm	t0millis,4,1
.global	maxValue
	.section	.rodata
	.type	maxValue, @object
	.size	maxValue, 4
maxValue:
	.byte	0
	.byte	0
	.byte	0
	.byte	79
	.comm	millis,4,1
	.comm	activeTime,4,1
	.comm	timeSinceBoot,4,1
.global	click
	.section .bss
	.type	click, @object
	.size	click, 1
click:
	.zero	1
.global	uart_input
	.data
	.type	uart_input, @object
	.size	uart_input, 14
uart_input:
	.zero	3
	.byte	1
	.zero	4
	.word	0
	.word	gs(uart_getchar)
	.word	0
.global	uart_output
	.type	uart_output, @object
	.size	uart_output, 14
uart_output:
	.zero	3
	.byte	2
	.zero	4
	.word	gs(uart_putchar)
	.word	0
	.word	0
	.ident	"GCC: (GNU) 4.9.2"
.global __do_copy_data
.global __do_clear_bss
