; Listing generated by Microsoft (R) Optimizing Compiler Version 19.00.24210.0 

	TITLE	C:\Users\yanshuyu\Documents\Visual Studio 2015\Projects\Collection\3party\zlib-1.2.8\adler32.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

PUBLIC	_adler32@12
PUBLIC	_adler32_combine@12
PUBLIC	_adler32_combine64@16
EXTRN	__allrem:PROC
; Function compile flags: /Odtp
; File c:\users\yanshuyu\documents\visual studio 2015\projects\collection\3party\zlib-1.2.8\adler32.c
_TEXT	SEGMENT
_adler1$ = 8						; size = 4
_adler2$ = 12						; size = 4
_len2$ = 16						; size = 8
_adler32_combine64@16 PROC

; 177  : {

	push	ebp
	mov	ebp, esp

; 178  :     return adler32_combine_(adler1, adler2, len2);

	mov	eax, DWORD PTR _len2$[ebp+4]
	push	eax
	mov	ecx, DWORD PTR _len2$[ebp]
	push	ecx
	mov	edx, DWORD PTR _adler2$[ebp]
	push	edx
	mov	eax, DWORD PTR _adler1$[ebp]
	push	eax
	call	_adler32_combine_
	add	esp, 16					; 00000010H

; 179  : }

	pop	ebp
	ret	16					; 00000010H
_adler32_combine64@16 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File c:\users\yanshuyu\documents\visual studio 2015\projects\collection\3party\zlib-1.2.8\adler32.c
_TEXT	SEGMENT
_rem$ = -12						; size = 4
_sum1$ = -8						; size = 4
_sum2$ = -4						; size = 4
_adler1$ = 8						; size = 4
_adler2$ = 12						; size = 4
_len2$ = 16						; size = 8
_adler32_combine_ PROC

