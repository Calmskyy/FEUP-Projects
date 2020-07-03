.class public TestTwo
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 2
.limit locals 3
bipush 10
istore 1
bipush 20
istore 2
while_0:
iload 1
iload 2
if_icmpge endwhile_0
iload 1
bipush 1
iadd
istore 1
goto while_0
endwhile_0:
iload 1
invokestatic io/println(I)V
return
.end method
