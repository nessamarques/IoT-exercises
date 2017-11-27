	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"*ring*\n"
	.text
.global	uart_putchar
	.type	uart_putchar, @function
uart_putchar:
	push r28
/* prologue: function */
/* frame size = 0 */
/* stack size = 1 */
.L__stack_usage = 1
	cpi r24,lo8(7)
	brne .L2
	lds r22,__iob+4
	lds r23,__iob+4+1
	ldi r24,lo8(.LC0)
	ldi r25,hi8(.LC0)
/* epilogue start */
	pop r28
	jmp fputs
.L2:
	mov r28,r24
	cpi r24,lo8(10)
	brne .L4
	ldi r24,lo8(13)
	call uart_putchar
.L4:
	lds r24,192
	sbrs r24,5
	rjmp .L4
	sts 198,r28
/* epilogue start */
	pop r28
	ret
	.size	uart_putchar, .-uart_putchar
.global	uart_getchar
	.type	uart_getchar, @function
uart_getchar:
	push r14
	push r15
	push r16
	push r17
	push r28
	push r29
/* prologue: function */
/* frame size = 0 */
/* stack size = 6 */
.L__stack_usage = 6
	lds r18,rxp.1877
	lds r19,rxp.1877+1
	or r18,r19
	breq .+2
	rjmp .L10
	movw r28,r24
	ldi r16,lo8(b.1876)
	ldi r17,hi8(b.1876)
.L12:
	lds r24,192
	sbrs r24,7
	rjmp .L12
	lds r24,192
	sbrc r24,4
	rjmp .L32
	lds r24,192
	sbrc r24,3
	rjmp .L34
	lds r24,198
	cpi r24,lo8(13)
	brne .L14
.L15:
	ldi r24,lo8(10)
	movw r30,r16
	st Z,r24
	movw r22,r28
	call uart_putchar
	ldi r24,lo8(b.1876)
	ldi r25,hi8(b.1876)
	sts rxp.1877+1,r25
	sts rxp.1877,r24
	rjmp .L10
.L14:
	cpi r24,lo8(10)
	breq .L15
	cpi r24,lo8(9)
	brne .L16
	ldi r24,lo8(32)
.L16:
	ldi r25,lo8(-32)
	add r25,r24
	cpi r25,lo8(95)
	brlo .L17
	cpi r24,lo8(-96)
	brlo .L18
.L17:
	ldi r31,hi8(b.1876+7)
	cpi r16,lo8(b.1876+7)
	cpc r17,r31
	brne .L19
	lds r22,__iob+4
	lds r23,__iob+4+1
	ldi r24,lo8(.LC0)
	ldi r25,hi8(.LC0)
	call fputs
	rjmp .L12
.L19:
	movw r14,r16
	ldi r25,-1
	sub r14,r25
	sbc r15,r25
	movw r30,r16
	st Z,r24
	movw r22,r28
	call uart_putchar
	movw r16,r14
	rjmp .L12
.L18:
	cpi r24,lo8(18)
	breq .L20
	brsh .L21
	cpi r24,lo8(3)
	brne .+2
	rjmp .L34
	cpi r24,lo8(8)
	breq .L22
	rjmp .L12
.L21:
	cpi r24,lo8(23)
	breq .L23
	cpi r24,lo8(127)
	breq .L22
	cpi r24,lo8(21)
	breq .L42
	rjmp .L12
.L23:
	movw r14,r16
	rjmp .L26
.L22:
	ldi r31,hi8(b.1876)
	cpi r16,lo8(b.1876)
	cpc r17,r31
	breq .+2
	brsh .+2
	rjmp .L12
	movw r22,r28
	ldi r24,lo8(8)
	call uart_putchar
	movw r22,r28
	ldi r24,lo8(32)
	call uart_putchar
	movw r22,r28
	ldi r24,lo8(8)
	call uart_putchar
	subi r16,1
	sbc r17,__zero_reg__
	rjmp .L12
