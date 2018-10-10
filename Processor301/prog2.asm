sub $0, $0, $0
sub $2, $2, $2
addi $2, $2, 3
beq $2, $0, 0x400004 #loop 3 times
add $0, $0, $1
j 0x400000
slt $5, $0, $1
lw $1, 0($3)
sw $1, 4($3)
addi $19, $10, 1 