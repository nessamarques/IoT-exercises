	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
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
.global	__vector_6
	.type	__vector_6, @function
__vector_6:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 3 */
.L__stack_usage = 3
/* epilogue start */
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
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 3 */
.L__stack_usage = 3
/* epilogue start */
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_16, .-__vector_16
.global	__vector_1
	.type	__vector_1, @function
__vector_1:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 3 */
.L__stack_usage = 3
/* epilogue start */
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_1, .-__vector_1
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
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
 ;  49 "main.c" 1
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
	call onReset
	ldi r24,lo8(.LC0)
	ldi r25,hi8(.LC0)
	call puts
/* #APP */
 ;  71 "main.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L7:
	rjmp .L7
	.size	main, .-main
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
