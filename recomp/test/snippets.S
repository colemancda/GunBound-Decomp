/* Hand-written x86-32 test snippets for the lifter.
 *
 * Every t_* function is cdecl:  void t(uint32 a, uint32 b, uint32 c, uint32 d, uint32 out[8])
 * and writes its results (values and raw EFLAGS) to out[]. The same code is run
 * natively (32-bit reference build) and through the lifter; the outputs must match.
 *
 * x87 register-register arithmetic is emitted as raw bytes so that neither the
 * assembler's nor a disassembler's fsub/fsubr naming can influence the test.
 */
        .intel_syntax noprefix
        .code32
        .text

#define A   [esp+4]
#define B   [esp+8]
#define C   [esp+12]
#define D   [esp+16]
#define OUT [esp+20]

        .macro FN name
        .globl \name
        .p2align 4, 0xCC
\name:
        .endm

/* ------------------------------------------------------------ add/sub family
 * c = EFLAGS to load first (carry-in for adc/sbb, and to see untouched flags). */
        .macro BINOP name, op, acc, width
        FN \name
        mov eax, A
        mov edx, OUT
        push dword ptr C
        popfd
        \op \acc, \width ptr B
        pushfd
        pop ecx
        mov [edx], eax
        mov [edx+4], ecx
        ret
        .endm

        /* same operation with a memory destination */
        .macro BINOPM name, op, reg, width
        FN \name
        mov eax, A
        mov ecx, B
        mov edx, OUT
        mov [edx], eax
        push dword ptr C
        popfd
        \op \width ptr [edx], \reg
        pushfd
        pop ecx
        mov [edx+4], ecx
        ret
        .endm

        BINOP t_add32, add, eax, dword
        BINOP t_adc32, adc, eax, dword
        BINOP t_sub32, sub, eax, dword
        BINOP t_sbb32, sbb, eax, dword
        BINOP t_cmp32, cmp, eax, dword
        BINOP t_and32, and, eax, dword
        BINOP t_or32, or, eax, dword
        BINOP t_xor32, xor, eax, dword
        BINOP t_test32, test, eax, dword
        BINOP t_add16, add, ax, word
        BINOP t_adc16, adc, ax, word
        BINOP t_sub16, sub, ax, word
        BINOP t_sbb16, sbb, ax, word
        BINOP t_cmp16, cmp, ax, word
        BINOP t_and16, and, ax, word
        BINOP t_add8, add, al, byte
        BINOP t_adc8, adc, al, byte
        BINOP t_sub8, sub, al, byte
        BINOP t_sbb8, sbb, al, byte
        BINOP t_cmp8, cmp, al, byte
        BINOP t_xor8, xor, al, byte
        BINOPM t_addm32, add, ecx, dword
        BINOPM t_adcm32, adc, ecx, dword
        BINOPM t_sbbm16, sbb, cx, word
        BINOPM t_subm8, sub, cl, byte
        BINOPM t_xorm8h, xor, ch, byte

        .macro UNOP name, op, acc
        FN \name
        mov eax, A
        mov edx, OUT
        push dword ptr C
        popfd
        \op \acc
        pushfd
        pop ecx
        mov [edx], eax
        mov [edx+4], ecx
        ret
        .endm

        UNOP t_inc32, inc, eax
        UNOP t_dec32, dec, eax
        UNOP t_neg32, neg, eax
        UNOP t_not32, not, eax
        UNOP t_inc16, inc, ax
        UNOP t_dec16, dec, ax
        UNOP t_neg16, neg, ax
        UNOP t_inc8, inc, al
        UNOP t_dec8, dec, al
        UNOP t_neg8, neg, al
        UNOP t_inc8h, inc, ah
        UNOP t_not8h, not, ah

