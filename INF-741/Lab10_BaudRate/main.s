	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	circular_buffer_pop
	.type	circular_buffer_pop, @function
circular_buffer_pop:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r24,0
	ldi r25,0
	ret
	.size	circular_buffer_pop, .-circular_buffer_pop
.global	circular_buffer_push
	.type	circular_buffer_push, @function
circular_buffer_push:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r24,0
	ldi r25,0
	ret
	.size	circular_buffer_push, .-circular_buffer_push
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* #APP */
 ;  22 "main.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L4:
	lds r24,192
	sbrs r24,5
	rjmp .L4
	sts 198,__zero_reg__
	rjmp .L4
	.size	main, .-main
	.text
.global	__vector_18
	.type	__vector_18, @function
__vector_18:
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
	.size	__vector_18, .-__vector_18
	.ident	"GCC: (GNU) 4.9.2"
