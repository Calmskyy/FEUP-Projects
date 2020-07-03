.class public WhileAndIF
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 11
.limit locals 5
bipush 20
istore 1
bipush 10
istore 2
bipush 10
newarray int
astore 4
iload 1
iload 2
if_icmpge else_0
iload 1
bipush 1
isub
istore 3
goto endif_0
else_0:
iload 2
bipush 1
isub
istore 3
endif_0:
while_1:
bipush 0
bipush 1
isub
iload 3
if_icmpge endwhile_1
aload 4
bipush c
iload 1
iload 2
isub
iastore
iload 3
bipush 1
isub
istore 3
iload 1
bipush 1
isub
istore 1
iload 2
bipush 1
isub
istore 2
goto while_1
endwhile_1:
bipush 0
istore 3
while_2:
iload 3
aload 4
arraylength
if_icmpge endwhile_2
aload 4
bipush c
iaload
invokestatic io/println(I)V
iload 3
bipush 1
iadd
istore 3
goto while_2
endwhile_2:
return
.end method
