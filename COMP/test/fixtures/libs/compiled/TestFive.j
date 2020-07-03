.class public TestFive
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public mult(II)I
.limit stack 2
.limit locals 4
iload 1
iload 2
imul
istore 3
iload 3
ireturn
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 6
.limit locals 6
bipush 2
newarray int
astore 5
aload 5
bipush 0
bipush 5
iastore
aload 5
bipush 0
iaload
istore 1
aload 5
arraylength
istore 2
new TestFive
dup
invokespecial TestFive/<init>()V
astore 4
aload 4
iload 1
iload 2
invokevirtual TestFive/mult(II)I
istore 3
iload 3
invokestatic io/println(I)V
return
.end method
