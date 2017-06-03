accept r0: 26h \38
accept r1: 13h \19
accept r3: 7fh \127
accept r4: 1ah \26
accept r7: 3eh \62
accept r8: 2dh \45
accept r10: 1a7h \423
accept r14: 7b6h \1974
accept rq: 1d5h \469
equ D: 45ch \1116

\1)
{add r11, r10, rq; }
{add r11, 1h; } \R11:= R10 + PrQ + 1 [37dh]

\2)
{add r6, r14, D; } \R6:= R14 + D [c12h]

\3)
{sub r13, r7, D, nz; }
{sub sla, r13, 1, nz; } \R13:= 2 (R7 - D - 1) [f7c2h]

\4)
{sub sra, r0, r4, nz; } \R0:= (R0 - R4)/2 [6h]

\5)
{sub sla, r3, r1, r3; } \ R3:= 2(R1 - R3) [ff28h]

\6)
{sub r9, r8, rq, nz; }
{sub sra, r9, 1, nz; } \ R9:= (R8 - PrQ - 1) / 2 [ff2c]