/* --------------------------------------------------------- shifts and rotates
 * a = value, b = count (in CL), c = EFLAGS to load first. */
        .macro SHIFT name, op, acc
        FN \name
        mov eax, A
        mov ecx, B
        mov edx, OUT
        push dword ptr C
        popfd
        \op \acc, cl
        pushfd
        pop ecx
        mov [edx], eax
        mov [edx+4], ecx
        ret
        .endm

        SHIFT t_shl32, shl, eax
        SHIFT t_shr32, shr, eax
        SHIFT t_sar32, sar, eax
        SHIFT t_rol32, rol, eax
        SHIFT t_ror32, ror, eax
        SHIFT t_rcl32, rcl, eax
        SHIFT t_rcr32, rcr, eax
        SHIFT t_shl16, shl, ax
        SHIFT t_shr16, shr, ax
        SHIFT t_sar16, sar, ax
        SHIFT t_rol16, rol, ax
        SHIFT t_ror16, ror, ax
        SHIFT t_rcl16, rcl, ax
        SHIFT t_rcr16, rcr, ax
        SHIFT t_shl8, shl, al
        SHIFT t_shr8, shr, al
        SHIFT t_sar8, sar, al
        SHIFT t_rol8, rol, al
        SHIFT t_ror8, ror, al
        SHIFT t_rcl8, rcl, al
        SHIFT t_rcr8, rcr, al

        /* shift by 1 (the only count with a defined OF) and by immediates */
        .macro SHIFT1 name, op, acc
        FN \name
        mov eax, A
        mov edx, OUT
        push dword ptr C
        popfd
        \op \acc, 1
        pushfd
        pop ecx
        mov [edx], eax
        mov [edx+4], ecx
        ret
        .endm

        SHIFT1 t_shl32_1, shl, eax
        SHIFT1 t_shr32_1, shr, eax
        SHIFT1 t_sar32_1, sar, eax
        SHIFT1 t_rol32_1, rol, eax
        SHIFT1 t_ror32_1, ror, eax
        SHIFT1 t_rcl32_1, rcl, eax
        SHIFT1 t_rcr32_1, rcr, eax
        SHIFT1 t_shl8_1, shl, al
        SHIFT1 t_sar16_1, sar, ax
        SHIFT1 t_ror8_1, ror, al
        SHIFT1 t_rcr16_1, rcr, ax

        FN t_shift_imm              /* a -> six immediate-count results */
        mov edx, OUT
        mov eax, A
        shl eax, 5
        mov [edx], eax
        mov eax, A
        shr eax, 13
        mov [edx+4], eax
        mov eax, A
        sar eax, 31
        mov [edx+8], eax
        mov eax, A
        rol eax, 13
        mov [edx+12], eax
        mov eax, A
        ror ax, 4
        mov [edx+16], eax
        mov eax, A
        sar al, 3
        shl ah, 2
        mov [edx+20], eax
        mov eax, A
        shl eax, 4
        pushfd
        pop ecx
        mov [edx+24], ecx
        mov eax, A
        sar eax, 2
        pushfd
        pop ecx
        mov [edx+28], ecx
        ret

        FN t_shld32                 /* a, b = operands, c = count */
        push ebx
        mov eax, [esp+8]
        mov ebx, [esp+12]
        mov ecx, [esp+16]
        mov edx, [esp+24]
        push 0x202
        popfd
        shld eax, ebx, cl
        pushfd
        pop dword ptr [edx+4]
        mov [edx], eax
        mov eax, [esp+8]
        shrd eax, ebx, cl
        pushfd
        pop dword ptr [edx+12]
        mov [edx+8], eax
        mov eax, [esp+8]
        shld eax, ebx, 7
        mov [edx+16], eax
        mov eax, [esp+8]
        shrd eax, ebx, 31
        mov [edx+20], eax
        pop ebx
        ret

