macro mov reg1,reg2:{or reg1,z,reg2;}
link l1:ct
accept r0: 076E0h \1st argument
accept r15:0AA6h \2nd argument
accept r1:0h \mantis sign
accept r2:0h \mantis order
accept r6:0h \Z
accept r8:0h \result

\mantis sign
{and r1,r0,8000h;}
{and rq,r15,8000h;}
{xor r1,r1,rq;}

\get order
{and r2,r0,7F00h;}
{and rq,r15,7F00h;}
{add r2,r2,rq;}

\multiplication
{and r5,r0,00FFh;}\R5 - X
{and rq,r15,00FFh;}\RQ - Y
{push nz,7;}
{or sll,rq,0;}
{rfct;}
{push nz,6;}
{cjp not co, label1;}
{add r6,r6,r5,z;}
label1 {or sll, r6, 0;}
{or sll, rq, 0;}
{rfct;}
{cjp not co,label2;}
{add r6,r6,r5,z;}
label2{or sll, rq, 0;}
\normalization
{mov rq,r6;}
{cjp no,label3;}
{or sll,rq,0;}
{sub r2,r2,0;}
label3{and r2,r2,7F00h;}
{push nz,7;}
{or srl,rq,0;}
{rfct;}


\finalize
{mov r8,rq;}
{or r8,r1;}
{or r8,r2;}
