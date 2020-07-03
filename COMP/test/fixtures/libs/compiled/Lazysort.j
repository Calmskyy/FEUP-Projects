.class public Lazysort
.super Quicksort
.method <init>()V
aload_0
invokenonvirtual Quicksort/<init>()V
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
new Lazysort
dup
invokespecial Lazysort/<init>()V
astore 4
aload 4
aload 1
invokevirtual Lazysort/quicksort([I)Z
aload 4
aload 1
invokevirtual Lazysort/printL()
astore 3
return
.end method
.method public quicksort([I)Z
.limit stack 99
.limit stack 99
aload 0
bipush 0
bipush 5
invokevirtual /random()
; something is missing here
if_icmpge else_0
aload 0
aload 0
invokevirtual /beLazy([I)
bipush true
astore 2
goto endif_0
else_0:
bipush false
astore 2
endif_0:
astore 2
goto endif_1
else_1:
aload 0
aload 0
bipush 0
invokevirtual /quicksort([I)
astore 2
endif_1:
aload 2
return
.end method
.method public beLazy([I)Z
.limit stack 99
.limit stack 99
aload 1
arraylength
istore 2
bipush 0
istore 3
while_0:
iload 3
iload 2
bipush 2
idiv
if_icmpge endwhile_0
aload 1
bipush $allowedNameI
aload 0
bipush 0
bipush 10
invokevirtual /random()
iastore
iload 3
bipush 1
iadd
istore 3
goto while_0
endwhile_0:
while_1:
iload 3
iload 2
if_icmpge endwhile_1
aload 1
bipush $allowedNameI
bipush 1
iadd
iastore
iload 3
bipush 1
iadd
istore 3
goto while_1
endwhile_1:
aload 0
return
.end method
