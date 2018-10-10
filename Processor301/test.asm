sub $0, $0, $0 						#clear out register $0
sub $1, $1, $1						#clear out register $1
sub $2, $2, $2						#clear out register $2
addi $1, $1, 1						#register $1 = 1
addi $2, $2, 3						#register $2 = 3
beq $2, $0, 0x400004 				#loop 3 times
add $0, $0, $1						#register $0 = $0 + $1
j 0x00400014						#jump to beq $2, $0, 0x400004
addi $1, $5, 0						
sub $4, $4, $4						#clear out register $4
sub $5, $5, $5						#clear out register $5
addi $5, $5, 1						# $5 = 1
slt $4, $0, $1						# $4 = 0 first, then changes to 1 after loop
beq $4, $5, 0x400002				#loops once
addi $1,$1, 6						#$1 = 6
j 0x00400030						# jump to beq $4, $5, 0x400002
lw $7, 0($10)						# $7 = MEM[10000068] which should be 0x1ea9d4cc
sw $7, 4($10)						# MEM[1000006c] = $7 data (=0x1ea9d4cc)