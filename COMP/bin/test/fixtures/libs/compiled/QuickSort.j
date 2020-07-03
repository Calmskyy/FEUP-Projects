.class public QuickSort
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 99
.limit stack 99
bipush 10
newarray int
astore 1
bipush 0
istore 2
while_0:
iload 2
aload 1
arraylength
if_icmpge endwhile_0
aload 1
bipush i
iload 2
isub
iastore
iload 2
bipush 1
iadd
istore 2
goto while_0
endwhile_0:
new QuickSort
dup
invokespecial QuickSort/<init>()V
astore 3
aload 3
aload 1
invokevirtual QuickSort/quicksort([I[III)ZZ
aload 3
aload 1
invokevirtual QuickSort/printL([I)Z
return
.end method
.method public printL([I)Z
.limit stack 99
.limit stack 99
bipush 0
istore 2
while_0:
iload 2
aload 1
arraylength
if_icmpge endwhile_0
aload 1
bipush i
iaload
invokestatic io/println(I)V
iload 2
bipush 1
iadd
istore 2
goto while_0
endwhile_0:
aload 0
return
.end method
.method public quicksort([I)Z
.limit stack 99
.limit stack 99
aload 0
return
.end method
.method public quicksort([III)Z
.limit stack 99
.limit stack 99
iload 2
iload 3
if_icmpge else_0
aload 0
aload 0
aload 0
aload 0
invokevirtual /partition([III)
istore 4
aload 0
aload 0
aload 0
invokevirtual /quicksort([I[III)
aload 0
aload 0
aload 0
invokevirtual /quicksort([I[III)
goto endif_0
else_0:
endif_0:
aload 0
return
.end method
.method public partition([III)I
.limit stack 99
.limit stack 99
aload 1
bipush hi
iaload
istore 4
istore 5
istore 6
while_0:
iload 6
iload 3
if_icmpge endwhile_0
aload 1
bipush j
iaload
iload 4
if_icmpge else_0
aload 1
bipush i
iaload
istore 7
aload 1
bipush i
aload 1
bipush j
iaload
iastore
aload 1
bipush j
iastore
iload 5
bipush 1
iadd
istore 5
goto endif_0
else_0:
endif_0:
iload 6
bipush 1
iadd
istore 6
goto while_0
endwhile_0:
aload 1
bipush i
iaload
istore 7
aload 1
bipush i
aload 1
bipush hi
iaload
iastore
aload 1
bipush hi
iastore
iload 5
ireturn
.end method
