.class public MonteCarloPi
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public performSingleEstimate()Z
.limit stack 2
.limit locals 5
aload 0
bipush 100
invokevirtual /random()
istore 1
aload 0
bipush 100
invokevirtual /random()
istore 2
bipush 100
idiv
istore 4
iload 4
; something is missing here
if_icmpge else_0
bipush true
astore 3
goto endif_0
else_0:
bipush false
astore 3
endif_0:
aload 3
return
.end method
.method public estimatePi100(I)I
.limit stack 2
.limit locals 5
bipush 0
istore 3
bipush 0
istore 2
while_0:
iload 3
iload 1
if_icmpge endwhile_0
iload 2
bipush 1
iadd
istore 2
goto endif_0
else_0:
endif_0:
iload 3
bipush 1
iadd
istore 3
goto while_0
endwhile_0:
bipush 400
imul
istore 4
iload 4
ireturn
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 1
.limit locals 3
aload 0
invokevirtual /requestNumber()
istore 2
aload 0
iload 2
invokevirtual /estimatePi100(I)
istore 1
aload 0
iload 1
invokevirtual /printResult()
return
.end method
