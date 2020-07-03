.class public TestThree
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 14
.limit locals 2
bipush 2
newarray int
astore 1
aload 1
bipush 0
bipush 10
iastore
aload 1
bipush 1
bipush 20
iastore
aload 1
bipush 1
iaload
aload 1
bipush 0
iaload
if_icmpge else_0
aload 1
bipush 0
iaload
invokestatic io/println(I)V
goto endif_0
else_0:
aload 1
bipush 1
iaload
invokestatic io/println(I)V
endif_0:
return
.end method