.L20:
	movw r22,r28
	ldi r24,lo8(13)
	call uart_putchar
	ldi r24,lo8(b.1876)
	mov r14,r24
	ldi r24,hi8(b.1876)
	mov r15,r24
.L27:
	cp r14,r16
	cpc r15,r17
	brlo .+2
	rjmp .L12
	movw r22,r28
	movw r30,r14
	ld r24,Z+
	movw r14,r30
	call uart_putchar
	rjmp .L27
.L42:
	ldi r31,hi8(b.1876)
	cpi r16,lo8(b.1876)
	cpc r17,r31
	breq .+2
	brsh .+2
	rjmp .L12
	movw r22,r28
	ldi r24,lo8(8)
	call uart_putchar
	movw r22,r28
	ldi r24,lo8(32)
	call uart_putchar
	movw r22,r28
	ldi r24,lo8(8)
	call uart_putchar
	subi r16,1
	sbc r17,__zero_reg__
	rjmp .L42
.L47:
	movw r30,r14
	ld r24,-Z
	movw r14,r30
	cpi r24,lo8(32)
	brne .+2
	rjmp .L12
	movw r22,r28
	ldi r24,lo8(8)
	call uart_putchar
	movw r22,r28
	ldi r24,lo8(32)
	call uart_putchar
	movw r22,r28
	ldi r24,lo8(8)
	call uart_putchar
.L26:
	movw r16,r14
	ldi r24,lo8(b.1876)
	cp r14,r24
	ldi r24,hi8(b.1876)
	cpc r15,r24
	breq .+2
	brsh .L47
	rjmp .L12
.L10:
	lds r30,rxp.1877
	lds r31,rxp.1877+1
	movw r24,r30
	adiw r24,1
	sts rxp.1877+1,r25
	sts rxp.1877,r24
	ld r24,Z
	cpi r24,lo8(10)
	brne .L13
	sts rxp.1877+1,__zero_reg__
	sts rxp.1877,__zero_reg__
	rjmp .L13
.L32:
	ldi r24,lo8(-2)
	rjmp .L13
.L34:
	ldi r24,lo8(-1)
.L13:
/* epilogue start */
	pop r29
	pop r28
	pop r17
	pop r16
	pop r15
	pop r14
	ret
	.size	uart_getchar, .-uart_getchar
.global	resetPlayers
	.type	resetPlayers, @function
resetPlayers:
	push r14
	push r15
	push r16
	push r17
	push r28
	push r29
/* prologue: function */
/* frame size = 0 */
/* stack size = 6 */
.L__stack_usage = 6
	movw r16,r24
	movw r14,r22
	movw r30,r24
	ld r24,Z
	ldd r25,Z+1
	sbiw r24,0
	breq .L49
.L50:
	movw r30,r24
	ldd r28,Z+2
	ldd r29,Z+3
	sbiw r28,0
	breq .L57
	call free
	movw r24,r28
	rjmp .L50
.L57:
	call free
.L49:
	ldi r24,lo8(4)
	ldi r25,0
	call malloc
	movw r28,r24
	ldi r24,lo8(1)
	ldi r25,0
	std Y+1,r25
	st Y,r24
	std Y+3,__zero_reg__
	std Y+2,__zero_reg__
	movw r30,r16
	std Z+1,r29
	st Z,r28
	ldi r16,lo8(2)
	ldi r17,0
.L52:
	cp r14,r16
	cpc r15,r17
	brlt .L58
	ldi r24,lo8(4)
	ldi r25,0
	call malloc
	std Y+3,r25
	std Y+2,r24
	movw r30,r24
	std Z+1,r17
	st Z,r16
	std Z+3,__zero_reg__
	std Z+2,__zero_reg__
	ldd __tmp_reg__,Y+2
	ldd r29,Y+3
	mov r28,__tmp_reg__
	subi r16,-1
	sbci r17,-1
	rjmp .L52
.L58:
/* epilogue start */
	pop r29
	pop r28
	pop r17
	pop r16
	pop r15
	pop r14
	ret
	.size	resetPlayers, .-resetPlayers
