	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	millis
	.type	millis, @function
millis:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	lds r22,tMillis
	lds r23,tMillis+1
	lds r24,tMillis+2
	lds r25,tMillis+3
	ret
	.size	millis, .-millis
.global	micros
	.type	micros, @function
micros:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	lds r22,tMillis
	lds r23,tMillis+1
	lds r24,tMillis+2
	lds r25,tMillis+3
	ldi r18,lo8(-24)
	ldi r19,lo8(3)
	ldi r20,0
	ldi r21,0
	call __udivmodsi4
	movw r24,r20
	movw r22,r18
	ret
	.size	micros, .-micros
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"[INFO] onReset"
.LC1:
	.string	"[INFO] Turns the LED off"
.LC2:
	.string	"\n*** PRESS BUTTON TO START! ***\n"
	.text
.global	onReset
	.type	onReset, @function
onReset:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r24,lo8(.LC0)
	ldi r25,hi8(.LC0)
	call puts
	call rand
	lds r18,minRndValue
	lds r19,minRndValue+1
	lds r22,maxRndValue
	lds r23,maxRndValue+1
	subi r22,-1
	sbci r23,-1
	sub r22,r18
	sbc r23,r19
	call __divmodhi4
	add r18,r24
	adc r19,r25
	sts minTime+1,r19
	sts minTime,r18
	ldi r24,lo8(.LC1)
	ldi r25,hi8(.LC1)
	call puts
	out 0x5,__zero_reg__
	sts firstClickTime,__zero_reg__
	sts firstClickTime+1,__zero_reg__
	sts firstClickTime+2,__zero_reg__
	sts firstClickTime+3,__zero_reg__
	sts currentClick,__zero_reg__
	sts currentClick+1,__zero_reg__
	sts currentClick+2,__zero_reg__
	sts currentClick+3,__zero_reg__
	sts lastClick,__zero_reg__
	sts lastClick+1,__zero_reg__
	sts lastClick+2,__zero_reg__
	sts lastClick+3,__zero_reg__
	ldi r24,lo8(.LC2)
	ldi r25,hi8(.LC2)
	jmp puts
	.size	onReset, .-onReset
.global	__vector_11
	.type	__vector_11, @function
__vector_11:
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
	lds r24,tMillis
	lds r25,tMillis+1
	lds r26,tMillis+2
	lds r27,tMillis+3
	adiw r24,1
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	sts tMillis,r24
	sts tMillis+1,r25
	sts tMillis+2,r26
	sts tMillis+3,r27
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
	.size	__vector_11, .-__vector_11
	.section	.rodata.str1.1
.LC3:
	.string	"[INFO] Button pressed"
.LC4:
	.string	"[INFO] Turns the LED ON"
.LC5:
	.string	"[INFO] GAME STARTED!"
.LC6:
	.string	"\n*** REACTION TIME: %ld ms ***\n\n"
.LC7:
	.string	"\n*** TOO EARLY ***\n"
.LC8:
	.string	"[INFO] OK!"
.LC9:
	.string	"\n*** TIMEOUT ***\n"
	.text
.global	startGame
	.type	startGame, @function
startGame:
	push r28
	push r29
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	ldi r24,lo8(.LC3)
	ldi r25,hi8(.LC3)
	call puts
	ldi r24,lo8(1)
	sts playing,r24
	lds r20,firstClickTime
	lds r21,firstClickTime+1
	lds r22,firstClickTime+2
	lds r23,firstClickTime+3
	cp r20,__zero_reg__
	cpc r21,__zero_reg__
	cpc r22,__zero_reg__
	cpc r23,__zero_reg__
	brne .L6
	lds r24,tMillis
	lds r25,tMillis+1
	lds r26,tMillis+2
	lds r27,tMillis+3
	sts firstClickTime,r24
	sts firstClickTime+1,r25
	sts firstClickTime+2,r26
	sts firstClickTime+3,r27
	ldi r24,lo8(.LC4)
	ldi r25,hi8(.LC4)
	call puts
	ldi r24,lo8(-1)
	out 0x5,r24
	ldi r24,lo8(.LC5)
	ldi r25,hi8(.LC5)
	rjmp .L9
.L6:
	lds r24,currentClick
	lds r25,currentClick+1
	lds r26,currentClick+2
	lds r27,currentClick+3
	movw r28,r24
	sub r28,r20
	sbc r29,r21
	push r27
	push r26
	push r25
	push r24
	ldi r24,lo8(.LC6)
	ldi r25,hi8(.LC6)
	push r25
	push r24
	call printf
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	lds r24,minTime
	lds r25,minTime+1
	cp r28,r24
	cpc r29,r25
	brge .L7
	ldi r24,lo8(.LC7)
	ldi r25,hi8(.LC7)
