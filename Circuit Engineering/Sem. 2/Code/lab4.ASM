macro mov reg1,reg2:{or reg1,z,reg2;}

accept r8:0bh
link l1:ct
link l2:rdm
link ewh:16
link m:7,6,5,4,3,2,1,0,z,z,z,z
dw 0h:100h
dw 100h:0c130h
dw 101h:0a144h
dw 102h:0a134h
dw 103h:0ff00h
dw 0bh:0105h
dw 04h:82C0h
dw 03h:006Fh
accept rdm_delay:2

\SUBROUT1
s1 {xor r1,r1;oey;ewh;}
   {or nil,r1,z;oey;ewl;}
   {xor r6,r6;}
p1 {cjp rdm,P1;r;or r6,bus_d,z;}\R6=PC
   {or nil,r6,z;oey;ewl;}
   {xor r4,r4;}
p2 {cjp rdm,P2; r; or r4,bus_d,z;}\R4=asm command
   {xor r2,r2;}
   {or r2,r4,Z;}
   {push nz,7;}
   {rfct; or sr.0,r2,r2,z;}
   {xor r5,r5;}
   {or r5,r4;}
   {and r4,000fh;}
   {and r5,00f0h;}
   {push nz,3;}
   {rfct;or sr.0,r5,z;}
   {or nil,r4,z;oey;ewl;}
   {xor r10,r10;}
p3 {cjp rdm,P3;r;or r10,bus_d,z;}\R10=REGy
   {or nil,r5,z;oey;ewl;}
   {xor r11,r11;}
p4 {cjp rdm,P4;r;or r11,bus_d,z;}\R11=REGx
{jmap;or nil,r2,z;oey;}

\SUBROUT2
s2 {or nil,r8,z;oey;ewl;}
   {xor r12,r12;}
p5 {cjp rdm,p5;r;or r12,bus_d,z;}
   {cjp rn_v,d1;}
   {and r12,0fbffh;}
   {cjp nz,j1;}
d1 {or r12,0400h;}
j1 {cjp rn_c,d2;}
   {and r12,0fffeh;}
   {cjp nz,j2;}
d2 {or r12,0001h;}
j2 {cjp rn_n,d3;}
   {and r12,0feffh;}
   {cjp nz,j3;}
d3 {or r12,0100h;}
j3 {load rm,flags;and nil,r15,00ffh;}
   {cjp rm_z,d4;}
   {and r12,0ffbfh;}
   {cjp nz,j4;}
d4 {or r12,0040h;}
j4 {or nil,r8,z;oey;ewl;}
rr1 {cjp rdm,rr1;w;or nil,r12,z;oey;}
    {or nil,r5,z;oey;ewl;}
rr2 {cjp rdm,rr2;w;or nil,r15,z;oey;}
    {add r6,1;}\rc=rc+1
    {or nil,r1,z;oey;ewl;}
rr3 {cjp rdm,rr3;w;or nil,r6,z;oey;}
{cjp nz,s1;}

\MCFINISH
org 0ff0h
{cjp nz,END;}

\MCCONV
org 0c10h
{mov r15,r11;}
{and r15,8000h;}
{xor r2,r2;}
{mov r3,r11;}
{and r3,7fffh;}
{push nz,15;}
{add r2,1;}
{load rn,flags;and nil,r3,0001h;}
{cjp rn_z,ne1;}
{mov r7,r2;}
ne1{and sra,r3,r3;}
{rfct;}
{push nz,7;}
{and sla,r7,0ffffh;}
{rfct;}
{or r15,r7;}
{mov r7,r11;}
{and r7,7fffh;}
{load rn,flags;and nil,r7,0ff00h;}
{cjp rn_z,norm;}
{push nz,7;}
{and sra,r7,0ffffh;}
{rfct;}
norm{and r3,0;}
{load rn,flags;and nil,r7,0080h;}
{cjp not rn_z,final1;}
re1{and sla,r7,0ffffh;}
{add r3,1;}
{load rn,flags;and nil,r7,0080h;}
{cjp rn_z,re1;}
final1{load rn,flags;or r15,r7;}
{cjp nz,s2;}

\MCMULF
org 0a10h
\mantis`s sign
{and r15,r11,8000h;}
{and rq,r10,8000h;}
{xor r15,r15,rq;}
\get order
{and r14,r11,7F00h;}
{and rq,r10,7F00h;}
{add r14,r14,rq;}
\multiplication
{and r13,r11,00FFh;}
{and rq,r10,00FFh;}
{xor r9,r9;}
{push nz,7;}
{or sll,rq,0;}
{rfct;}
{push nz,6;}
{cjp not co, label1;}
{add r9,r9,r13,z;}
label1 {or sll, r9, 0;}
{or sll, rq, 0;}
{rfct;}
{cjp not co,label2;}
{add r9,r9,r13,z;}
label2{or sll, rq, 0;}
\normalization
{mov rq,r9;}
{cjp no,label3;}
{or sll,rq,0;}
{sub r14,r14,0;}
label3{and r14,r14,7F00h;}
{push nz,7;}
{or srl,rq,0;}
{rfct;}
\finalize
{mov r4,rq;}
{or r4,r15;}
{or r4,r14;}
{load rn,flags;or r15,r4;}
MN_END{cjp nz,s2;}
\This is the end
END{}
