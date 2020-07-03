.class public FindMaximum
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public find_maximum([I)I
.limit stack 9
.limit locals 5
bipush 1
istore 2
aload 1
bipush 0
iaload
istore 3
while_0:
iload 2
aload 1
arraylength
if_icmpge endwhile_0
aload 1
bipush i
iaload
istore 4
iload 3
iload 4
if_icmpge else_0
istore 3
goto endif_0
else_0:
endif_0:
iload 2
bipush 1
iadd
istore 2
goto while_0
endwhile_0:
iload 3
ireturn
.end method
.method public build_test_arr()I
.limit stack 7
.limit locals 1
bipush 5
newarray int
astore 0
aload 0
bipush 0
bipush 14
iastore
aload 0
bipush 1
bipush 28
iastore
aload 0
bipush 2
bipush 0
iastore
aload 0
bipush 3
bipush 0
bipush 5
isub
iastore
aload 0
bipush 4
bipush 12
iastore
aload 0
return
.end method
.method public get_array()[I
.limit stack 1
.limit locals 1
aload 0
return
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 0
.limit locals 2
new FindMaximum
dup
invokespecial FindMaximum/<init>()V
astore 1
aload 1
invokevirtual FindMaximum/build_test_arr()I
aload 0
invokevirtual /printResult()
return
.end method