/* ------------------------------------------------------------ multiply/divide */
        FN t_mul32
        mov eax, A
        mov ecx, OUT
        push 0x202
        popfd
        mul dword ptr B
        mov [ecx], eax
        mov [ecx+4], edx
        pushfd
        pop dword ptr [ecx+8]
        mov eax, A
        push 0x202
        popfd
        imul dword ptr B
        mov [ecx+12], eax
        mov [ecx+16], edx
        pushfd
        pop dword ptr [ecx+20]
        mov eax, A
        imul eax, dword ptr B
        mov [ecx+24], eax
        pushfd
        pop dword ptr [ecx+28]
        ret

        FN t_mul16
        mov eax, A
        mov ecx, OUT
        mov edx, 0x11112222
        mul word ptr B
        mov [ecx], eax
        mov [ecx+4], edx
        pushfd
        pop dword ptr [ecx+8]
        mov eax, A
        mov edx, 0x33334444
        imul word ptr B
        mov [ecx+12], eax
        mov [ecx+16], edx
        pushfd
        pop dword ptr [ecx+20]
        mov eax, A
        imul ax, word ptr B
        mov [ecx+24], eax
        pushfd
        pop dword ptr [ecx+28]
        ret

        FN t_mul8
        mov eax, A
        mov ecx, OUT
        mul byte ptr B
        mov [ecx], eax
        pushfd
        pop dword ptr [ecx+4]
        mov eax, A
        imul byte ptr B
        mov [ecx+8], eax
        pushfd
        pop dword ptr [ecx+12]
        ret

        FN t_imul3
        mov ecx, OUT
        imul eax, dword ptr A, 0x12345
        mov [ecx], eax
        pushfd
        pop dword ptr [ecx+4]
        imul eax, dword ptr A, -7
        mov [ecx+8], eax
        pushfd
        pop dword ptr [ecx+12]
        mov edx, A
        imul eax, edx, 100
        mov [ecx+16], eax
        mov eax, 0x55550000
        imul ax, word ptr A, -300
        mov [ecx+20], eax
        pushfd
        pop dword ptr [ecx+24]
        ret

        FN t_div32                  /* b:a / c, unsigned */
        mov eax, A
        mov edx, B
        mov ecx, OUT
        div dword ptr C
        mov [ecx], eax
        mov [ecx+4], edx
        ret

        FN t_idiv32                 /* b:a / c, signed */
        mov eax, A
        mov edx, B
        mov ecx, OUT
        idiv dword ptr C
        mov [ecx], eax
        mov [ecx+4], edx
        ret

        FN t_cdq_idiv               /* a / b the way compilers do it */
        mov eax, A
        mov ecx, OUT
        cdq
        idiv dword ptr B
        mov [ecx], eax
        mov [ecx+4], edx
        mov eax, A
        cwde
        mov [ecx+8], eax
        mov eax, A
        cbw
        mov [ecx+12], eax
        mov eax, A
        mov edx, 0x77777777
        cwd
        mov [ecx+16], edx
        ret

        FN t_div16                  /* dx:ax = a, divisor c */
        mov eax, A
        mov edx, eax
        shr edx, 16
        mov ecx, OUT
        div word ptr C
        mov [ecx], eax
        mov [ecx+4], edx
        ret

        FN t_idiv16
        mov eax, A
        mov edx, eax
        shr edx, 16
        mov ecx, OUT
        idiv word ptr C
        mov [ecx], eax
        mov [ecx+4], edx
        ret

        FN t_div8                   /* ax = a, divisor c */
        mov eax, A
        mov ecx, OUT
        div byte ptr C
        mov [ecx], eax
        ret

        FN t_idiv8
        mov eax, A
        mov ecx, OUT
        idiv byte ptr C
        mov [ecx], eax
        ret

/* ---------------------------------------------------------- condition codes */
        .macro SETCC16
        .irp cc, o, no, b, ae, e, ne, be, a, s, ns, p, np, l, ge, le, g
        set\cc cl
        movzx ecx, cl
        lea ebx, [ecx + ebx*2]
        .endr
        .endm

        FN t_setcc_cmp              /* cmp a, b -> 16 setcc bits */
        push ebx
        mov ebx, 0
        mov eax, [esp+8]
        cmp eax, [esp+12]
        SETCC16
        mov edx, [esp+24]
        mov [edx], ebx
        mov ebx, 0
        mov eax, [esp+8]
        cmp al, [esp+12]
        SETCC16
        mov [edx+4], ebx
        mov ebx, 0
        mov eax, [esp+8]
        test eax, [esp+12]
        SETCC16
        mov [edx+8], ebx
        pop ebx
        ret

        FN t_setcc_flags            /* c = EFLAGS -> 16 setcc bits */
        push ebx
        mov ebx, 0
        push dword ptr [esp+16]
        popfd
        SETCC16
        mov edx, [esp+24]
        mov [edx], ebx
        pop ebx
        ret

        FN t_jcc_flags              /* c = EFLAGS -> 16 jcc bits */
        push ebx
        mov ebx, 0
        push dword ptr [esp+16]
        popfd
        .irp cc, o, no, b, ae, e, ne, be, a, s, ns, p, np, l, ge, le, g
        lea ebx, [ebx*2]
        j\cc 1f
        jmp 2f
1:      lea ebx, [ebx+1]
2:
        .endr
        mov edx, [esp+24]
        mov [edx], ebx
        pop ebx
        ret

        FN t_lahf_sahf              /* a = value for AH, c = EFLAGS */
        mov edx, OUT
        push dword ptr C
        popfd
        mov eax, 0
        lahf
        mov [edx], eax
        push 0x202
        popfd
        mov eax, A
        sahf
        pushfd
        pop dword ptr [edx+4]
        push 0xA97                 /* CF PF AF SF OF set, ZF clear */
        popfd
        mov eax, A
        sahf                       /* must leave OF alone */
        pushfd
        pop dword ptr [edx+8]
        push dword ptr C
        popfd
        cmc
        pushfd
        pop dword ptr [edx+12]
        stc
        pushfd
        pop dword ptr [edx+16]
        clc
        pushfd
        pop dword ptr [edx+20]
        ret

