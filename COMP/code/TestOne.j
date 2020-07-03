.class public TestOne
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 0
.limit locals 4
bipush 10
istore 1
bipush 3
istore 2
iload 1
iload 2
iadd
istore 3
iload 3
invokestatic io/println(I)V
return
.end method
