.class public Simple
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public add(II)I
.limit stack 2
.limit locals 4
iload 1
iload 2
iadd
istore 3
iload 3
ireturn
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 0
.limit locals 5
bipush 10
istore 1
bipush 20
istore 2
new Simple
dup
invokespecial Simple/<init>()V
astore 4
aload 4
iload 1
iload 2
invokevirtual Simple/add(II)I
istore 3
iload 3
invokestatic io/println(I)V
return
.end method
