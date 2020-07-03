.class public Life
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 99
.limit stack 99
new Life
dup
invokespecial Life/<init>()V
astore 1
aload 1
invokevirtual Life/init()Z
while_0:
aload 1
invokevirtual Life/printField()Z
aload 1
invokevirtual Life/update()Z
invokestatic io/println(I)V
istore 2
goto while_0
endwhile_0:
return
.end method
.method public init()Z
.limit stack 99
.limit stack 99
bipush 1
newarray int
astore 1
bipush 2
astore 0
bipush 3
astore 0
bipush 3
astore 0
bipush 225000
astore 0
aload 0
aload 1
invokevirtual /field([I)
astore 0
aload 1
bipush 0
iaload
istore 2
iload 2
bipush 1
isub
astore 0
idiv
astore 0
aload 0
return
.end method
.method public field([I)[I
.limit stack 99
.limit stack 99
bipush 100
newarray int
astore 2
aload 1
bipush 0
bipush 10
iastore
aload 2
bipush 0
bipush 0
iastore
aload 2
bipush 1
bipush 0
iastore
aload 2
bipush 2
bipush 1
iastore
aload 2
bipush 3
bipush 0
iastore
aload 2
bipush 4
bipush 0
iastore
aload 2
bipush 5
bipush 0
iastore
aload 2
bipush 6
bipush 0
iastore
aload 2
bipush 7
bipush 0
iastore
aload 2
bipush 8
bipush 0
iastore
aload 2
bipush 9
bipush 0
iastore
aload 2
bipush 10
bipush 1
iastore
aload 2
bipush 11
bipush 0
iastore
aload 2
bipush 12
bipush 1
iastore
aload 2
bipush 13
bipush 0
iastore
aload 2
bipush 14
bipush 0
iastore
aload 2
bipush 15
bipush 0
iastore
aload 2
bipush 16
bipush 0
iastore
aload 2
bipush 17
bipush 0
iastore
aload 2
bipush 18
bipush 0
iastore
aload 2
bipush 19
bipush 0
iastore
aload 2
bipush 20
bipush 0
iastore
aload 2
bipush 21
bipush 1
iastore
aload 2
bipush 22
bipush 1
iastore
aload 2
bipush 23
bipush 0
iastore
aload 2
bipush 24
bipush 0
iastore
aload 2
bipush 25
bipush 0
iastore
aload 2
bipush 26
bipush 0
iastore
aload 2
bipush 27
bipush 0
iastore
aload 2
bipush 28
bipush 0
iastore
aload 2
bipush 29
bipush 0
iastore
aload 2
bipush 30
bipush 0
iastore
aload 2
bipush 31
bipush 0
iastore
aload 2
bipush 32
bipush 0
iastore
aload 2
bipush 33
bipush 0
iastore
aload 2
bipush 34
bipush 0
iastore
aload 2
bipush 35
bipush 0
iastore
aload 2
bipush 36
bipush 0
iastore
aload 2
bipush 37
bipush 0
iastore
aload 2
bipush 38
bipush 0
iastore
aload 2
bipush 39
bipush 0
iastore
aload 2
bipush 40
bipush 0
iastore
aload 2
bipush 41
bipush 0
iastore
aload 2
bipush 42
bipush 0
iastore
aload 2
bipush 43
bipush 0
iastore
aload 2
bipush 44
bipush 0
iastore
aload 2
bipush 45
bipush 0
iastore
aload 2
bipush 46
bipush 0
iastore
aload 2
bipush 47
bipush 0
iastore
aload 2
bipush 48
bipush 0
iastore
aload 2
bipush 49
bipush 0
iastore
aload 2
bipush 50
bipush 0
iastore
aload 2
bipush 51
bipush 0
iastore
aload 2
bipush 52
bipush 0
iastore
aload 2
bipush 53
bipush 0
iastore
aload 2
bipush 54
bipush 0
iastore
aload 2
bipush 55
bipush 0
iastore
aload 2
bipush 56
bipush 0
iastore
aload 2
bipush 57
bipush 0
iastore
aload 2
bipush 58
bipush 0
iastore
aload 2
bipush 59
bipush 0
iastore
aload 2
bipush 60
bipush 0
iastore
aload 2
bipush 61
bipush 0
iastore
aload 2
bipush 62
bipush 0
iastore
aload 2
bipush 63
bipush 0
iastore
aload 2
bipush 64
bipush 0
iastore
aload 2
bipush 65
bipush 0
iastore
aload 2
bipush 66
bipush 0
iastore
aload 2
bipush 67
bipush 0
iastore
aload 2
bipush 68
bipush 0
iastore
aload 2
bipush 69
bipush 0
iastore
aload 2
bipush 70
bipush 0
iastore
aload 2
bipush 71
bipush 0
iastore
aload 2
bipush 72
bipush 0
iastore
aload 2
bipush 73
bipush 0
iastore
aload 2
bipush 74
bipush 0
iastore
aload 2
bipush 75
bipush 0
iastore
aload 2
bipush 76
bipush 0
iastore
aload 2
bipush 77
bipush 0
iastore
aload 2
bipush 78
bipush 0
iastore
aload 2
bipush 79
bipush 0
iastore
aload 2
bipush 80
bipush 0
iastore
aload 2
bipush 81
bipush 0
iastore
aload 2
bipush 82
bipush 0
iastore
aload 2
bipush 83
bipush 0
iastore
aload 2
bipush 84
bipush 0
iastore
aload 2
bipush 85
bipush 0
iastore
aload 2
bipush 86
bipush 0
iastore
aload 2
bipush 87
bipush 0
iastore
aload 2
bipush 88
bipush 0
iastore
aload 2
bipush 89
bipush 0
iastore
aload 2
bipush 90
bipush 0
iastore
aload 2
bipush 91
bipush 0
iastore
aload 2
bipush 92
bipush 0
iastore
aload 2
bipush 93
bipush 0
iastore
aload 2
bipush 94
bipush 0
iastore
aload 2
bipush 95
bipush 0
iastore
aload 2
bipush 96
bipush 0
iastore
aload 2
bipush 97
bipush 0
iastore
aload 2
bipush 98
bipush 0
iastore
aload 2
bipush 99
bipush 0
iastore
aload 2
return
.end method
.method public update()Z
.limit stack 99
.limit stack 99
bipush null
newarray int
astore 5
bipush 0
istore 1
while_0:
iload 1
aload 0
arraylength
if_icmpge endwhile_0
aload 0
bipush i
iaload
istore 2
aload 0
iload 1
invokevirtual /getLiveNeighborN(I)
istore 3
astore 4
aload 5
bipush i
bipush 0
iastore
goto endif_0
else_0:
aload 5
bipush i
aload 0
bipush i
iaload
iastore
endif_0:
goto endif_0
else_0:
aload 5
bipush i
bipush 1
iastore
goto endif_0
else_0:
aload 5
bipush i
aload 0
bipush i
iaload
iastore
endif_0:
endif_0:
iload 1
bipush 1
iadd
istore 1
goto while_0
endwhile_0:
astore 0
aload 0
return
.end method
.method public printField()Z
.limit stack 99
.limit stack 99
bipush 0
istore 1
bipush 0
istore 2
while_0:
iload 1
aload 0
arraylength
if_icmpge endwhile_0
invokestatic io/println(I)V
bipush 0
istore 2
goto endif_0
else_0:
endif_0:
aload 0
bipush i
iaload
invokestatic io/println(I)V
iload 1
bipush 1
iadd
istore 1
iload 2
bipush 1
iadd
istore 2
goto while_0
endwhile_0:
invokestatic io/println(I)V
invokestatic io/println(I)V
aload 0
return
.end method
.method public trIdx(II)I
.limit stack 99
.limit stack 99
aload 0
return
.end method
.method public cartIdx(I)[I
.limit stack 99
.limit stack 99
bipush 1
iadd
istore 4
iload 1
iload 4
idiv
istore 3
iload 1
isub
istore 2
bipush 2
newarray int
astore 5
aload 5
bipush 0
iastore
aload 5
bipush 1
iastore
aload 5
return
.end method
.method public getNeighborCoords(I)[I
.limit stack 99
.limit stack 99
aload 0
aload 0
invokevirtual /cartIdx(I)
astore 8
aload 8
bipush 0
iaload
istore 2
aload 8
bipush 1
iaload
istore 3
iload 2
aload 0
if_icmpge else_0
iload 2
bipush 1
iadd
istore 6
iload 2
bipush 1
isub
istore 4
goto endif_0
else_0:
istore 4
endif_0:
goto endif_0
else_0:
bipush 0
istore 6
iload 2
bipush 1
isub
istore 4
endif_0:
iload 3
aload 0
if_icmpge else_1
iload 3
bipush 1
iadd
istore 7
iload 3
bipush 1
isub
istore 5
goto endif_0
else_0:
istore 5
endif_0:
goto endif_1
else_1:
bipush 0
istore 7
iload 3
bipush 1
isub
istore 5
endif_1:
bipush 8
newarray int
astore 9
aload 9
bipush 0
aload 0
iload 1
iload 4
invokevirtual /trIdx(II)
iastore
aload 9
bipush 1
aload 0
iload 3
iload 4
invokevirtual /trIdx(II)
iastore
aload 9
bipush 2
aload 0
iload 3
iload 2
invokevirtual /trIdx(II)
iastore
aload 9
bipush 3
aload 0
iload 3
iload 6
invokevirtual /trIdx(II)
iastore
aload 9
bipush 4
aload 0
iload 1
iload 6
invokevirtual /trIdx(II)
iastore
aload 9
bipush 5
aload 0
iload 5
iload 6
invokevirtual /trIdx(II)
iastore
aload 9
bipush 6
aload 0
iload 5
iload 2
invokevirtual /trIdx(II)
iastore
aload 9
bipush 7
aload 0
iload 5
iload 4
invokevirtual /trIdx(II)
iastore
aload 9
return
.end method
.method public getLiveNeighborN(I)I
.limit stack 99
.limit stack 99
bipush 0
istore 4
aload 0
aload 0
invokevirtual /getNeighborCoords(I)
astore 2
bipush 0
istore 3
while_0:
iload 3
aload 2
arraylength
if_icmpge endwhile_0
iload 4
bipush 1
iadd
istore 4
goto endif_0
else_0:
endif_0:
iload 3
bipush 1
iadd
istore 3
goto while_0
endwhile_0:
iload 4
ireturn
.end method
.method public busyWait(I)Z
.limit stack 99
.limit stack 99
iload 1
imul
istore 3
bipush 0
istore 2
while_0:
iload 2
iload 3
if_icmpge endwhile_0
iload 2
bipush 1
iadd
istore 2
goto while_0
endwhile_0:
aload 0
return
.end method
.method public eq(II)Z
.limit stack 99
.limit stack 99
aload 0
return
.end method
.method public ne(II)Z
.limit stack 99
.limit stack 99
aload 0
return
.end method
.method public lt(II)Z
.limit stack 99
.limit stack 99
aload 0
return
.end method
.method public le(II)Z
.limit stack 99
.limit stack 99
aload 0
return
.end method
.method public gt(II)Z
.limit stack 99
.limit stack 99
aload 0
return
.end method
.method public ge(II)Z
.limit stack 99
.limit stack 99
aload 0
return
.end method