.global	removePlayer
	.type	removePlayer, @function
removePlayer:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r26,r24
	ld r30,X+
	ld r31,X
	ldi r26,0
	ldi r27,0
.L60:
	sbiw r30,0
	breq .L65
	cp r30,r22
	cpc r31,r23
	brne .L61
	movw r30,r22
	ldd r18,Z+2
	ldd r19,Z+3
	sbiw r26,0
	brne .L62
	movw r26,r24
	st X+,r18
	st X,r19
	rjmp .L63
.L62:
	adiw r26,2+1
	st X,r19
	st -X,r18
	sbiw r26,2
.L63:
	movw r24,r22
	jmp free
.L61:
	movw r26,r30
	ldd __tmp_reg__,Z+2
	ldd r31,Z+3
	mov r30,__tmp_reg__
	rjmp .L60
.L65:
/* epilogue start */
	ret
	.size	removePlayer, .-removePlayer
.global	resetNotes
	.type	resetNotes, @function
resetNotes:
	push r16
	push r17
	push r28
	push r29
/* prologue: function */
/* frame size = 0 */
/* stack size = 4 */
.L__stack_usage = 4
	movw r28,r24
	ld r24,Y
	ldd r25,Y+1
	sbiw r24,0
	breq .L67
.L68:
	movw r30,r24
	ldd r16,Z+2
	ldd r17,Z+3
	cp r16,__zero_reg__
	cpc r17,__zero_reg__
	breq .L73
	call free
	movw r24,r16
	rjmp .L68
.L73:
	call free
.L67:
	std Y+1,__zero_reg__
	st Y,__zero_reg__
/* epilogue start */
	pop r29
	pop r28
	pop r17
	pop r16
	ret
	.size	resetNotes, .-resetNotes
.global	verifyNote
	.type	verifyNote, @function
verifyNote:
	push r16
	push r17
	push r28
	push r29
/* prologue: function */
/* frame size = 0 */
/* stack size = 4 */
.L__stack_usage = 4
	cp r22,__zero_reg__
	cpc r23,__zero_reg__
	brne .L75
	movw r28,r20
	movw r16,r24
	ldi r24,lo8(4)
	ldi r25,0
	call malloc
	movw r26,r24
	adiw r26,1
	st X,r29
	st -X,r28
	adiw r26,2+1
	st X,__zero_reg__
	st -X,__zero_reg__
	sbiw r26,2
	movw r28,r16
	ld r30,Y
	ldd r31,Y+1
	sbiw r30,0
	brne .L81
	std Y+1,r25
	st Y,r24
	rjmp .L82
.L81:
	ldd r24,Z+2
	ldd r25,Z+3
	sbiw r24,0
	breq .L83
	movw r30,r24
	rjmp .L81
.L83:
	std Z+3,r27
	std Z+2,r26
.L82:
	ldi r24,lo8(2)
	ldi r25,0
	rjmp .L77
.L75:
	ldi r24,lo8(1)
	ldi r25,0
	movw r30,r22
	ld r18,Z
	ldd r19,Z+1
	cp r18,r20
	cpc r19,r21
	breq .L77
	ldi r24,0
.L77:
/* epilogue start */
	pop r29
	pop r28
	pop r17
	pop r16
	ret
	.size	verifyNote, .-verifyNote
.global	millis
	.type	millis, @function
millis:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	lds r24,t0millis
	lds r25,t0millis+1
	ret
	.size	millis, .-millis
.global	micros
	.type	micros, @function
micros:
	push r16
	push r17
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	lds r26,t0millis
	lds r27,t0millis+1
	in r30,0x26
	lds r20,t0fraction
	lds r21,t0fraction+1
	ldi r18,lo8(-6)
	ldi r19,0
	call __usmulhisi3
	movw r26,r24
	movw r24,r22
	add r24,r30
	adc r25,__zero_reg__
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	movw r16,r24
	movw r18,r26
	ldi r24,2
	1:
	lsl r16
	rol r17
	rol r18
	rol r19
	dec r24
	brne 1b
	movw r24,r20
	lsl r21
	sbc r26,r26
	sbc r27,r27
	movw r22,r24
	movw r24,r26
	add r22,r16
	adc r23,r17
	adc r24,r18
	adc r25,r19