/* -------------------------------------------------------------- string ops
 * out[0..5] is a 24-byte scratch buffer; out[6], out[7] report registers/flags. */
        .macro FILLBUF              /* edx = out, args at [esp+12..] after 2 pushes */
        mov eax, [esp+12]
        mov [edx], eax
        not eax
        mov [edx+8], eax
        mov eax, [esp+16]
        mov [edx+4], eax
        not eax
        mov [edx+12], eax
        mov eax, [esp+12]
        xor eax, [esp+16]
        mov [edx+16], eax
        mov eax, [esp+12]
        add eax, [esp+16]
        mov [edx+20], eax
        .endm

        .macro STRREGS              /* out[6] = (esi-out) | (edi-out)<<8 | ecx<<16 */
        sub esi, edx
        sub edi, edx
        and esi, 0xFF
        and edi, 0xFF
        shl edi, 8
        shl ecx, 16
        or esi, edi
        or esi, ecx
        mov [edx+24], esi
        .endm

        FN t_rep_movsb              /* c = count (0..16), d bit0 = backward */
        push esi
        push edi
        mov edx, [esp+28]
        FILLBUF
        mov ecx, [esp+20]
        test byte ptr [esp+24], 1
        jnz 1f
        lea esi, [edx]
        lea edi, [edx+3]
        rep movsb
        jmp 2f
1:      std
        lea esi, [edx+19]
        lea edi, [edx+22]
        rep movsb
        cld
2:      STRREGS
        pop edi
        pop esi
        ret

        FN t_rep_movsd              /* c = count (0..4), d bit0 = backward */
        push esi
        push edi
        mov edx, [esp+28]
        FILLBUF
        mov ecx, [esp+20]
        test byte ptr [esp+24], 1
        jnz 1f
        lea esi, [edx]
        lea edi, [edx+4]
        rep movsd
        jmp 2f
1:      std
        lea esi, [edx+12]
        lea edi, [edx+20]
        rep movsd
        cld
2:      STRREGS
        pop edi
        pop esi
        ret

        FN t_rep_stos               /* a = fill value, c = count (0..5) */
        push esi
        push edi
        mov edx, [esp+28]
        FILLBUF
        mov eax, [esp+12]
        mov ecx, [esp+20]
        lea edi, [edx+1]
        rep stosb
        mov ecx, [esp+20]
        lea edi, [edx+8]
        rep stosd
        lea edi, [edx+6]
        stosw
        stosb
        mov esi, edx
        lodsb
        lodsw
        movsb
        movsw
        lodsd
        mov ecx, eax
        and ecx, 0xFF
        STRREGS
        pop edi
        pop esi
        ret

        FN t_strlen                 /* a, b = bytes of the string (zero terminated in the buffer) */
        push esi
        push edi
        mov edx, [esp+28]
        FILLBUF
        mov dword ptr [edx+20], 0
        mov edi, edx
        or ecx, -1
        xor eax, eax
        repne scasb
        not ecx
        dec ecx
        mov [edx+24], ecx
        pushfd
        pop dword ptr [edx+28]
        pop edi
        pop esi
        ret

        FN t_scas_bounded           /* c = count, d = byte to find */
        push esi
        push edi
        mov edx, [esp+28]
        FILLBUF
        mov edi, edx
        mov ecx, [esp+20]
        mov eax, [esp+24]
        push 0x202
        popfd
        repne scasb
        pushfd
        pop dword ptr [edx+28]
        mov esi, edx
        STRREGS
        pop edi
        pop esi
        ret

        FN t_memcmp                 /* compare (a,b) with (c,d), 8 bytes, repe cmpsb */
        push esi
        push edi
        mov edx, [esp+28]
        mov eax, [esp+12]
        mov [edx], eax
        mov eax, [esp+16]
        mov [edx+4], eax
        mov eax, [esp+20]
        mov [edx+8], eax
        mov eax, [esp+24]
        mov [edx+12], eax
        lea esi, [edx]
        lea edi, [edx+8]
        mov ecx, 8
        push 0x202
        popfd
        repe cmpsb
        pushfd
        pop dword ptr [edx+28]
        seta al
        setb ah
        movzx eax, ax
        mov [edx+20], eax
        STRREGS
        lea esi, [edx]
        lea edi, [edx+8]
        mov ecx, 2
        repe cmpsd
        setne al
        movzx eax, al
        shl ecx, 8
        or eax, ecx
        mov [edx+16], eax
        pop edi
        pop esi
        ret