; 140  : {

	push	ebp
	mov	ebp, esp
	sub	esp, 12					; 0000000cH

; 141  :     unsigned long sum1;
; 142  :     unsigned long sum2;
; 143  :     unsigned rem;
; 144  : 
; 145  :     /* for negative len, return invalid adler32 as a clue for debugging */
; 146  :     if (len2 < 0)

	cmp	DWORD PTR _len2$[ebp+4], 0
	jg	SHORT $LN2@adler32_co
	jl	SHORT $LN8@adler32_co
	cmp	DWORD PTR _len2$[ebp], 0
	jae	SHORT $LN2@adler32_co
$LN8@adler32_co:

; 147  :         return 0xffffffffUL;

	or	eax, -1
	jmp	$LN1@adler32_co
$LN2@adler32_co:

; 148  : 
; 149  :     /* the derivation of this formula is left as an exercise for the reader */
; 150  :     MOD63(len2);                /* assumes len2 >= 0 */

	push	0
	push	65521					; 0000fff1H
	mov	eax, DWORD PTR _len2$[ebp+4]
	push	eax
	mov	ecx, DWORD PTR _len2$[ebp]
	push	ecx
	call	__allrem
	mov	DWORD PTR _len2$[ebp], eax
	mov	DWORD PTR _len2$[ebp+4], edx

; 151  :     rem = (unsigned)len2;

	mov	edx, DWORD PTR _len2$[ebp]
	mov	DWORD PTR _rem$[ebp], edx

; 152  :     sum1 = adler1 & 0xffff;

	mov	eax, DWORD PTR _adler1$[ebp]
	and	eax, 65535				; 0000ffffH
	mov	DWORD PTR _sum1$[ebp], eax

; 153  :     sum2 = rem * sum1;

	mov	ecx, DWORD PTR _rem$[ebp]
	imul	ecx, DWORD PTR _sum1$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx

; 154  :     MOD(sum2);

	mov	eax, DWORD PTR _sum2$[ebp]
	xor	edx, edx
	mov	ecx, 65521				; 0000fff1H
	div	ecx
	mov	DWORD PTR _sum2$[ebp], edx

; 155  :     sum1 += (adler2 & 0xffff) + BASE - 1;

	mov	edx, DWORD PTR _adler2$[ebp]
	and	edx, 65535				; 0000ffffH
	mov	eax, DWORD PTR _sum1$[ebp]
	lea	ecx, DWORD PTR [eax+edx+65520]
	mov	DWORD PTR _sum1$[ebp], ecx

; 156  :     sum2 += ((adler1 >> 16) & 0xffff) + ((adler2 >> 16) & 0xffff) + BASE - rem;

	mov	edx, DWORD PTR _adler1$[ebp]
	shr	edx, 16					; 00000010H
	and	edx, 65535				; 0000ffffH
	mov	eax, DWORD PTR _adler2$[ebp]
	shr	eax, 16					; 00000010H
	and	eax, 65535				; 0000ffffH
	lea	ecx, DWORD PTR [edx+eax+65521]
	sub	ecx, DWORD PTR _rem$[ebp]
	add	ecx, DWORD PTR _sum2$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx

; 157  :     if (sum1 >= BASE) sum1 -= BASE;

	cmp	DWORD PTR _sum1$[ebp], 65521		; 0000fff1H
	jb	SHORT $LN3@adler32_co
	mov	edx, DWORD PTR _sum1$[ebp]
	sub	edx, 65521				; 0000fff1H
	mov	DWORD PTR _sum1$[ebp], edx
$LN3@adler32_co:

; 158  :     if (sum1 >= BASE) sum1 -= BASE;

	cmp	DWORD PTR _sum1$[ebp], 65521		; 0000fff1H
	jb	SHORT $LN4@adler32_co
	mov	eax, DWORD PTR _sum1$[ebp]
	sub	eax, 65521				; 0000fff1H
	mov	DWORD PTR _sum1$[ebp], eax
$LN4@adler32_co:

; 159  :     if (sum2 >= (BASE << 1)) sum2 -= (BASE << 1);

	cmp	DWORD PTR _sum2$[ebp], 131042		; 0001ffe2H
	jb	SHORT $LN5@adler32_co
	mov	ecx, DWORD PTR _sum2$[ebp]
	sub	ecx, 131042				; 0001ffe2H
	mov	DWORD PTR _sum2$[ebp], ecx
$LN5@adler32_co:

; 160  :     if (sum2 >= BASE) sum2 -= BASE;

	cmp	DWORD PTR _sum2$[ebp], 65521		; 0000fff1H
	jb	SHORT $LN6@adler32_co
	mov	edx, DWORD PTR _sum2$[ebp]
	sub	edx, 65521				; 0000fff1H
	mov	DWORD PTR _sum2$[ebp], edx
$LN6@adler32_co:

; 161  :     return sum1 | (sum2 << 16);

	mov	eax, DWORD PTR _sum2$[ebp]
	shl	eax, 16					; 00000010H
	or	eax, DWORD PTR _sum1$[ebp]
$LN1@adler32_co:

; 162  : }

	mov	esp, ebp
	pop	ebp
	ret	0
_adler32_combine_ ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File c:\users\yanshuyu\documents\visual studio 2015\projects\collection\3party\zlib-1.2.8\adler32.c
_TEXT	SEGMENT
_adler1$ = 8						; size = 4
_adler2$ = 12						; size = 4
_len2$ = 16						; size = 4
_adler32_combine@12 PROC

; 169  : {

	push	ebp
	mov	ebp, esp

; 170  :     return adler32_combine_(adler1, adler2, len2);

	mov	eax, DWORD PTR _len2$[ebp]
	cdq
	push	edx
	push	eax
	mov	eax, DWORD PTR _adler2$[ebp]
	push	eax
	mov	ecx, DWORD PTR _adler1$[ebp]
	push	ecx
	call	_adler32_combine_
	add	esp, 16					; 00000010H

; 171  : }

	pop	ebp
	ret	12					; 0000000cH
_adler32_combine@12 ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File c:\users\yanshuyu\documents\visual studio 2015\projects\collection\3party\zlib-1.2.8\adler32.c
_TEXT	SEGMENT
tv298 = -16						; size = 4
tv83 = -12						; size = 4
_n$ = -8						; size = 4
_sum2$ = -4						; size = 4
_adler$ = 8						; size = 4
_buf$ = 12						; size = 4
_len$ = 16						; size = 4
_adler32@12 PROC

; 69   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 16					; 00000010H