/* epilogue start */
	pop r17
	pop r16
	ret
	.size	micros, .-micros
.global	getTimeInterval
	.type	getTimeInterval, @function
getTimeInterval:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	lds r18,t0millis
	lds r19,t0millis+1
	lds r18,t0millis
	lds r19,t0millis+1
	movw r20,r18
	sub r20,r24
	sbc r21,r25
	movw r24,r20
	ret
	.size	getTimeInterval, .-getTimeInterval
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
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 6 */
.L__stack_usage = 6
	lds r24,t0millis
	lds r25,t0millis+1
	adiw r24,1
	sts t0millis+1,r25
	sts t0millis,r24
	lds r24,t0fraction
	lds r25,t0fraction+1
	adiw r24,24
	sts t0fraction+1,r25
	sts t0fraction,r24
	lds r24,t0fraction
	lds r25,t0fraction+1
	cpi r24,-24
	sbci r25,3
	brlt .L89
	lds r24,t0fraction
	lds r25,t0fraction+1
	subi r24,-24
	sbci r25,3
	sts t0fraction+1,r25
	sts t0fraction,r24
	lds r24,t0millis
	lds r25,t0millis+1
	adiw r24,1
	sts t0millis+1,r25
	sts t0millis,r24
.L89:
/* epilogue start */
	pop r25
	pop r24
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_16, .-__vector_16
.global	__floatsisf
.global	__divsf3
.global	__mulsf3
.global	__fixsfsi
.global	playTone
	.type	playTone, @function
playTone:
	push r28
	push r29
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	movw r28,r22
	ldi r18,lo8(1)
	sts buzzerState,r18
	lds r18,t0millis
	lds r19,t0millis+1
	sts buzzerTime+1,r19
	sts buzzerTime,r18
	lds r18,t0millis
	lds r19,t0millis+1
	sts buzzerStartTime+1,r19
	sts buzzerStartTime,r18
	movw r22,r24
	lsl r25
	sbc r24,r24
	sbc r25,r25
	call __floatsisf
	movw r18,r22
	movw r20,r24
	ldi r22,0
	ldi r23,0
	ldi r24,lo8(-128)
	ldi r25,lo8(63)
	call __divsf3
	ldi r18,0
	ldi r19,0
	ldi r20,lo8(122)
	ldi r21,lo8(68)
	call __mulsf3
	call __fixsfsi
	sts buzzerPeriod+1,r23
	sts buzzerPeriod,r22
	sts buzzerDuration+1,r29
	sts buzzerDuration,r28
/* epilogue start */
	pop r29
	pop r28
	ret
	.size	playTone, .-playTone
.global	__vector_1
	.type	__vector_1, @function
__vector_1:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
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
/* stack size = 15 */
.L__stack_usage = 15
	lds r24,timer0debounce
	lds r25,timer0debounce+1
	call getTimeInterval
	cpi r24,45
	sbci r25,1
	brlt .L92
	ldi r24,lo8(1)
	sts buttonPressed,r24
	sts whichButtonPressed,__zero_reg__
	ldi r22,lo8(-112)
	ldi r23,lo8(1)
	ldi r24,lo8(33)
	ldi r25,0
	call playTone
	lds r24,t0millis
	lds r25,t0millis+1
	sts timer0debounce+1,r25
	sts timer0debounce,r24
.L92:
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
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_1, .-__vector_1
.global	__vector_2
	.type	__vector_2, @function
__vector_2:
	push r1
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
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
/* stack size = 15 */
.L__stack_usage = 15
	lds r24,timer1debounce
	lds r25,timer1debounce+1
	call getTimeInterval
	cpi r24,45
	sbci r25,1
	brlt .L94
	ldi r24,lo8(1)
	sts buttonPressed,r24
	sts whichButtonPressed,r24
	ldi r22,lo8(-112)
	ldi r23,lo8(1)
	ldi r24,lo8(-22)
	ldi r25,lo8(10)
	call playTone
	lds r24,t0millis
	lds r25,t0millis+1
	sts timer1debounce+1,r25
	sts timer1debounce,r24