/* -------------------------------------------------------------------- misc */
        FN t_extend                 /* movsx / movzx / bswap / lea / xchg */
        push ebx
        mov edx, [esp+24]
        mov ebx, [esp+8]
        movsx eax, bl
        mov [edx], eax
        movsx eax, bh
        mov [edx+4], eax
        movsx eax, bx
        mov [edx+8], eax
        movzx eax, bh
        movzx ecx, bx
        lea eax, [eax + ecx*8 + 0x1234]
        mov [edx+12], eax
        mov eax, ebx
        bswap eax
        mov [edx+16], eax
        mov eax, [esp+8]
        mov ecx, [esp+12]
        xchg eax, ecx
        xchg al, ch
        xchg [edx+16], ecx
        mov [edx+20], eax
        mov [edx+24], ecx
        mov eax, 0x11223344
        movsx ax, bl
        mov [edx+28], eax
        pop ebx
        ret

        FN t_bits                   /* a = value, b = bit index */
        push ebx
        mov edx, [esp+24]
        mov eax, [esp+8]
        mov ecx, [esp+12]
        xor ebx, ebx
        bt eax, ecx
        adc ebx, ebx
        bts eax, ecx
        adc ebx, ebx
        mov [edx], eax
        btr eax, 3
        adc ebx, ebx
        btc eax, 31
        adc ebx, ebx
        mov [edx+4], eax
        mov [edx+8], ebx
        /* bit-string addressing: index may select a neighbouring dword */
        mov eax, [esp+8]
        mov [edx+12], eax
        mov [edx+16], eax
        mov [edx+20], eax
        and ecx, 63
        sub ecx, 32
        xor ebx, ebx
        bt dword ptr [edx+16], ecx
        adc ebx, ebx
        bts dword ptr [edx+16], ecx
        adc ebx, ebx
        mov [edx+24], ebx
        mov eax, 0xAAAAAAAA
        bsf eax, dword ptr [esp+8]
        setz bl
        mov ecx, 0xBBBBBBBB
        bsr ecx, dword ptr [esp+8]
        setz bh
        shl eax, 8
        xor eax, ecx
        xor eax, ebx
        mov [edx+28], eax
        pop ebx
        ret

        FN t_xadd_cmpxchg
        mov edx, OUT
        mov eax, A
        mov ecx, B
        xadd eax, ecx
        mov [edx], eax
        mov [edx+4], ecx
        pushfd
        pop dword ptr [edx+8]
        mov eax, A
        mov [edx+12], eax
        mov eax, C
        mov ecx, B
        lock cmpxchg [edx+12], ecx
        mov [edx+16], eax
        pushfd
        pop dword ptr [edx+20]
        mov eax, A
        mov ecx, B
        lock xadd [edx+12], ecx
        mov [edx+24], ecx
        ret

        FN t_wide_arith             /* 64-bit add/sub/neg/shift from 32-bit pieces: (b:a) op (d:c) */
        mov ecx, OUT
        mov eax, A
        mov edx, B
        add eax, C
        adc edx, D
        mov [ecx], eax
        mov [ecx+4], edx
        mov eax, A
        mov edx, B
        sub eax, C
        sbb edx, D
        mov [ecx+8], eax
        mov [ecx+12], edx
        mov eax, A
        mov edx, B
        neg eax
        adc edx, 0
        neg edx
        mov [ecx+16], eax
        mov [ecx+20], edx
        mov eax, A
        cmp eax, C
        sbb eax, eax
        mov [ecx+24], eax
        mov eax, A
        mov edx, B
        shld edx, eax, 9
        shl eax, 9
        xor eax, edx
        mov [ecx+28], eax
        ret

        FN t_stack                  /* push/pop corner cases, pushad/popad, leave */
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        mov edx, [ebp+24]
        mov ecx, esp
        push esp                   /* pushes the value before the decrement */
        pop eax
        sub eax, ecx
        mov [edx], eax
        push dword ptr [ebp+8]
        push dword ptr [ebp+12]
        pop dword ptr [esp]        /* address computed after the increment */
        pop eax
        mov [edx+4], eax
        mov eax, [ebp+8]
        mov ebx, [ebp+12]
        mov esi, 0x51515151
        mov edi, 0xD1D1D1D1
        pushad
        mov eax, [esp+28]
        add eax, [esp+16]          /* saved eax + saved ebx */
        mov [edx+8], eax
        mov eax, [esp+12]          /* saved esp */
        sub eax, esp
        mov [edx+12], eax
        mov dword ptr [esp+4], 0x12121212  /* saved esi */
        xor ebx, ebx
        popad
        mov [edx+16], esi
        mov [edx+20], ebx
        push word ptr [ebp+8]
        mov eax, ecx
        sub eax, esp
        pop cx
        movzx ecx, cx
        shl eax, 16
        or eax, ecx
        mov [edx+24], eax
        mov eax, [ebp+8]
        push eax
        xchg [esp], edx
        xchg [esp], edx
        pop eax
        mov [edx+28], eax
        lea esp, [ebp-12]
        pop edi
        pop esi
        pop ebx
        leave
        ret

