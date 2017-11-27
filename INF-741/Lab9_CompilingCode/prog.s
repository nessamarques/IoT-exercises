	.file	"prog.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	delay_ms
	.type	delay_ms, @function
delay_ms:
	push r28
	push r29
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
/* stack size = 4 */
.L__stack_usage = 4
.L2:
	tst r24
	breq .L7
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
.L3:
	ldd r18,Y+1
	ldd r19,Y+2
	cpi r18,57
	cpc r19,__zero_reg__
	breq .L8
	ldd r18,Y+1
	ldd r19,Y+2
	subi r18,-1
	sbci r19,-1
	std Y+2,r19
	std Y+1,r18
	rjmp .L3
.L8:
	subi r24,lo8(-(-1))
	rjmp .L2
.L7:
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	delay_ms, .-delay_ms
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r24,lo8(-1)
	out 0x4,r24
	ldi r17,lo8(-1)
.L12:
	out 0x5,r17
	ldi r28,lo8(10)
	ldi r29,0
.L10:
	ldi r24,lo8(-56)
	call delay_ms
	sbiw r28,1
	brne .L10
	out 0x5,__zero_reg__
	ldi r28,lo8(10)
	ldi r29,0
.L11:
	ldi r24,lo8(-56)
	call delay_ms
	sbiw r28,1
	brne .L11
	rjmp .L12
	.size	main, .-main
	.ident	"GCC: (GNU) 4.9.2"