.L94:
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
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.size	__vector_2, .-__vector_2
.global	setupInterruptButton
	.type	setupInterruptButton, @function
setupInterruptButton:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	in r24,0xa
	andi r24,lo8(-13)
	out 0xa,r24
	in r24,0xb
	ori r24,lo8(12)
	out 0xb,r24
	ldi r24,lo8(3)
	out 0x1d,r24
	ldi r24,lo8(15)
	sts 105,r24
	ret
	.size	setupInterruptButton, .-setupInterruptButton
.global	setupTimer0
	.type	setupTimer0, @function
setupTimer0:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r24,lo8(1)
	sts 110,r24
	out 0x26,__zero_reg__
	ldi r24,lo8(3)
	out 0x25,r24
	ret
	.size	setupTimer0, .-setupTimer0
	.section	.rodata.str1.1
.LC1:
	.string	"\n\n******************************"
.LC2:
	.string	"*** Follow the leader game ***"
.LC3:
	.string	"******************************\n"
.LC4:
	.string	"-> Welcome to the follow the leader game! Please enter the number of players: [2-9] "
.LC5:
	.string	"%d"
.LC6:
	.string	"Wrong input."
.LC7:
	.string	"\n\n-> ROUND %d\n"
.LC8:
	.string	"-> Player %d\n"
.LC9:
	.string	"\n\n-> Time expired. You have been eliminated! "
.LC10:
	.string	"-> Incorrect sequence! You have been eliminated."
.LC11:
	.string	"-> Player %d won!\n"
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,14
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 14 */
/* stack size = 16 */
.L__stack_usage = 16
/* #APP */
 ;  285 "main.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	lds r24,193
	ori r24,lo8(24)
	sts 193,r24
	lds r24,194
	ori r24,lo8(6)
	sts 194,r24
	sts 197,__zero_reg__
	ldi r24,lo8(103)
	sts 196,r24
	movw r30,r28
	adiw r30,1
	ldi r24,lo8(14)
	movw r26,r30
	0:
	st X+,__zero_reg__
	dec r24
	brne 0b
	ldi r24,lo8(3)
	std Y+4,r24
	ldi r24,lo8(gs(uart_putchar))
	ldi r25,hi8(gs(uart_putchar))
	std Y+10,r25
	std Y+9,r24
	ldi r24,lo8(gs(uart_getchar))
	ldi r25,hi8(gs(uart_getchar))
	std Y+12,r25
	std Y+11,r24
	sts __iob+1,r31
	sts __iob,r30
	sts __iob+2+1,r31
	sts __iob+2,r30
	ldi r24,lo8(-1)
	out 0x4,r24
	out 0x5,__zero_reg__
	call setupInterruptButton
	call setupTimer0
/* #APP */
 ;  304 "main.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
	ldi r17,lo8(3)
	ldi r16,lo8(2)
	ldi r24,lo8(.LC11)
	mov r14,r24
	ldi r24,hi8(.LC11)
	mov r15,r24
	ldi r25,lo8(.LC8)
	mov r12,r25
	ldi r25,hi8(.LC8)
	mov r13,r25
	ldi r18,lo8(4)
	mov r3,r18
	ldi r19,lo8(.LC7)
	mov r10,r19
	ldi r19,hi8(.LC7)
	mov r11,r19
	ldi r20,lo8(players)
	mov r8,r20
	ldi r20,hi8(players)
	mov r9,r20
	ldi r21,lo8(.LC5)
	mov r6,r21
	ldi r21,hi8(.LC5)
	mov r7,r21
	clr r2
	inc r2