/* ------------------------------------------------------------ control flow */
        FN h_stdcall2               /* stdcall: x*3 + y */
        mov eax, [esp+4]
        lea eax, [eax + eax*2]
        add eax, [esp+8]
        ret 8

        FN h_cdecl1                 /* cdecl: x ^ 0x5A5A5A5A */
        mov eax, [esp+4]
        xor eax, 0x5A5A5A5A
        ret

        FN h_fact                   /* cdecl recursive: n! (mod 2^32) */
        mov eax, [esp+4]
        cmp eax, 1
        ja 1f
        mov eax, 1
        ret
1:      dec eax
        push eax
        call h_fact
        add esp, 4
        imul eax, dword ptr [esp+4]
        ret

        FN h_tail                   /* tail-jumps into h_cdecl1 */
        add dword ptr [esp+4], 7
        jmp h_cdecl1

/* Jump tables as the C run-time's memcpy has them: one whose slot 0 is never
 * used and overlaps the bytes of the preceding instruction, and one that is
 * indexed with -4..-1 from the address just past its end. */
        FN t_switch3
        mov edx, OUT
        mov eax, A
        and eax, 3
        mov ecx, B
        and ecx, 3
        sub ecx, 4
        test eax, eax
        jz 5f
        jmp dword ptr [eax*4 + 6f - 4]
5:      jmp dword ptr [ecx*4 + 7f]
        .p2align 2
6:      .long 1f, 2f, 3f
        .long 4f, 3f, 2f, 1f
7:
1:      mov dword ptr [edx], 0x11
        ret
2:      mov dword ptr [edx], 0x22
        ret
3:      mov dword ptr [edx], 0x33
        ret
4:      mov dword ptr [edx], 0x44
        ret

/* Non-local control flow, shaped like the transfer into a C++ catch block: a deep
 * callee restores the stack and frame pointers of an outer activation and jumps
 * to a continuation label inside it, which then returns to its own caller.
 * h_nl_level recurses through one call site, so every activation between the
 * thrower and the catching one is a stale frame with the same return address.
 *   b bits 0..2: recursion depth n     b bits 4..6: level that catches (none if > n) */
        FN t_nonlocal
        push ebp
        mov ebp, esp
        sub esp, 8                  /* [ebp-8], [ebp-4]: esp and ebp of the catching activation */
        push ebx
        push esi
        push edi
        lea ebx, [ebp-8]
        mov dword ptr [ebx], 0
        mov esi, [ebp+8]
        mov edi, [ebp+12]
        mov edx, edi
        shr edx, 4
        and edx, 7
        and edi, 7
        call h_nl_level
        mov edx, [ebp+24]
        mov [edx], esi
        mov [edx+4], eax
        pop edi
        pop esi
        pop ebx
        leave
        ret

        FN h_nl_level               /* edi = this level, edx = catching level, esi = accumulator */
        push ebp
        mov ebp, esp
        push edi
        cmp edi, edx
        jne 1f
        mov [ebx], esp
        mov [ebx+4], ebp
1:      test edi, edi
        jz 2f
        dec edi
        call h_nl_level
        jmp 3f
2:      call h_nl_throw
3:      mov edi, [ebp-4]            /* the call returned normally */
        lea esi, [esi*2+edi+1]
        .globl h_nl_cont
h_nl_cont:                          /* also the catch continuation of the catching level */
        mov edi, [ebp-4]
        rol esi, 5
        xor esi, edi
        mov eax, edi
        pop edi
        pop ebp
        ret

        FN h_nl_throw
        cmp dword ptr [ebx], 0
        je 1f
        mov eax, offset h_nl_cont
        mov esp, [ebx]
        mov ebp, [ebx+4]
        jmp eax
1:      ret

        FN t_calls
        push ebx
        mov ebx, [esp+24]
        push dword ptr [esp+12]
        push dword ptr [esp+12]
        call h_stdcall2
        mov [ebx], eax
        push dword ptr [esp+8]
        mov ecx, offset h_cdecl1
        call ecx
        add esp, 4
        mov [ebx+4], eax
        mov dword ptr [ebx+8], offset h_stdcall2
        push 5
        push dword ptr [esp+16]
        call dword ptr [ebx+8]
        mov [ebx+8], eax
        mov eax, [esp+8]
        and eax, 15
        push eax
        call h_fact
        pop ecx
        mov [ebx+12], eax
        push dword ptr [esp+12]
        call h_tail
        pop ecx
        mov [ebx+16], eax
        mov eax, esp
        sub eax, ebx
        mov ecx, esp
        call .Lgetpc               /* call/pop get-pc idiom */
