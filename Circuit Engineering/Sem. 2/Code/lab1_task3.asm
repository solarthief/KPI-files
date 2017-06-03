equ D: 3h \x1
accept rq: 0fffbh \x2
accept r6: 4h \x3
accept r10: 0fffeh \x4

\k1 = 24;
\k2 = 14;
\k3 = 13;
\k4 = 8;
\y = 13x1 - 8x2 - 14x3 + 24x4

{add sla, r0, r10; }

{add r0, D; }
{sub r0, rq, nz; }
{sub r0, r6, nz; }
{add sla, r0, r10; }

{add r0, D; }
{sub sla, r0, r6, nz; }

{sub sla, r0, r6, nz; }

{add r0, D; }