.L100:
	lds r24,buzzerState
	cpi r24,lo8(1)
	brne .L101
	lds r24,buzzerTime
	lds r25,buzzerTime+1
	call getTimeInterval
	lds r18,buzzerPeriod
	lds r19,buzzerPeriod+1
	cp r18,r24
	cpc r19,r25
	brge .L103
	lds r24,t0millis
	lds r25,t0millis+1
	sts buzzerTime+1,r25
	sts buzzerTime,r24
	in r24,0x5
	com r24
	out 0x5,r24
.L103:
	lds r24,buzzerStartTime
	lds r25,buzzerStartTime+1
	call getTimeInterval
	lds r18,buzzerDuration
	lds r19,buzzerDuration+1
	cp r18,r24
	cpc r19,r25
	brge .L101
	out 0x5,__zero_reg__
	sts buzzerState,__zero_reg__
.L101:
	lds r30,state
	ldi r31,0
	cpi r30,8
	cpc r31,__zero_reg__
	brsh .L100
	subi r30,lo8(-(gs(.L105)))
	sbci r31,hi8(-(gs(.L105)))
	jmp __tablejump2__
	.section	.progmem.gcc_sw_table,"a",@progbits
	.p2align	1
.L105:
	.word gs(.L104)
	.word gs(.L106)
	.word gs(.L107)
	.word gs(.L108)
	.word gs(.L109)
	.word gs(.L110)
	.word gs(.L111)
	.word gs(.L112)
	.section	.text.startup
.L104:
	ldi r24,lo8(.LC1)
	ldi r25,hi8(.LC1)
	call puts
	ldi r24,lo8(.LC2)
	ldi r25,hi8(.LC2)
	call puts
	ldi r24,lo8(.LC3)
	ldi r25,hi8(.LC3)
	call puts
	ldi r24,lo8(.LC4)
	ldi r25,hi8(.LC4)
	call puts
	sts state,r2
	rjmp .L100
.L106:
	push r9
	push r8
	push r7
	push r6
	call scanf
	movw r4,r24
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	sbiw r24,1
	brne .L114
	lds r22,players
	lds r23,players+1
	movw r24,r22
	sbiw r24,2
	sbiw r24,8
	brsh .L114
	ldi r24,lo8(playersHead)
	ldi r25,hi8(playersHead)
	call resetPlayers
	ldi r24,lo8(notesHead)
	ldi r25,hi8(notesHead)
	call resetNotes
	sts roundTurn+1,r5
	sts roundTurn,r4
	rjmp .L128
.L114:
	ldi r24,lo8(.LC6)
	ldi r25,hi8(.LC6)
	call puts
	rjmp .L100
.L107:
	lds r24,roundTurn+1
	push r24
	lds r24,roundTurn
	push r24
	push r11
	push r10
	call printf
	lds r24,roundTurn
	lds r25,roundTurn+1
	adiw r24,1
	sts roundTurn+1,r25
	sts roundTurn,r24
	lds r24,playersHead
	lds r25,playersHead+1
	sts currentPlayer+1,r25
	sts currentPlayer,r24
	sts state,r17
	rjmp .L129
.L108:
	lds r24,notesHead
	lds r25,notesHead+1
	sts currentNote+1,r25
	sts currentNote,r24
	lds r24,t0millis
	lds r25,t0millis+1
	sts turnStartTimestamp+1,r25
	sts turnStartTimestamp,r24
	lds r30,currentPlayer
	lds r31,currentPlayer+1
	ldd r24,Z+1
	push r24
	ld r24,Z
	push r24
	push r13
	push r12
	call printf
	sts state,r3
	rjmp .L129
.L109:
	lds r24,turnStartTimestamp
	lds r25,turnStartTimestamp+1
	call getTimeInterval
	cpi r24,-119
	sbci r25,19
	brlt .L115
	ldi r24,lo8(.LC9)
	ldi r25,hi8(.LC9)
	call puts
	ldi r31,lo8(6)
	sts state,r31
	rjmp .L100
