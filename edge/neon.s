	.cpu cortex-a9
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"neon.c"
	.text
	.align	2
	.global	initializeArray_neon
	.arch armv7-a
	.syntax unified
	.arm
	.fpu neon
	.type	initializeArray_neon, %function
initializeArray_neon:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #60
	str	r0, [fp, #-56]
	str	r1, [fp, #-60]
	mov	r3, #2
	strh	r3, [fp, #-30]	@ movhi
	ldrh	r3, [fp, #-30]	@ movhi
	vdup.16	q8, r3
	vstr	d16, [fp, #-28]
	vstr	d17, [fp, #-20]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L3
.L4:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #1
	ldr	r2, [fp, #-56]
	add	r3, r2, r3
	str	r3, [fp, #-36]
	vldr	d16, [fp, #-28]
	vldr	d17, [fp, #-20]
	vstr	d16, [fp, #-52]
	vstr	d17, [fp, #-44]
	ldr	r3, [fp, #-36]
	vldr	d16, [fp, #-52]
	vldr	d17, [fp, #-44]
	vst1.16	{d16-d17}, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #8
	str	r3, [fp, #-8]
.L3:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-60]
	cmp	r2, r3
	blt	.L4
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	initializeArray_neon, .-initializeArray_neon
	.align	2
	.global	sum_neon
	.syntax unified
	.arm
	.fpu neon
	.type	sum_neon, %function
sum_neon:
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #204
	str	r0, [fp, #-200]
	str	r1, [fp, #-204]
	mov	r3, #0
	strh	r3, [fp, #-70]	@ movhi
	ldrh	r3, [fp, #-70]	@ movhi
	vdup.16	q8, r3
	vstr	d16, [fp, #-20]
	vstr	d17, [fp, #-12]
	vmov.i32	d16, #0  @ di
	vstr.64	d16, [fp, #-36]	@ int
	mov	r3, #0
	str	r3, [fp, #-24]
	b	.L7
.L10:
	ldr	r3, [fp, #-24]
	lsl	r3, r3, #1
	ldr	r2, [fp, #-200]
	add	r3, r2, r3
	str	r3, [fp, #-112]
	ldr	r3, [fp, #-112]
	vld1.16	{d16-d17}, [r3]
	vstr	d16, [fp, #-52]
	vstr	d17, [fp, #-44]
	vldr	d16, [fp, #-20]
	vldr	d17, [fp, #-12]
	vstr	d16, [fp, #-92]
	vstr	d17, [fp, #-84]
	vldr	d16, [fp, #-52]
	vldr	d17, [fp, #-44]
	vstr	d16, [fp, #-108]
	vstr	d17, [fp, #-100]
	vldr	d18, [fp, #-92]
	vldr	d19, [fp, #-84]
	vldr	d16, [fp, #-108]
	vldr	d17, [fp, #-100]
	vadd.i16	q8, q9, q8
	vstr	d16, [fp, #-20]
	vstr	d17, [fp, #-12]
	ldr	r3, [fp, #-24]
	add	r3, r3, #8
	str	r3, [fp, #-24]
.L7:
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-204]
	cmp	r2, r3
	blt	.L10
	vldr	d16, [fp, #-20]
	vldr	d17, [fp, #-12]
	vstr	d16, [fp, #-196]
	vstr	d17, [fp, #-188]
	vldr	d16, [fp, #-196]
	vldr	d17, [fp, #-188]
	vstr	d16, [fp, #-60]
	vldr	d16, [fp, #-20]
	vldr	d17, [fp, #-12]
	vstr	d16, [fp, #-180]
	vstr	d17, [fp, #-172]
	vldr	d16, [fp, #-180]
	vldr	d17, [fp, #-172]
	vmov	d16, d17  @ v4hi
	vstr	d16, [fp, #-68]
	vldr	d16, [fp, #-60]
	vstr	d16, [fp, #-156]
	vldr	d16, [fp, #-68]
	vstr	d16, [fp, #-164]
	vldr	d17, [fp, #-156]
	vldr	d16, [fp, #-164]
	vadd.i16	d16, d17, d16
	vstr	d16, [fp, #-60]
	vldr	d16, [fp, #-60]
	vstr	d16, [fp, #-148]
	vldr	d16, [fp, #-148]
	vmov.s16	r3, d16[0]
	sxth	r3, r3
	vdup.16	d16, r3
	vshr.s64	d16, d16, #48
	ldrd	r0, [fp, #-36]
	vmov	r2, r3, d16	@ int
	adds	r2, r2, r0
	adc	r3, r3, r1
	strd	r2, [fp, #-36]
	vldr	d16, [fp, #-60]
	vstr	d16, [fp, #-140]
	vldr	d16, [fp, #-140]
	vmov.s16	r3, d16[1]
	sxth	r3, r3
	vdup.16	d16, r3
	vshr.s64	d16, d16, #48
	ldrd	r0, [fp, #-36]
	vmov	r2, r3, d16	@ int
	adds	r2, r2, r0
	adc	r3, r3, r1
	strd	r2, [fp, #-36]
	vldr	d16, [fp, #-60]
	vstr	d16, [fp, #-132]
	vldr	d16, [fp, #-132]
	vmov.s16	r3, d16[2]
	sxth	r3, r3
	vdup.16	d16, r3
	vshr.s64	d16, d16, #48
	ldrd	r0, [fp, #-36]
	vmov	r2, r3, d16	@ int
	adds	r2, r2, r0
	adc	r3, r3, r1
	strd	r2, [fp, #-36]
	vldr	d16, [fp, #-60]
	vstr	d16, [fp, #-124]
	vldr	d16, [fp, #-124]
	vmov.s16	r3, d16[3]
	sxth	r3, r3
	vdup.16	d16, r3
	vshr.s64	d16, d16, #48
	ldrd	r0, [fp, #-36]
	vmov	r2, r3, d16	@ int
	adds	r2, r2, r0
	adc	r3, r3, r1
	strd	r2, [fp, #-36]
	ldr	r3, [fp, #-36]
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	sum_neon, .-sum_neon
	.ident	"GCC: (GNU) 8.2.0"
