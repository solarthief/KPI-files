macro mov reg1,reg2:{or reg1,z,reg2;}
accept poh: 10h,21h,4fh,5dh,61h,70h,82h,9fh,0a2h,0b5h,0c6h,0a8h,20h,92h,0d5h,80h
link l1:z
link l3:z

\R2=(R3-1)/2
{mov r2,r3;}
{sub srl,r2,z;}
\R4=R3&R2
{mov r4,r3;}
{and r4,r2;}
\loop count
{push nz,3;}
\R5=2(R4+1)
{mov r5,r4;}
{add sll,r5,z,nz;}
\goto mpp
{cjs not l3,mpp;}
{rfct;}
\loop end
\R12=(R8-R5-1)/2
{mov r12,r8;}
{sub srl,r12,r12,r5,z;}
{cjp nz,END;}
org 100h
mpp {mov r6,r5;}
{add r6,r6,r7,z;}\R6=R5+R7
{cjp not l1,label1;}
\R7=(R8-1)/2
{mov r7,r8;}
{sub srl,r7,z;}
label1 {mov r5,r7;}
{sub sll,r5,z;crtn nz;}\R5=2*(R7-1)
END{}