.Lgetpc:
        pop eax
        sub eax, offset .Lgetpc     /* a named label: LLVM's assembler has no "offset 1b" */
        mov [ebx+20], eax
        sub ecx, esp
        mov [ebx+24], ecx
        pop ebx
        ret

        FN t_switch                 /* dense table */
        mov eax, A
        mov edx, OUT
        cmp eax, 5
        ja 9f
        jmp dword ptr [eax*4 + swtab1]
1:      mov dword ptr [edx], 0x100
        ret
2:      mov dword ptr [edx], 0x211
        ret
3:      mov dword ptr [edx], 0x322
        jmp 8f
4:      mov dword ptr [edx], 0x433
8:      add dword ptr [edx], 0x1000
        ret
9:      mov dword ptr [edx], 0xDEF
        ret
        .p2align 2
swtab1: .long 1b, 2b, 3b, 4b, 2b, 1b

        FN t_switch2                /* two-level table: byte index, then dword targets */
        mov eax, A
        mov edx, OUT
        sub eax, 10
        cmp eax, 9
        ja 9f
        movzx eax, byte ptr [eax + swidx2]
        jmp dword ptr [eax*4 + swtab2]
1:      mov dword ptr [edx], 0xA1
        ret
2:      mov dword ptr [edx], 0xB2
        ret
3:      mov dword ptr [edx], 0xC3
        ret
9:      mov dword ptr [edx], 0xDD
        ret
        .p2align 2
swtab2: .long 1b, 2b, 3b, 9b
swidx2: .byte 0, 1, 3, 3, 2, 2, 0, 3, 1, 2

        FN t_loops                  /* loop, jecxz, a counted jcc loop */
        mov ecx, A
        and ecx, 31
        mov edx, OUT
        xor eax, eax
        jecxz 2f
1:      lea eax, [eax + ecx*2 + 1]
        loop 1b
2:      mov [edx], eax
        mov ecx, A
        and ecx, 7
        xor eax, eax
3:      add eax, ecx
        dec ecx
        jns 3b
        mov [edx+4], eax
        ret