.L9:
/* epilogue start */
	pop r29
	pop r28
	jmp puts
.L7:
	lds r24,maxTime
	lds r25,maxTime+1
	cp r28,r24
	cpc r29,r25
	brge .L8
	ldi r24,lo8(.LC8)
	ldi r25,hi8(.LC8)
	rjmp .L9
.L8:
	ldi r24,lo8(.LC9)
	ldi r25,hi8(.LC9)
	call puts
/* epilogue start */
	pop r29
	pop r28
	jmp onReset
	.size	startGame, .-startGame
.global	__vector_1
	.type	__vector_1, @function
__vector_1:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r16
	push r17
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
/* stack size = 17 */
.L__stack_usage = 17
	lds r20,currentClick
	lds r21,currentClick+1
	lds r22,currentClick+2
	lds r23,currentClick+3
	sts lastClick,r20
	sts lastClick+1,r21
	sts lastClick+2,r22
	sts lastClick+3,r23
	lds r24,tMillis
	lds r25,tMillis+1
	lds r26,tMillis+2
	lds r27,tMillis+3
	sts currentClick,r24
	sts currentClick+1,r25
	sts currentClick+2,r26
	sts currentClick+3,r27
	lds r16,firstClickTime
	lds r17,firstClickTime+1
	lds r18,firstClickTime+2
	lds r19,firstClickTime+3
	or r16,r17
	or r16,r18
	or r16,r19
	brne .L12
.L14:
	call startGame
	rjmp .L11
.L12:
	cp r20,r24
	cpc r21,r25
	cpc r22,r26
	cpc r23,r27
	brne .L14
.L11:
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
	pop r17
	pop r16
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_1, .-__vector_1
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	call uart_init
	ldi r24,lo8(uart_output)
	ldi r25,hi8(uart_output)
	sts __iob+2+1,r25
	sts __iob+2,r24
	ldi r24,lo8(uart_input)
	ldi r25,hi8(uart_input)
	sts __iob+1,r25
	sts __iob,r24
	ldi r24,0
	ldi r25,0
	call time
	call srand
/* #APP */
 ;  144 "main.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	ldi r24,lo8(-1)
	out 0x4,r24
	cbi 0xa,2
	sbi 0xb,2
	lds r24,105
	andi r24,lo8(-2)
	sts 105,r24
	lds r24,105
	ori r24,lo8(2)
	sts 105,r24
	sbi 0x1d,0
	lds r24,129
	ori r24,lo8(11)
	sts 129,r24
	sts 132+1,__zero_reg__
	sts 132,__zero_reg__
	ldi r24,lo8(-6)
	ldi r25,0
	sts 136+1,r25
	sts 136,r24
	lds r24,111
	ori r24,lo8(2)
	sts 111,r24
/* #APP */
 ;  157 "main.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L23:
	call onReset
	lds r18,playing
	lds r20,currentClick
	lds r21,currentClick+1
	lds r22,currentClick+2
	lds r23,currentClick+3
	lds r24,firstClickTime
	lds r25,firstClickTime+1
	lds r26,firstClickTime+2
	lds r27,firstClickTime+3
	sub r20,r24
	sbc r21,r25
	sbc r22,r26
	sbc r23,r27
	lds r24,maxTime
	lds r25,maxTime+1
	mov __tmp_reg__,r25
	lsl r0
	sbc r26,r26
	sbc r27,r27
.L16:
	cpse r18,__zero_reg__
	rjmp .L22
.L21:
	rjmp .L21
.L22:
	cp r20,r24
	cpc r21,r25
	cpc r22,r26
	cpc r23,r27
	brlo .L16
	ldi r24,lo8(.LC9)
	ldi r25,hi8(.LC9)
	call puts
	rjmp .L23
	.size	main, .-main
.global	playing
	.section .bss
	.type	playing, @object
	.size	playing, 1
playing:
	.zero	1
.global	maxRndValue
	.data
	.type	maxRndValue, @object
	.size	maxRndValue, 2
maxRndValue:
	.word	3000
.global	minRndValue
	.type	minRndValue, @object
	.size	minRndValue, 2
minRndValue:
	.word	1000
.global	maxTime
	.type	maxTime, @object
	.size	maxTime, 2
maxTime:
	.word	5000
.global	minTime
	.section .bss
	.type	minTime, @object
	.size	minTime, 2
minTime:
	.zero	2
	.comm	lastClick,4,1
	.comm	currentClick,4,1
	.comm	firstClickTime,4,1
	.comm	tMillis,4,1
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