.L115:
	lds r24,buttonPressed
	tst r24
	brne .+2
	rjmp .L100
	sts buttonPressed,__zero_reg__
	lds r20,whichButtonPressed
	ldi r21,0
	lds r22,currentNote
	lds r23,currentNote+1
	ldi r24,lo8(notesHead)
	ldi r25,hi8(notesHead)
	call verifyNote
	cpi r24,1
	cpc r25,__zero_reg__
	breq .L118
	cpi r24,2
	cpc r25,__zero_reg__
	breq .L119
	or r24,r25
	brne .L117
	ldi r18,lo8(5)
	sts state,r18
	rjmp .L117
.L118:
	lds r30,currentNote
	lds r31,currentNote+1
	ldd r24,Z+2
	ldd r25,Z+3
	sts currentNote+1,r25
	sts currentNote,r24
	rjmp .L117
.L119:
	ldi r24,lo8(7)
	sts state,r24
.L117:
	lds r24,t0millis
	lds r25,t0millis+1
	sts turnStartTimestamp+1,r25
	sts turnStartTimestamp,r24
	rjmp .L100
.L110:
	ldi r24,lo8(.LC10)
	ldi r25,hi8(.LC10)
	call puts
.L111:
	lds r22,currentPlayer
	lds r23,currentPlayer+1
	movw r26,r22
	adiw r26,2
	ld r24,X+
	ld r25,X
	sbiw r26,2+1
	sbiw r24,0
	brne .L121
	sts state,r16
	rjmp .L122
.L121:
	sts currentPlayer+1,r25
	sts currentPlayer,r24
	sts state,r17
.L122:
	ldi r24,lo8(playersHead)
	ldi r25,hi8(playersHead)
	call removePlayer
	lds r30,playersHead
	lds r31,playersHead+1
	ldd r24,Z+2
	ldd r25,Z+3
	or r24,r25
	breq .+2
	rjmp .L100
	ldd r24,Z+1
	push r24
	ld r24,Z
	push r24
	push r15
	push r14
	call printf
	sts state,__zero_reg__
.L129:
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	rjmp .L100
.L112:
	lds r30,currentPlayer
	lds r31,currentPlayer+1
	ldd r24,Z+2
	ldd r25,Z+3
	sbiw r24,0
	brne .L123
.L128:
	sts state,r16
	rjmp .L100
.L123:
	sts currentPlayer+1,r25
	sts currentPlayer,r24
	sts state,r17
	rjmp .L100
	.size	main, .-main
	.local	b.1876
	.comm	b.1876,8,1
	.local	rxp.1877
	.comm	rxp.1877,2,1
.global	currentNote
	.section .bss
	.type	currentNote, @object
	.size	currentNote, 2
currentNote:
	.zero	2
.global	notesHead
	.type	notesHead, @object
	.size	notesHead, 2
notesHead:
	.zero	2
.global	currentPlayer
	.type	currentPlayer, @object
	.size	currentPlayer, 2
currentPlayer:
	.zero	2
.global	playersHead
	.type	playersHead, @object
	.size	playersHead, 2
playersHead:
	.zero	2
	.comm	whichButtonPressed,1,1
	.comm	buttonPressed,1,1
.global	state
	.type	state, @object
	.size	state, 1
state:
	.zero	1
.global	buzzerState
	.type	buzzerState, @object
	.size	buzzerState, 1
buzzerState:
	.zero	1
.global	overflowInMicrosseconds
	.section	.rodata
	.type	overflowInMicrosseconds, @object
	.size	overflowInMicrosseconds, 2
overflowInMicrosseconds:
	.word	1024
	.comm	roundTurn,2,1
	.comm	players,2,1
	.comm	buzzerStartTime,2,1
	.comm	buzzerTime,2,1
	.comm	buzzerDuration,2,1
	.comm	buzzerPeriod,2,1
	.comm	timer1debounce,2,1
	.comm	timer0debounce,2,1
	.comm	turnStartTimestamp,2,1
	.comm	t0fraction,2,1
	.comm	t0millis,2,1
	.ident	"GCC: (GNU) 4.9.2"
.global __do_copy_data
.global __do_clear_bss