; 70   :     unsigned long sum2;
; 71   :     unsigned n;
; 72   : 
; 73   :     /* split Adler-32 into component sums */
; 74   :     sum2 = (adler >> 16) & 0xffff;

	mov	eax, DWORD PTR _adler$[ebp]
	shr	eax, 16					; 00000010H
	and	eax, 65535				; 0000ffffH
	mov	DWORD PTR _sum2$[ebp], eax

; 75   :     adler &= 0xffff;

	mov	ecx, DWORD PTR _adler$[ebp]
	and	ecx, 65535				; 0000ffffH
	mov	DWORD PTR _adler$[ebp], ecx

; 76   : 
; 77   :     /* in case user likes doing a byte at a time, keep it fast */
; 78   :     if (len == 1) {

	cmp	DWORD PTR _len$[ebp], 1
	jne	SHORT $LN13@adler32

; 79   :         adler += buf[0];

	mov	edx, 1
	imul	eax, edx, 0
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx

; 80   :         if (adler >= BASE)

	cmp	DWORD PTR _adler$[ebp], 65521		; 0000fff1H
	jb	SHORT $LN14@adler32

; 81   :             adler -= BASE;

	mov	eax, DWORD PTR _adler$[ebp]
	sub	eax, 65521				; 0000fff1H
	mov	DWORD PTR _adler$[ebp], eax
$LN14@adler32:

; 82   :         sum2 += adler;

	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx

; 83   :         if (sum2 >= BASE)

	cmp	DWORD PTR _sum2$[ebp], 65521		; 0000fff1H
	jb	SHORT $LN15@adler32

; 84   :             sum2 -= BASE;

	mov	edx, DWORD PTR _sum2$[ebp]
	sub	edx, 65521				; 0000fff1H
	mov	DWORD PTR _sum2$[ebp], edx
$LN15@adler32:

; 85   :         return adler | (sum2 << 16);

	mov	eax, DWORD PTR _sum2$[ebp]
	shl	eax, 16					; 00000010H
	or	eax, DWORD PTR _adler$[ebp]
	jmp	$LN1@adler32
$LN13@adler32:

; 86   :     }
; 87   : 
; 88   :     /* initial Adler-32 value (deferred check for len == 1 speed) */
; 89   :     if (buf == Z_NULL)

	cmp	DWORD PTR _buf$[ebp], 0
	jne	SHORT $LN16@adler32

; 90   :         return 1L;

	mov	eax, 1
	jmp	$LN1@adler32
$LN16@adler32:

; 91   : 
; 92   :     /* in case short lengths are provided, keep it somewhat fast */
; 93   :     if (len < 16) {

	cmp	DWORD PTR _len$[ebp], 16		; 00000010H
	jae	SHORT $LN4@adler32
$LN2@adler32:

; 94   :         while (len--) {

	mov	eax, DWORD PTR _len$[ebp]
	mov	DWORD PTR tv83[ebp], eax
	mov	ecx, DWORD PTR _len$[ebp]
	sub	ecx, 1
	mov	DWORD PTR _len$[ebp], ecx
	cmp	DWORD PTR tv83[ebp], 0
	je	SHORT $LN3@adler32

; 95   :             adler += *buf++;

	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _buf$[ebp]
	add	ecx, 1
	mov	DWORD PTR _buf$[ebp], ecx

; 96   :             sum2 += adler;

	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx

; 97   :         }

	jmp	SHORT $LN2@adler32
$LN3@adler32:

; 98   :         if (adler >= BASE)

	cmp	DWORD PTR _adler$[ebp], 65521		; 0000fff1H
	jb	SHORT $LN18@adler32

; 99   :             adler -= BASE;

	mov	eax, DWORD PTR _adler$[ebp]
	sub	eax, 65521				; 0000fff1H
	mov	DWORD PTR _adler$[ebp], eax
$LN18@adler32:

; 100  :         MOD28(sum2);            /* only added so many BASE's */

	mov	eax, DWORD PTR _sum2$[ebp]
	xor	edx, edx
	mov	ecx, 65521				; 0000fff1H
	div	ecx
	mov	DWORD PTR _sum2$[ebp], edx

; 101  :         return adler | (sum2 << 16);

	mov	eax, DWORD PTR _sum2$[ebp]
	shl	eax, 16					; 00000010H
	or	eax, DWORD PTR _adler$[ebp]
	jmp	$LN1@adler32
$LN4@adler32:

; 102  :     }
; 103  : 
; 104  :     /* do length NMAX blocks -- requires just one modulo operation */
; 105  :     while (len >= NMAX) {

	cmp	DWORD PTR _len$[ebp], 5552		; 000015b0H
	jb	$LN5@adler32

; 106  :         len -= NMAX;

	mov	edx, DWORD PTR _len$[ebp]
	sub	edx, 5552				; 000015b0H
	mov	DWORD PTR _len$[ebp], edx

; 107  :         n = NMAX / 16;          /* NMAX is divisible by 16 */

	mov	DWORD PTR _n$[ebp], 347			; 0000015bH
$LN8@adler32:

; 108  :         do {
; 109  :             DO16(buf);          /* 16 sums unrolled */

	mov	eax, 1
	imul	ecx, eax, 0
	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx
	mov	edx, 1
	shl	edx, 0
	mov	eax, DWORD PTR _buf$[ebp]
	movzx	ecx, BYTE PTR [eax+edx]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], ecx
	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx
	mov	eax, 1
	shl	eax, 1
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax
	mov	ecx, 1
	imul	edx, ecx, 3
	mov	eax, DWORD PTR _buf$[ebp]
	movzx	ecx, BYTE PTR [eax+edx]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], ecx
	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx
	mov	eax, 1
	shl	eax, 2
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax
	mov	ecx, 1
	imul	edx, ecx, 5
	mov	eax, DWORD PTR _buf$[ebp]
	movzx	ecx, BYTE PTR [eax+edx]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], ecx
	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx
	mov	eax, 1
	imul	ecx, eax, 6
	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx
	mov	edx, 1
	imul	eax, edx, 7
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax
	mov	ecx, 1
	shl	ecx, 3
	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx
	mov	edx, 1
	imul	eax, edx, 9
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax
	mov	ecx, 1
	imul	edx, ecx, 10
	mov	eax, DWORD PTR _buf$[ebp]
	movzx	ecx, BYTE PTR [eax+edx]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], ecx
	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx
	mov	eax, 1
	imul	ecx, eax, 11
	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx
	mov	edx, 1
	imul	eax, edx, 12
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax
	mov	ecx, 1
	imul	edx, ecx, 13
	mov	eax, DWORD PTR _buf$[ebp]
	movzx	ecx, BYTE PTR [eax+edx]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], ecx
	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx
	mov	eax, 1
	imul	ecx, eax, 14
	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx
	mov	edx, 1
	imul	eax, edx, 15
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax

; 110  :             buf += 16;

	mov	ecx, DWORD PTR _buf$[ebp]
	add	ecx, 16					; 00000010H
	mov	DWORD PTR _buf$[ebp], ecx

; 111  :         } while (--n);

	mov	edx, DWORD PTR _n$[ebp]
	sub	edx, 1
	mov	DWORD PTR _n$[ebp], edx
	jne	$LN8@adler32

; 112  :         MOD(adler);

	mov	eax, DWORD PTR _adler$[ebp]
	xor	edx, edx
	mov	ecx, 65521				; 0000fff1H
	div	ecx
	mov	DWORD PTR _adler$[ebp], edx

; 113  :         MOD(sum2);

	mov	eax, DWORD PTR _sum2$[ebp]
	xor	edx, edx
	mov	ecx, 65521				; 0000fff1H
	div	ecx
	mov	DWORD PTR _sum2$[ebp], edx

; 114  :     }

	jmp	$LN4@adler32
$LN5@adler32:

; 115  : 
; 116  :     /* do remaining bytes (less than NMAX, still just one modulo) */
; 117  :     if (len) {                  /* avoid modulos if none remaining */

	cmp	DWORD PTR _len$[ebp], 0
	je	$LN19@adler32
$LN9@adler32:

; 118  :         while (len >= 16) {

	cmp	DWORD PTR _len$[ebp], 16		; 00000010H
	jb	$LN11@adler32

; 119  :             len -= 16;

	mov	edx, DWORD PTR _len$[ebp]
	sub	edx, 16					; 00000010H
	mov	DWORD PTR _len$[ebp], edx

; 120  :             DO16(buf);

	mov	eax, 1
	imul	ecx, eax, 0
	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx
	mov	edx, 1
	shl	edx, 0
	mov	eax, DWORD PTR _buf$[ebp]
	movzx	ecx, BYTE PTR [eax+edx]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], ecx
	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx
	mov	eax, 1
	shl	eax, 1
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax
	mov	ecx, 1
	imul	edx, ecx, 3
	mov	eax, DWORD PTR _buf$[ebp]
	movzx	ecx, BYTE PTR [eax+edx]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], ecx
	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx
	mov	eax, 1
	shl	eax, 2
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax
	mov	ecx, 1
	imul	edx, ecx, 5
	mov	eax, DWORD PTR _buf$[ebp]
	movzx	ecx, BYTE PTR [eax+edx]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], ecx
	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx
	mov	eax, 1
	imul	ecx, eax, 6
	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx
	mov	edx, 1
	imul	eax, edx, 7
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax
	mov	ecx, 1
	shl	ecx, 3
	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx
	mov	edx, 1
	imul	eax, edx, 9
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax
	mov	ecx, 1
	imul	edx, ecx, 10
	mov	eax, DWORD PTR _buf$[ebp]
	movzx	ecx, BYTE PTR [eax+edx]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], ecx
	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx
	mov	eax, 1
	imul	ecx, eax, 11
	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx
	mov	edx, 1
	imul	eax, edx, 12
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax
	mov	ecx, 1
	imul	edx, ecx, 13
	mov	eax, DWORD PTR _buf$[ebp]
	movzx	ecx, BYTE PTR [eax+edx]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], ecx
	mov	edx, DWORD PTR _sum2$[ebp]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], edx
	mov	eax, 1
	imul	ecx, eax, 14
	mov	edx, DWORD PTR _buf$[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], eax
	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx
	mov	edx, 1
	imul	eax, edx, 15
	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx+eax]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _sum2$[ebp]
	add	eax, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], eax

; 121  :             buf += 16;

	mov	ecx, DWORD PTR _buf$[ebp]
	add	ecx, 16					; 00000010H
	mov	DWORD PTR _buf$[ebp], ecx

; 122  :         }

	jmp	$LN9@adler32
$LN11@adler32:

; 123  :         while (len--) {

	mov	edx, DWORD PTR _len$[ebp]
	mov	DWORD PTR tv298[ebp], edx
	mov	eax, DWORD PTR _len$[ebp]
	sub	eax, 1
	mov	DWORD PTR _len$[ebp], eax
	cmp	DWORD PTR tv298[ebp], 0
	je	SHORT $LN12@adler32

; 124  :             adler += *buf++;

	mov	ecx, DWORD PTR _buf$[ebp]
	movzx	edx, BYTE PTR [ecx]
	add	edx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _adler$[ebp], edx
	mov	eax, DWORD PTR _buf$[ebp]
	add	eax, 1
	mov	DWORD PTR _buf$[ebp], eax

; 125  :             sum2 += adler;

	mov	ecx, DWORD PTR _sum2$[ebp]
	add	ecx, DWORD PTR _adler$[ebp]
	mov	DWORD PTR _sum2$[ebp], ecx

; 126  :         }

	jmp	SHORT $LN11@adler32
$LN12@adler32:

; 127  :         MOD(adler);

	mov	eax, DWORD PTR _adler$[ebp]
	xor	edx, edx
	mov	ecx, 65521				; 0000fff1H
	div	ecx
	mov	DWORD PTR _adler$[ebp], edx

; 128  :         MOD(sum2);

	mov	eax, DWORD PTR _sum2$[ebp]
	xor	edx, edx
	mov	ecx, 65521				; 0000fff1H
	div	ecx
	mov	DWORD PTR _sum2$[ebp], edx
$LN19@adler32:

; 129  :     }
; 130  : 
; 131  :     /* return recombined sums */
; 132  :     return adler | (sum2 << 16);

	mov	eax, DWORD PTR _sum2$[ebp]
	shl	eax, 16					; 00000010H
	or	eax, DWORD PTR _adler$[ebp]
$LN1@adler32:

; 133  : }

	mov	esp, ebp
	pop	ebp
	ret	12					; 0000000cH
_adler32@12 ENDP
_TEXT	ENDS
END
