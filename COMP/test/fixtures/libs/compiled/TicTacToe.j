.class public TicTacToe
.super java/lang/Object
.method <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method
.method public init()Z
.limit stack 99
.limit locals 99
bipush 3
newarray int
astore 0
bipush 3
newarray int
astore 0
bipush 3
newarray int
astore 0
bipush 2
newarray int
astore 0
aload 0
bipush 0
bipush 1
iastore
aload 0
bipush 1
bipush 2
iastore
bipush 0
astore 0
bipush 0
astore 0
aload 0
return
.end method
.method public getRow0()[I
.limit stack 99
.limit locals 99
aload 0
return
.end method
.method public getRow1()[I
.limit stack 99
.limit locals 99
aload 0
return
.end method
.method public getRow2()[I
.limit stack 99
.limit locals 99
aload 0
return
.end method
.method public MoveRow([II)Z
.limit stack 99
.limit locals 99
iload 2
; something is missing here
if_icmpge else_0
bipush 0
astore 3
goto endif_0
else_0:
; something is missing here
iload 2
if_icmpge else_0
bipush 0
astore 3
goto endif_0
else_0:
; something is missing here
aload 1
iload 2
iaload
if_icmpge else_0
bipush 0
astore 3
goto endif_0
else_0:
aload 1
bipush column
aload 0
iload 0
iaload
iastore
bipush 1
iadd
astore 0
bipush 1
astore 3
endif_0:
endif_0:
endif_0:
aload 3
return
.end method
.method public Move(II)Z
.limit stack 99
.limit locals 99
aload 0
aload 0
aload 0
invokevirtual /MoveRow([II)
astore 3
goto endif_0
else_0:
aload 0
aload 0
aload 0
invokevirtual /MoveRow([II)
astore 3
goto endif_0
else_0:
aload 0
aload 0
aload 0
invokevirtual /MoveRow([II)
astore 3
goto endif_0
else_0:
bipush 0
astore 3
endif_0:
endif_0:
endif_0:
aload 3
return
.end method
.method public inbounds(II)Z
.limit stack 99
.limit locals 99
iload 1
; something is missing here
if_icmpge else_0
bipush 0
astore 3
goto endif_0
else_0:
iload 2
; something is missing here
if_icmpge else_0
bipush 0
astore 3
goto endif_0
else_0:
; something is missing here
iload 1
if_icmpge else_0
bipush 0
astore 3
goto endif_0
else_0:
; something is missing here
iload 2
if_icmpge else_0
bipush 0
astore 3
goto endif_0
else_0:
bipush 1
astore 3
endif_0:
endif_0:
endif_0:
endif_0:
aload 3
return
.end method
.method public changeturn()Z
.limit stack 99
.limit locals 99
bipush 1
isub
astore 0
aload 0
return
.end method
.method public getCurrentPlayer()I
.limit stack 99
.limit locals 99
aload 0
return
.end method
.method public winner()I
.limit stack 99
.limit locals 99
bipush 0
bipush 1
isub
istore 2
bipush 3
newarray int
astore 1
aload 0
bipush 0
iaload
istore 2
goto endif_0
else_0:
aload 0
bipush 0
iaload
istore 2
goto endif_0
else_0:
aload 0
bipush 0
iaload
istore 2
goto endif_0
else_0:
bipush 0
istore 3
while_0:
iload 2
; something is missing here
if_icmpge endwhile_0
aload 1
bipush 0
aload 0
iload 3
iaload
iastore
aload 1
bipush 1
aload 0
iload 3
iaload
iastore
aload 1
bipush 2
aload 0
iload 3
iaload
iastore
aload 1
bipush 0
iaload
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
iload 2
; something is missing here
if_icmpge else_1
aload 1
bipush 0
aload 0
bipush 0
iaload
iastore
aload 1
bipush 1
aload 0
bipush 1
iaload
iastore
aload 1
bipush 2
aload 0
bipush 2
iaload
iastore
aload 1
bipush 0
iaload
istore 2
goto endif_0
else_0:
aload 1
bipush 0
aload 0
bipush 2
iaload
iastore
aload 1
bipush 1
aload 0
bipush 1
iaload
iastore
aload 1
bipush 2
aload 0
bipush 0
iaload
iastore
aload 1
bipush 0
iaload
istore 2
goto endif_0
else_0:
endif_0:
endif_0:
goto endif_1
else_1:
endif_1:
endif_0:
endif_0:
endif_0:
iload 2
; something is missing here
if_icmpge else_1
bipush 0
istore 2
goto endif_1
else_1:
endif_1:
iload 2
ireturn
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 99
.limit locals 99
new TicTacToe
dup
invokespecial TicTacToe/<init>()V
astore 1
aload 1
invokevirtual TicTacToe/init()Z
while_0:
bipush 0
astore 3
while_0:
aload 0
invokevirtual /printBoard()
aload 1
invokevirtual TicTacToe/getCurrentPlayer()I
istore 5
aload 0
iload 5
invokevirtual /playerTurn()
astore 4
aload 0
invokevirtual /wrongMove()
goto endif_0
else_0:
aload 0
invokevirtual /placeTaken()
goto endif_0
else_0:
bipush 1
astore 3
endif_0:
endif_0:
goto while_0
endwhile_0:
aload 1
invokevirtual TicTacToe/changeturn()Z
goto while_0
endwhile_0:
aload 0
invokevirtual /printBoard()
aload 1
invokevirtual TicTacToe/winner()I
istore 2
aload 0
iload 2
invokevirtual /printWinner()
return
.end method