/* --------------------------------------------------------------------- x87
 * Doubles are passed by value as (lo, hi) pairs: x = (a, b), y = (c, d). */
        .macro CW53
        push 0x27F
        fldcw word ptr [esp]
        pop eax
        .endm

        FN t_fist                   /* x = (a,b), c = control word */
        mov edx, OUT
        fldcw word ptr C
        fld qword ptr A
        fistp dword ptr [edx]
        fld qword ptr A
        fistp word ptr [edx+4]
        fld qword ptr A
        fistp qword ptr [edx+8]
        fld qword ptr A
        frndint
        fstp qword ptr [edx+16]
        fld qword ptr A
        fist dword ptr [edx+24]
        fstp st(0)
        fnstcw word ptr [edx+28]
        CW53
        ret

        FN t_farith_mem             /* x op y with memory operands */
        mov edx, OUT
        CW53
        fld qword ptr A
        fadd qword ptr C
        fstp qword ptr [edx]
        fld qword ptr A
        fsub qword ptr C
        fstp qword ptr [edx+8]
        fld qword ptr A
        fmul qword ptr C
        fstp qword ptr [edx+16]
        fld qword ptr A
        fdiv qword ptr C
        fstp qword ptr [edx+24]
        ret

        FN t_farith_memr            /* reversed memory forms */
        mov edx, OUT
        CW53
        fld qword ptr A
        fsubr qword ptr C
        fstp qword ptr [edx]
        fld qword ptr A
        fdivr qword ptr C
        fstp qword ptr [edx+8]
        fld qword ptr A
        fstp dword ptr [edx+16]    /* round to float */
        fld dword ptr [edx+16]
        fmul dword ptr [edx+16]
        fstp qword ptr [edx+24]
        fild dword ptr A
        fiadd dword ptr C
        fimul word ptr A
        fistp dword ptr [edx+20]
        ret

        .macro LOADXY               /* st0 = y, st1 = x */
        fld qword ptr A
        fld qword ptr C
        .endm

        FN t_farith_pop             /* DE xx: st1 = st1 op st0, pop */
        mov edx, OUT
        CW53
        LOADXY
        .byte 0xDE, 0xE9           /* fsubp st(1), st   : x - y */
        fstp qword ptr [edx]
        LOADXY
        .byte 0xDE, 0xE1           /* fsubrp st(1), st  : y - x */
        fstp qword ptr [edx+8]
        LOADXY
        .byte 0xDE, 0xF9           /* fdivp st(1), st   : x / y */
        fstp qword ptr [edx+16]
        LOADXY
        .byte 0xDE, 0xF1           /* fdivrp st(1), st  : y / x */
        fstp qword ptr [edx+24]
        ret

        FN t_farith_st0             /* D8 xx: st0 = st0 op st1 */
        mov edx, OUT
        CW53
        LOADXY
        .byte 0xD8, 0xE1           /* fsub st, st(1)    : y - x */
        fstp qword ptr [edx]
        fstp st(0)
        LOADXY
        .byte 0xD8, 0xE9           /* fsubr st, st(1)   : x - y */
        fstp qword ptr [edx+8]
        fstp st(0)
        LOADXY
        .byte 0xD8, 0xF1           /* fdiv st, st(1)    : y / x */
        fstp qword ptr [edx+16]
        fstp st(0)
        LOADXY
        .byte 0xD8, 0xF9           /* fdivr st, st(1)   : x / y */
        fstp qword ptr [edx+24]
        fstp st(0)
        ret

        FN t_farith_sti             /* DC xx: st1 = st1 op st0, no pop */
        mov edx, OUT
        CW53
        LOADXY
        .byte 0xDC, 0xE9           /* fsub st(1), st    : x - y */
        fstp st(0)
        fstp qword ptr [edx]
        LOADXY
        .byte 0xDC, 0xE1           /* fsubr st(1), st   : y - x */
        fstp st(0)
        fstp qword ptr [edx+8]
        LOADXY
        .byte 0xDC, 0xF9           /* fdiv st(1), st    : x / y */
        fstp st(0)
        fstp qword ptr [edx+16]
        LOADXY
        .byte 0xDC, 0xF1           /* fdivr st(1), st   : y / x */
        fstp st(0)
        fstp qword ptr [edx+24]
        ret

        FN t_fmisc                  /* fchs fabs fsqrt fxch constants, tbyte round trip */
        mov edx, OUT
        CW53
        fld qword ptr A
        fchs
        fld qword ptr C
        fabs
        fsqrt
        fxch st(1)
        .byte 0xDE, 0xC1           /* faddp st(1), st */
        fstp qword ptr [edx]
        fld1
        fldpi
        .byte 0xDE, 0xC9           /* fmulp st(1), st */
        fldz
        .byte 0xDE, 0xC1           /* faddp */
        fmul qword ptr A
        fstp qword ptr [edx+8]
        fld qword ptr A
        fstp tbyte ptr [edx+16]
        fld tbyte ptr [edx+16]
        fadd st(0), st(0)
        movzx eax, word ptr [edx+24]
        mov [edx+28], eax
        fstp qword ptr [edx+20]
        ret

        FN t_fcom                   /* compare x with y every common way */
        push ebx
        mov edx, [esp+24]
        fld qword ptr [esp+16]     /* y */
        fld qword ptr [esp+8]      /* x */
        fcompp
        fnstsw ax
        mov [edx], eax
        sahf
        seta bl
        setb bh
        sete cl
        setp ch
        shl ebx, 16
        mov bx, cx
        mov [edx+4], ebx
        fld qword ptr [esp+8]
        fcomp qword ptr [esp+16]
        fnstsw ax
        test ah, 0x41
        setz al
        movzx eax, al
        mov [edx+8], eax
        fld qword ptr [esp+8]
        fcom qword ptr [esp+16]
        fnstsw word ptr [edx+12]
        ftst
        fnstsw ax
        mov [edx+16], eax
        fxam
        fnstsw ax
        mov [edx+20], eax
        fld qword ptr [esp+16]
        fucompp
        fnstsw ax
        test ah, 5
        setp al
        movzx eax, al
        mov [edx+24], eax
        pop ebx
        ret

        FN t_fprem                  /* x fprem y, x fprem1 y */
        mov edx, OUT
        CW53
        fld qword ptr C
        fld qword ptr A
        fprem
        fnstsw ax
        mov [edx+24], eax
        fstp qword ptr [edx]
        fstp st(0)
        fld qword ptr C
        fld qword ptr A
        fprem1
        fnstsw ax
        mov [edx+28], eax
        fstp qword ptr [edx+8]
        fstp st(0)
        ret

        FN t_fscale                 /* x * 2^c */
        mov edx, OUT
        CW53
        fild dword ptr C
        fld qword ptr A
        fscale
        fstp qword ptr [edx]
        fstp st(0)
        ret

        FN t_fint                   /* integer loads/stores of every width; (b:a) is an int64 */
        mov edx, OUT
        CW53
        fild word ptr A
        fild dword ptr A
        .byte 0xDE, 0xC9           /* fmulp */
        fstp qword ptr [edx]
        fild qword ptr A
        fidiv dword ptr C
        fstp qword ptr [edx+8]
        fild dword ptr A
        fisub word ptr C
        fistp dword ptr [edx+16]
        fild dword ptr A
        ficom dword ptr C
        fnstsw ax
        fstp st(0)
        mov [edx+20], eax
        fild qword ptr A
        fistp qword ptr [edx+24]
        ret
