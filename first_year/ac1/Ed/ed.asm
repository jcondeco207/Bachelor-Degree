.globl main
.data
ARRAY:		.space 400
FILESIZE:	.word 100
INP:		.space 100	# espaco para string "command"
FN:		.space 52	# espaco para string "filename"
X:		.word 0
Y:		.word 0
POS:		.word 0
END:		.word 0
TRUECHAR:	.word 0
QM:		.string "?\n"
SAVED:		.word 0
ORIGIN:		.space 100
INSERT:		.space 100
NUMBERS:	.word 0, 0 
ADDERI:		.space 52
READ:		.space 1000
POSO:		.word 0
ENDO:		.word 0
ENTER:		.string "\n"
.text

# Utilities:

# ------------------------------------------------------------------------------------------------------
# mallocArray - reserva espaco para strings de comprimento 100 e coloca o seu endere�o no arrray
# a0 - endereco do array
# nao retorna nada
mallocArray:		
			li t0, 100	# array length (number of lines)
			mv t1, a0	# array address
	
	L_mallocArray:	li a7, 9
			li a0, 100    	# size of each string
			ecall		# heap allocated string
	
			sw a0, 0(t1)	# store pointer
			addi t1, t1, 4
			addi t0, t0, -1
			bgtz t0, L_mallocArray
			ret
# ------------------------------------------------------------------------------------------------------
# isNumber - verifica se e um numero
# a0 - ascii do possivel numero
# valor de retorno: a0 -> 1/0 caso seja ou nao numero
isNumber:		
			
			li t0, 48
			li t1, 57
			li t2, 0
			blt a0, t0, END_isNumber
			bgt a0, t1, END_isNumber
			addi t2, zero, 1
	END_isNumber:	mv a0, t2
			ret

# ------------------------------------------------------------------------------------------------------
# exit - sai do programa
# sem argumentos
# nao retorna nada
exit:			li a7, 93	
			add a0, t0, zero
			ecall
			ret

# ------------------------------------------------------------------------------------------------------
# exist_numbers - verifica se existem numeros na string
# a0 - endereco da string em questao
# valor de retorno: a0 -> 1/0 caso haja ou nao numeros
exist_numbers:		addi sp, sp, -32
			sw s6, 28(sp)
			sw s5, 24(sp)
			sw s4, 20(sp)
			sw s3, 16(sp)
			sw s2, 12(sp)
			sw s1, 8(sp)
			sw s0, 4(sp)
			sw ra, 0(sp)
			
			mv s0, a0
			li s1, 0	# check = 0
			li s2, 0	# i = 0
			
			li s3, 1	# number one
			li s4, 37	# '%'
			li s5, 36	# '$'
			
		l_en:	lb s6, 0(s0)	# s6 -> caracter em questao
			beqz s6, end_en
			
			#is number
			mv a0, s6
			jal isNumber
			beq a0, s3, fnd_en
			#is %
			beq s6, s4, fnd_en
			#is $
			beq s6, s5, fnd_en
			
			addi s0, s0, 1	# avanca na string 
			addi s2, s2, 1	# i++
			j l_en
			
		fnd_en:	li s1, 1	# check = 1
		
		end_en:	mv a0, s1	# a0 -> check (0/1)
			
			
			lw ra, 0(sp)
			lw s0, 4(sp)
			lw s1, 8(sp)
			lw s2, 12(sp)
			lw s3, 16(sp)
			lw s4, 20(sp)
			lw s5, 24(sp)
			lw s6, 28(sp)
			addi sp, sp, 32
			ret			

# ------------------------------------------------------------------------------------------------------
# copy - copia uma string para outra
# a0 - endereco da string destino
# a1 - endereco da string origem
# nao retorna nada
copy:
			lbu t0, 0(a1)
			addi a1, a1, 1
			beq t0, zero, END_copy	#ver se lbu da origem e nulo e se sim branch to the end, senao incrementar e continuar o ciclo
			sb t0, 0(a0)
			addi a0, a0, 1
			j copy
	END_copy:	li t2, 0
			addi a0, a0, 1
			sb t2, 0(a0)
			ret

# ------------------------------------------------------------------------------------------------------
# GetOrigin - serve para obter localizacao do ficheiro
# a0 - endereco string donde se vai copiar
# nao retorna nada
GetOrigin:
			
			mv a1, a0
			addi a1, a1, 2	# avancar letra e espaco
			la a0, ORIGIN	
			li t3, 10	# t3 = \n
			
			# a0 - endereco da string destino
			# a1 - endereco da string origem
		GO_l:	lbu t0, 0(a1)
			addi a1, a1, 1
			beq t0, t3, end_GO	#ver se lbu da origem e \n e se sim branch to the end, senao incrementar e continuar o ciclo
			sb t0, 0(a0)
			addi a0, a0, 1
			j GO_l

	end_GO:		li t2, 0
			addi a0, a0, 1
			sb t2, 0(a0)
			ret

# ------------------------------------------------------------------------------------------------------
# LenString - calcula numero de caracteres de uma string sem contar com o nulo
# a0 - endereco da string
# valor de retorno: a0 -> comprimento da string (sem contar com o nulo)
LenString:
			mv t0, a0	# t0 = string adress
			li a0, 0	# a0 = contador
		L_ls:	lb t1, 0(t0)
			beq t1, zero, END_ls
			addi t0, t0, 1
			addi a0, a0, 1
			j L_ls
		END_ls:	ret

# ------------------------------------------------------------------------------------------------------
# CompareStrings - compara strings
# argumentos: a0 -> endereco line1, a1 -> endereco line2
# devolve: a0 -> 1/0 se sao iguais ou nao
CompareStrings:
			mv t0, a0
			li a0, 0
		L_cs:	lbu t1, 0(t0)
			lbu t2, 0(a1)
			addi t0, t0, 1
			addi a1, a1, 1
			xor t3, t1, t2
			add a0, a0, t3
			beq t1, zero, END_cs
			beq t2, zero, END_cs
			j L_cs
		END_cs:	beq a0, zero, E_cs
			addi a0, zero, 1
		E_cs:	xori a0, a0, 1
			ret

# ------------------------------------------------------------------------------------------------------
# isLetter - verifica se e uma letra
# a0 - char
# valor de retorno: a0 -> 1/0 caso seja ou nao letra
isLetter:
			li t0, 97
			li t1, 122
			li t2, 0
			li t3, 81
			blt a0, t0, iL_PhaseOne
			bgt a0, t1, iL_PhaseOne
			addi t2, zero, 1
	iL_PhaseOne:	bne a0, t3, END_isLetter
			addi t2, zero, 1 
	END_isLetter:	mv a0, t2
			ret
			
# ------------------------------------------------------------------------------------------------------
# NumberToInt - passar um algarismo em char para int
# a0 - endereco do byte com o char do algarismo
# valor de retorno: a0 -> valor int do char em questao
NumberToInt:
			lbu t0, 0(a0) #passa o adress do numero pelo a0
			addi t0, t0, -48
			mv a0, t0
			ret

# ------------------------------------------------------------------------------------------------------
# CheckChar - verifica se existe um caracter na frase (string)
# a0 - endereco da string
# a1 - ascii do caracter procurado
# valor de retorno: a0 -> 1/0 caso exista ou nao na string
CheckChar:
			addi sp, sp, -4
			sw ra, 0(sp)
		
		
			mv t2, a0	#char *txt
			jal LenString
			
			li t0, 0 #x
			li t1, 0 #i
			mv t3, a0 #strlen(txt)
			mv t4, a1
			li a0, 0
			
	LOOP_CheckChar:	lb t5, 0(t2)
			bge t1, t3, END_CheckChar
			addi t2, t2, 1
			addi t1, t1, 1
			bne t5, t4, LOOP_CheckChar
			li a0, 1
		
	END_CheckChar:	lw ra, 0(sp)
			addi sp, sp, 4
			ret

# ------------------------------------------------------------------------------------------------------
# stop - atualiza variaveis x e y com os devidos valores
# a0 - endereco da string que sera analisada
# nao retorna nada
stop:
			addi sp, sp, -36
			sw s7, 32(sp)
			sw s6, 28(sp)
			sw s5, 24(sp)
			sw s4, 20(sp)
			sw s3, 16(sp)
			sw s2, 12(sp)
			sw s1, 8(sp)
			sw s0, 4(sp)
			sw ra, 0(sp)
			
			la t0, NUMBERS
			li t1, 0
			sw t1, 0(t0)
			sw t1, 4(t0)
			la t0, X
			sw t1, 0(t0)
			la t0, Y
			sw t1, 0(t0)
			
			
			li s0, -1		# s0 -> int i = -1
			la s1, NUMBERS		# s1 -> adress de numbers {0, 0} 
			la s2, ADDERI		# s2 -> adress de adderi[50]
			li s3, 0		# s3 -> int adder = 0
			mv s4, a0		# s4 -> endereco de str 
			addi s4, s4, -1
			
			jal exist_numbers
			beqz a0, end_stop
			
			li s5, -1		#s5 -> int j = 0
			li s6, 2
			
	for_stop:	addi s5, s5, 1		# j++
			bge s5, s6, efor_stop
			addi s0, s0, 1		# i++
			addi s4, s4, 1
	while_stop:	li t0, 0		# t0 -> \0
			li t1, 44		# t1 -> ','
			li t2, 10		# t2 -> \n
			lbu s7, 0(s4)		# s7 -> str[i]
			
			#(str[i] != '\0') && (str[i] != ',') && (!isLetter(str[i])) && (str[i] != '\n')
			beq s7, t0, ewhile_stop 
			beq s7, t1, ewhile_stop
			beq s7, t2, ewhile_stop
			mv a0, s7
			jal isLetter
			bnez a0, ewhile_stop
			#if((int)str[i] != 32)
			li t0, 32
			beq s7, t0, eif_stop
			#if(isNumber(str[i]))
			mv a0, s7
			jal isNumber
			beqz a0, else1_stop
			# adder = NumberToInt(str[i])
			mv a0, s4
			jal NumberToInt	
			mv s7, a0
	else1_stop:	mv s3, s7
			#----- end if/else -----#
			
			# numbers[j] = (numbers[j] * 10) + adder #
			lw t0, 0(s1)
			li t1, 10
			mul t0, t0, t1
			add t0, t0, s3
			sw t0, 0(s1)		
			# --------------------- #
			
	eif_stop:	li t2, 4
			mul t1, s5, t2		# t0 -> endereco de adderi[i]
			add t0, s2, t1
			sw s3, 0(t0)		# adderi[i] = adder
			addi s0, s0, 1		# i++
			addi s4, s4, 1		# avança na string str		
			j while_stop
			
	ewhile_stop:	addi s1, s1, 4		# avanca no array numbers
			j for_stop
			# if(adderi[0] == 0)
	efor_stop:	la t0, X		# t0 -> *px
			la t1, Y		# t1 -> *py
			la t3, ADDERI		# t3 -> adress do ADDERI
			lw t3, 0(t3)		# t3 -> primeiro valor do adderi
			bnez t3, skip1_stop	# adderi[0] == 0 ?
			li t2, -1		# t2 = -1
			sw t2, 0(t0)		# *px = -1
			sw t2, 0(t1)		# *py = -1
			jal end_stop
			# else		
	skip1_stop:	la t3, NUMBERS		# t3 -> adress do numbers
			lw t2, 0(t3)		# t2 = numbers[0]
			sw t2, 0(t0)		# *px = numbers[0]
			lw t2, 4(t3)		# t2 = numbers[1]
			sw t2, 0(t1)		# *py = numbers[1]
			
	end_stop:	lw ra, 0(sp)
			lw s0, 4(sp)
			lw s1, 8(sp)
			lw s2, 12(sp)
			lw s3, 16(sp)
			lw s4, 20(sp)
			lw s5, 24(sp)
			lw s6, 28(sp)
			lw s7, 32(sp)
			addi sp, sp, 36
			ret

# ------------------------------------------------------------------------------------------------------
# FindFunction - deteta se se trata da funcao e, p, w, etc...
# a0 - endereco da string (inserida pelo user)
# a1 - char com o possivel comando
# valor de retorno: a0 -> 1/0 caso exista esse comando na string ou nao
FindFunction:
			li t0, 0 	# check = 0 -> t0
			li t2, 0 	# i = 0 -> t2
			li t3, 32 	# t3 = 32 , a.k.a. "space"
			li t4, 10 	# t4 = \n , a.k.a. "enter"
	L_Ffunc:	lbu t1, 0(a0) 
			addi a0, a0, 1
			beq t1, t3, END_Ffunc
			beq t1, t4, END_Ffunc
			beqz t1, END_Ffunc
			bne t1, a1, L_Ffunc
			addi t0, zero, 1
				
	END_Ffunc:	mv a0, t0
			ret

# ------------------------------------------------------------------------------------------------------
# FindIndex - encontra a posicao no array de determinada linha
# a0 - endereco da linha atual no array
# a1 - endereco da primeira pos vazia a contar do fim do array
# a2 - numero da linha (x - 1o no inserido pelo user)
# valor de retorno: a0 -> retorna endereco da linha x
FindIndex:		
			mv t0, a0
			beq a2, zero, fi_end	# se x = 0 return apontador para pos atual que esta em a0
			la t0, ARRAY
			addi a2, a2, -1
	fi_loop:	bgt t0, a0, fi_bloop2	# loop enquanto t0<=pos
			beqz a2, fi_end		# x=0 encontrou indice da linha
			addi t0, t0, 4
			addi a2, a2, -1
			j fi_loop
			
	fi_bloop2:	la t1, ARRAY	
			addi t1, t1, 396	# t1 = ultimo endereco array
			mv t0, a1
			addi t0, t0 4		# t0 = endereco depois do end
			
	fi_loop2:	bgt t0, t1, fi_end	# loop enquanto t0<=t1
			beqz a2, fi_end		# x=0 encontrou indice da linha
			addi t0, t0, 4
			addi a2, a2, -1
			j fi_loop2
			
	fi_end:		mv a0, t0
			ret
	
# ------------------------------------------------------------------------------------------------------
# LastIndex - encontra a posicao no array da ultima linha escrita
# a0 - endereco da linha atual no array
# a1 - endereco da primeira pos vazia a contar do fim do array
# valor de retorno: a0 -> retorna endereco da ultima linha escrita
LastIndex:
			mv t0, a0		# t0 = apontador para pos atual
			mv t1, a1		# t1 = apontador para 1a pos vazia a contar do fim
			la t2, FILESIZE
			lw t3, 0(t2)		# t3 = FILESIZE
			la a0, ARRAY
			addi a0, a0, 396	# t2 = endereco da ultima pos array (99*4=396)
			bne t1, a0, END_li
			mv a0, t0
		END_li:	ret
		

# Arrray related:

# ------------------------------------------------------------------------------------------------------
# moveUp - movimenta um intervalo de linhas no array para cima (e atualiza a posicao atual)
# a0 - endereco da linha ate a qual se fara o move (inclusive)
# a1 - endereco do array
# a2 - endereco da linha atual no array
# a3 - endereco da primeira pos vazia a contar do fim do array
# nao retorna nada
moveUp:
			addi sp, sp, -20
			sw ra, 16(sp)
			sw s0, 12(sp)
			sw s1, 8(sp)
			sw s2, 4(sp)
			sw s3, 0(sp)
			
			mv s0, a0	# s0 = "i"
			mv s1, a1	# s1 = endereco array
			mv s2, a2	# s2 = endereco linha atual (pos)
			mv s3, a3	# s3 = endereco end
			
			addi t0, s2, -4
			beq s2, t0, E_mU	# if pos = endereco antes do array termina funcao
			la t0, ARRAY
			addi t0, t0, 396	# t0 = ultimo endereco do array
			beq s3, t0, E_mU	# if end = endereco antes do ultimo termina funcao
			
		L_mU:	beq s3, s0, E_mU	# loop enquanto end != "i"
			addi t0, s2, 4		# t0 = endereco a seguir ao da linha atual (pos)
			addi t1, s3, 4		# t1 = endereco a seguir ao do end
			lw a0, 0(t0)	# a0 = endereco string destino
			lw a1, 0(t1)	# a1 = endereco string origem
			jal copy
			addi s3, s3, 4		# incrementar end
			addi s2, s2, 4		# incrementar pos
			j L_mU
			
		E_mU:	la t0, POS
			sw s2, 0(t0)
			la t0, END
			sw s3, 0(t0)
			lw s3, 0(sp)
			lw s2, 4(sp)
			lw s1, 8(sp)
			lw s0, 12(sp)
			lw ra, 16(sp)
			addi sp, sp, 20
			ret

# ------------------------------------------------------------------------------------------------------
# moveDown - movimenta um intervalo de linhas no array para baixo (e atualiza a posicao atual)
# a0 - endereco da linha ate a qual se fara o move (inclusive)
# a1 - endereco do array
# a2 - endereco da linha atual no array
# a3 - endereco da primeira pos vazia a contar do fim do array
# nao retorna nada
moveDown:
			addi sp, sp, -20
			sw ra, 16(sp)
			sw s0, 12(sp)
			sw s1, 8(sp)
			sw s2, 4(sp)
			sw s3, 0(sp)
			
			mv s0, a0	# s0 = "i"
			mv s1, a1	# s1 = endereco array
			mv s2, a2	# s2 = endereco linha atual (pos)
			mv s3, a3	# s3 = endereco end
			
			addi t0, s2, -4
			beq s2, t0, E_mD	# if pos = endereco antes do array termina funcao
			
		L_mD:	blt s2, s0, E_mD	# loop enquanto pos >= "i"
			lw a0, 0(s3)		# a0 = endereco string na linha atual (pos)
			lw a1, 0(s2)		# a1 = endereco string no end
			jal copy
			addi s3, s3, -4		# decrementar end
			addi s2, s2, -4		# decrementar pos
			j L_mD
			
		E_mD:	la t0, POS
			sw s2, 0(t0)
			la t0, END
			sw s3, 0(t0)
			lw s3, 0(sp)
			lw s2, 4(sp)
			lw s1, 8(sp)
			lw s0, 12(sp)
			lw ra, 16(sp)
			addi sp, sp, 20
			ret

# ------------------------------------------------------------------------------------------------------
# changePos - modifica posicao atual do array
# a0 - endereco do array
# a1 - endereco da linha atual no array
# a2 - endereco da primeira pos vazia a contar do fim do array
# a3 - endereco x
# valor de retorno: a0 -> endereco da string da linha atual no array
changePos:
			addi sp, sp, -20
			sw ra, 16(sp)
			sw s0, 12(sp)
			sw s1, 8(sp)
			sw s2, 4(sp)
			sw s3, 0(sp)
			
			mv s0, a0	# s0 = endereco array
			mv s1, a1	# s1 = endereco linha atual (pos)
			mv s2, a2	# s2 = endereco end
			mv s3, a3	# s3 = endereco x
			
			# se pos = endereco x nao se fazem mudancas
			beq s1, s3, E_cP
			
			# se endereco x <= pos
			bgt s3, s1, else_cP	# se endereco x maior que pos vai pro else
			addi a0, s3, 4	# a0 = endereco depois de x
			mv a1, s0	# a1 = endereco array
			mv a2, s1	# a2 = endereco linha atual (pos)
			mv a3, s2	# a3 = endereco end
			jal moveDown
			j E_cP
			
			# else
		else_cP:	
			mv a0, s3	# a0 = endereco x
			mv a1, s0	# a1 = endereco array
			mv a2, s1	# a2 = endereco linha atual (pos)
			mv a3, s2	# a3 = endereco end
			jal moveUp
			j E_cP
			
		E_cP:	lw t0, POS
			lw a0, 0(t0)	# return endereco da string da linha atual no array
			lw s3, 0(sp)
			lw s2, 4(sp)
			lw s1, 8(sp)
			lw s0, 12(sp)
			lw ra, 16(sp)
			addi sp, sp, 20
			ret
			

# ------------------------------------------------------------------------------------------------------
# insertLines - insere input do utilizador no array
# a0 - endereco do array
# a1 - endereco da linha atual no array
# nao retorna nada
insertLines:
			addi sp, sp, -8
			sw ra, 4(sp)
			sw s0, 0(sp)
			
			mv s0, a1	# s0 = endereco pos
	loop_iL:	addi s0, s0, 4	# s0 = endereco a seguir a pos
			lw a0, 0(s0)	# a0 = endereco string a seguir a pos
			mv s1, a0	# s1 = endereco string a seguir a pos
			li a1, 100
			jal gets
			lbu t0, 0(s1)	# t0 = primeiro char da string inserida
			li t1, 46	# t1 -> dot '.'
			beq t0, t1, end_iL
			j loop_iL
		
	end_iL:
			# decrementar e salvar valor de pos
			addi s0, s0, -4
			la t0, POS
			sw s0, 0(t0)
			lw s0, 0(sp)
			lw ra, 4(sp)
			addi sp, sp, 8
			ret

# ------------------------------------------------------------------------------------------------------
# i - insere antes duma linha
# a0 - endere�o do array
# a1 - endere�o da linha atual no array
# a2 - endere�o da primeira pos vazia a contar do fim do array
# a3 - endereco x
# a4 - endereco y
# a5 - valor de TRUECHAR
# nao retorna nada
i:
			addi sp, sp, -32
			sw ra, 28(sp)
			sw s0, 24(sp)
			sw s1, 20(sp)
			sw s2, 16(sp)
			sw s3, 12(sp)
			sw s4, 8(sp)
			sw s5, 4(sp)
			sw s6, 0(sp)
			
			mv s0, a0		# s0 = endereco array
			mv s1, a1		# s1 = endereco linha atual (pos)
			mv s2, a2		# s2 = endereco end
			mv s3, a3		# s3 = endereco x
			mv s4, a4		# s4 = endereco y
			mv s5, a5		# s5 = valor truechar
			
			lw t0, 0(s4)		# t0 = y
			beqz t0, nxt_i
			mv s3, s4		# if y != 0, endereco x = endereco y
			
		nxt_i:
			# faz findindex se truechar=0 e x!= 36 ou x!=37
			beqz s5, anxt_i
			lw t0, 0(s3)
			li t1, 36
			beq t0, t1, aanxt_i
			li t1, 37
			beq t0, t1, aanxt_i
			
		anxt_i:	mv a0, s1		# a0 = endereco linha atual (pos)
			mv a1, s2		# a1 = endereco end
			lw a2, 0(s3) 		# a2 = x
			jal FindIndex
			mv s6, a0		# s6 = endereco linha x (linha antes da qual queremos inserir) -> "i"
			
		aanxt_i:
			beqz s5, else_i		# truechar = 0 -> branch
			lw t0, 0(s3)		# t0 = valor x
			li t1, 36
			beq t0, t1, if_i	# if x == 36 entrar no if
			li t1, 37
			bne t0, t1, else_i	# if x != 37 (e != 36) nao entra
			# i (s6) = li - 4 e move up
		if_i:	mv a0, s1		# a0 = endereco linha atual (pos)
			mv a1, s2		# a1 = endereco end
			jal LastIndex
			addi a0, a0, -4 	# a0 = endereco antes do da ultima linha escrita
			mv a1, s0		# a1 = endereco array
			mv a2, s1		# a2 = endereco linha atual (pos)
			mv a3, s2		# a3 = endereco end
			jal moveUp
			j E_i
			
		else_i:	ble s6, s1, else2_i	# entra else se i>pos
			mv a0, s6
			addi a0, a0, -4 	# a0 = endereco antes do da ultima linha escrita
			mv a1, s0		# a1 = endereco array
			mv a2, s1		# a2 = endereco linha atual (pos)
			mv a3, s2		# a3 = endereco end
			jal moveUp
			j E_i
			
		else2_i:
			mv a0, s6		# a0 = endereco da ultima linha escrita
			mv a1, s0		# a1 = endereco array
			mv a2, s1		# a2 = endereco linha atual (pos)
			mv a3, s2		# a3 = endereco end
			jal moveDown
			j E_i
			
		E_i:	la a0, ARRAY
			lw a1, POS
			
			jal insertLines
			lw s6, 0(sp)
			lw s5, 4(sp)
			lw s4, 8(sp)
			lw s3, 12(sp)
			lw s2, 16(sp)
			lw s1, 20(sp)
			lw s0, 24(sp)
			lw ra, 28(sp)
			addi sp, sp, 32
			ret

# ------------------------------------------------------------------------------------------------------
# a - insere depois duma linha
# a0 - endere�o do array
# a1 - endere�o da linha atual no array
# a2 - endere�o da primeira pos vazia a contar do fim do array
# a3 - endereco x
# a4 - endereco y
# a5 - valor de TRUECHAR
# nao retorna nada
a:
			addi sp, sp, -32
			sw ra, 28(sp)
			sw s0, 24(sp)
			sw s1, 20(sp)
			sw s2, 16(sp)
			sw s3, 12(sp)
			sw s4, 8(sp)
			sw s5, 4(sp)
			sw s6, 0(sp)
			
			mv s0, a0	# s0 = endereco array
			mv s1, a1	# s1 = endereco linha atual (pos)
			mv s2, a2	# s2 = endereco end
			mv s3, a3	# s3 = endereco x
			mv s4, a4	# s4 = endereco y
			mv s5, a5	# s5 = valor truechar
			
			lw t0, 0(s4)	# t0 = y
			beqz t0, nxt_a
			mv s3, s4	# if y != 0, endereco x = endereco y
			
		nxt_a:
			# faz findindex se truechar=0 e x!= 36 ou x!=37
			beqz s5, anxt_a
			lw t0, 0(s3)
			li t1, 36
			beq t0, t1, aanxt_a
			li t1, 37
			beq t0, t1, aanxt_a	
			
		anxt_a:	mv a0, s1	# a0 = endereco linha atual (pos)
			mv a1, s2	# a1 = endereco end
			lw a2, 0(s3) 	# a2 = x
			jal FindIndex
			mv s6, a0	# s6 = endereco linha x (linha antes da qual queremos inserir) -> "i"
			
		aanxt_a:	
			beqz s5, else_a	# truechar = 0 -> branch
			lw t0, 0(s3)	# t0 = valor x
			li t1, 36
			beq t0, t1, if_a	# if x == 36 entrar no if
			li t1, 37
			bne t0, t1, else_a	# if x != 37 (e != 36) nao entra
			# i (s6) = li - 4 e move up
		if_a:	mv a0, s1	# a0 = endereco linha atual (pos)
			mv a1, s2	# a1 = endereco end
			jal LastIndex	# a0 = endereco da ultima linha escrita
			mv a1, s0	# a1 = endereco array
			mv a2, s1	# a2 = endereco linha atual (pos)
			mv a3, s2	# a3 = endereco end
			jal moveUp
			j E_a
			
		else_a:	ble s6, s1, else2_a	# entra else se i>pos
			mv a0, s6	# a0 = endereco da ultima linha escrita
			mv a1, s0	# a1 = endereco array
			mv a2, s1	# a2 = endereco linha atual (pos)
			mv a3, s2	# a3 = endereco end
			jal moveUp
			j E_a
			
		else2_a:
			mv a0, s6	
			addi a0, a0, 4	# a0 = endereco a seguir ao da ultima linha escrita
			mv a1, s0	# a1 = endereco array
			mv a2, s1	# a2 = endereco linha atual (pos)
			mv a3, s2	# a3 = endereco end
			jal moveDown
			j E_a
			
		E_a:	la a0, ARRAY
			lw a1, POS
			jal insertLines
			lw s6, 0(sp)
			lw s5, 4(sp)
			lw s4, 8(sp)
			lw s3, 12(sp)
			lw s2, 16(sp)
			lw s1, 20(sp)
			lw s0, 24(sp)
			lw ra, 28(sp)
			addi sp, sp, 32
			ret


# ------------------------------------------------------------------------------------------------------
# d - delete intervalo de linhas (ou s� uma)
# a0 - endere�o do array
# a1 - endere�o da linha atual no array
# a2 - endere�o da primeira pos vazia a contar do fim do array
# a3 - endereco x
# a4 - endereco y
# a5 - valor de TRUECHAR
# nao retorna nada
d:
			addi sp, sp, -44
			sw ra, 40(sp)
			sw s0, 36(sp)
			sw s1, 32(sp)
			sw s2, 28(sp)
			sw s3, 24(sp)
			sw s4, 20(sp)
			sw s5, 16(sp)
			sw s6, 12(sp)
			sw s7, 8(sp)
			sw s8, 4(sp)
			
			mv s0, a0	# s0 = endereco array
			mv s1, a1	# s1 = endereco linha atual (pos)
			mv s2, a2	# s2 = endereco end
			mv s3, a3	# s3 = endereco x
			mv s4, a4	# s4 = endereco y
			mv s5, a5	# s5 = valor truechar
			
			# faz findindex se truechar=0 e x!= 36 ou x!=37
			#bnez s5, nex_d
			#lw t0, 0(s3)
			#li t1, 36
			#beq t0, t1, nex_d
			#li t1, 37
			#beq t0, t1, nex_d
			
			mv a0, s1
			mv a1, s2
			lw a2, 0(s3)
			jal FindIndex
			mv s6, a0	# s6 = "start" -> endereco linha x
			mv a0, s1
			mv a1, s2
			lw a2, 0(s4)
			jal FindIndex
			mv s7, a0	# s7 = "ending" -> endereco linha y
			mv a0, s1
			mv a1, s2
			jal LastIndex
			mv s8, a0	# s8 = "li" -> endereco ultima linha escrita
			
			# se y=36 e truechar=1 entro no if, senao branch pro segundo if
		nex_d:	beqz s5, bif_d
			li t0, 36
			lw t1, 0(s4)
			bne t0, t1, bif_d
			mv s7, s8
			
			# if x=37 && truechar || start=0 && ending=li
		bif_d:	lw t0, 0(s3)		# t0 = valor x
			li t1, 37
			bne t0, t1, A_d		# se x!=37 testar outra condicao
			bnez s5, if_d		# se truechar != 0 (e x=37) entao tem valor 1 logo entra no if
		A_d:	la t0, ARRAY
			bne s6, t0, else_if_d	# se endereco linha x != primeiro endereco array nao entra if
			bne s7, s8, else_if_d	# so entra if se ending=li (e start= primeiro indice array), senao branch
			
		if_d:	la t0, ARRAY
			addi s1, t0, -4		# pos = endereco antes array
			la t0, ARRAY
			addi s2, t0, 396	# end = ultimo endereco array
			j E_d
		#----
		# delete 1 linha
		else_if_d:
			lw t0, 0(s4)
			bnez t0, else_d		# se y!=0 vai pro else, se y=0 entra aqui
			
				# delete linha atual quando nao e a ultima
				la t0, ARRAY
				addi t0, t0, 396	# t0 = ultimo endereco do array
				beq s2, t0, else2_d	# se end = ultimo endereco do array nao entra aqui
				lw t0, 0(s3)		# t0 = x
				beqz t0, ent_d		# se x=0 entra aqui
				# testar start == *ppos, senao nao entra aqui
				bne s6, s1, else2_d
				
			ent_d:	lw a0, 0(s1)	# a0 = endereco string pos atual
				addi t0, s2, 4
				lw a1, 0(t0)	# # a1 = endereco string depois do end
				jal copy
				addi s2, s2, 4
				j E_d
				
			else2_d:		
				beq s6, s8, if3_d	# entra if se "start=li"
				beqz s5, else3_d	# se truechar = 0 nao entra
				lw t0, 0(s3)		# t0 = x
				li t1, 36
				bne t0, t1, else3_d	# se x != 36 nao entra
				
				# delete da ultima linha
				if3_d:
					# se x=36
					lw t0, 0(s3)		# t0 = x
					li t1, 36
					bne t0, t1, belse_if4_d	# se x != 36 nao entra
					mv s6, s8
					
					belse_if4_d:
					addi t0, s3, -4		# t0 = endereco antes start
					bne s2, t0, else_if4_d	# so entra se end = endereco antes start
					
					addi s2, s2, 4		# incrementar end 
					j E_d
					
					else_if4_d:
					la t0, ARRAY
					addi t0, t0, 396	# t0 = ultimo endereco do array
					bne s2, t0, else4_d	# so entra se end = ultimo endereco do array
					
					addi s1, s1, -4		# decrementar pos 
					j E_d
					
					else4_d:
					addi a0, s6, -4		# a0 = endereco antes do da linha x (decrementar start)
					mv a1, s0		# a1 = endereco array
					mv a2, s1		# a2 = endereco linha atual (pos)
					mv a3, s2		# a3 = endereco end
					jal moveUp	# move's alteram pos e end
					lw s1, POS
					lw s2, END
					addi s2, s2, 4		# incrementar end
					j E_d
					
				#delete doutra linha
				else3_d:
					# delete antes de pos
					bge s6, s1, else5_d	# so entra if se start<pos
					
					lw a0, 0(s6)		# a0 = string de start
					addi t0, s6, 4		# t0 = endereco depois do start
					lw a1, 0(t0)		# a1 = string depois do start
					jal copy
					addi a0, s6, 4		# a0 = endereco depois do start
					mv a1, s0		# a1 = endereco array
					mv a2, s1		# a2 = endereco linha atual (pos)
					mv a3, s2		# a3 = endereco end			
					jal moveDown	# move's alteram pos e end
					lw s1, POS
					lw s2, END
					addi s2, s2, 4		# incrementar end
					j E_d
					
					# delete depois de pos
					else5_d:
					mv a0, s6		# a0 = endereco start
					mv a1, s0		# a1 = endereco array
					mv a2, s1		# a2 = endereco linha atual (pos)
					mv a3, s2		# a3 = endereco end
					jal moveUp	# move's alteram pos e end
					lw s1, POS
					lw s2, END
					lw a0, 0(s1)		# a0 = endereco string da linha atual (pos)
					addi t0, s6, 4		# t0 = endereco depois do start
					lw a1, 0(t0)		# a1 = string depois do start
					jal copy
					addi s2, s2, 4		# incrementar end
					j E_d
			
		#----	
		else_d:	
			# entra fif se ending = li || (truechar && y = 36)
			beq s7, s8, fif_d
			bnez s5, else6_d
			lw t0, 0(s4)	# t0 = y
			li t1, 36
			bne t0, t1, else6_d
			#se final array vazio *ppos passa a ser indice antes do start, else moveUp das cenas
			fif_d:
				# entra if se end = ultimo endereco array ou se start <= pos -> array vazio ou inclui posi��o atual (n fa�o moveups)
				la t0, ARRAY
				addi t0, t0, 396	# t0 = ultimo endereco do array
				beq s2, t0, if7_d	# entra if se end = ultimo endereco array
				bgt s6, s1, else7_d	# se start>pos ( e end != ultimo endereco array) vai pro else
				if7_d:
				addi s1, s6, -4		# pos = endereco antes start
				la t0, ARRAY
				addi t0, t0, 396	# t0 = ultimo endereco do array
				mv s2, t0		# end = ultimo endereco do array
				j E_d
				
				# array com coisas no fim
				else7_d:
				addi a0, s6, -4 	# a0 = endereco antes start
				mv a1, s0		# a1 = endereco array
				mv a2, s1		# a2 = pos
				mv a3, s2		# a3 = end
				jal moveUp	# move's alteram pos e end
				lw s1, POS
				lw s2, END
				la t0, ARRAY
				addi t0, t0, 396	# t0 = ultimo endereco do array
				mv s2, t0		# end = ultimo endereco do array
				j E_d
				
			# ending != li
			else6_d:
			lw a2, 0(s4)
			addi a2, a2, 1	# a2 = y+1
			mv a0, s1	# a0 = pos
			mv a1, s2	# a1 = end
			jal FindIndex
			mv t0, a0	# t0 = "newpos"
				# entra if se newpos>pos -> intervalo para fazer delete apanha fim do array
				ble t0, s1, else8_d
					# se start>pos, start=endereco a seguir a pos, se nao faz so o resto do if
					ble s6, s1, if8_d
					
					addi s6, s1, 4	# start = pos+1
					
					
				if8_d:
				mv s2, t0	# end = "newpos"
				sw t0, 0(sp)	# guardar t0 na pilha
				j E_else6_d
				
				else8_d:
				addi a0, t0, 4	# a0 = endereco depois de "newpos"
				mv a1, s0	# a1 = endereco array
				mv a2, s1	# a2 = pos
				mv a3, s2	# a3 = end
				sw t0, 0(sp)	# guardar t0 na pilha
				jal moveDown	# move's alteram pos e end
				lw s1, POS
				lw s2, END
				j E_else6_d
				
			E_else6_d:
			lw a0, 0(s6)	# a0 = start
			lw t0, 0(sp)	# a1 = newpos que tava guardado na pilha
			lw a1, 0(t0)
			jal copy
			mv s1, s6	# pos = start
			
		E_d:	la t0, POS
			sw s1, 0(t0)
			la t0, END
			sw s2, 0(t0)
			lw s8, 4(sp)
			lw s7, 8(sp)
			lw s6, 12(sp)
			lw s5, 16(sp)
			lw s4, 20(sp)
			lw s3, 24(sp)
			lw s2, 28(sp)
			lw s1, 32(sp)
			lw s0, 36(sp)
			lw ra, 40(sp)
			addi sp, sp, 44
			ret

# ------------------------------------------------------------------------------------------------------
# c - altera intervalo linhas (ou so uma)
# a0 - endereco do array
# a1 - endereco da linha atual no array
# a2 - endereco da primeira pos vazia a contar do fim do array
# a3 - endereco x
# a4 - endereco y
# a5 - valor de TRUECHAR
# nao retorna nada
c:
			addi sp, sp, -36	# era 32 mas la pro meio uso stack pra guardar um numero
			sw ra, 32(sp)
			sw s0, 28(sp)
			sw s1, 24(sp)
			sw s2, 20(sp)
			sw s3, 16(sp)
			sw s4, 12(sp)
			sw s5, 8(sp)
			sw s6, 4(sp)
			
			mv s0, a0	# s0 = endereco array
			mv s1, a1	# s1 = endereco linha atual (pos)
			mv s2, a2	# s2 = endereco end
			mv s3, a3	# s3 = endereco x
			mv s4, a4	# s4 = endereco y
			mv s5, a5	# s5 = valor truechar
			
			# faz findindex se truechar=0 e x!= 36 ou x!=37
			beqz s5, nex_c
			lw t0, 0(s3)
			li t1, 36
			beq t0, t1, nex_c
			li t1, 37
			beq t0, t1, nex_c
			
			mv a0, s1	# a0 = endereco linha atual (pos)
			mv a1, s2	# a1 = endereco end
			lw a2, 0(s3) 	# a2 = x
			jal FindIndex
			mv s6, a0	# s6 = endereco linha x (a partir donde queremos mudar) -> "j"
			
			# if pos = endreco array -4 addi 4
		nex_c:	lw t0, 0(s0)
			addi t0, t0, -4
			bne s1, t0, if_c
			addi s1, s1, 4
		#----	
			# ver se y = 0, senao vai pra else_c
		if_c:	lw t0, 0(s4)
			bnez t0, else_c
			lw t0, 0(s3)
			li t1, 37
			beq t0, t1, else_c
			
			# y=0 and x=0
			lw t0, 0(s3)
			beqz t0, bife_c
			bne s6, s1, else2_c
			
		bife_c:	addi s1, s1, -4	# "pos -=1" (endereco linha atual anda para tras)
			mv a0, s0	# a0 = endereco array
			mv a1, s1	# a1 = endereco linha atual (pos)
			jal insertLines
			lw s1, POS
			lw s2, END
			j E_c
			
			# y=0 and x!=0
		else2_c:
			# if j<pos
			bge s6, s1, else3_c
			addi a0, s6, 4	# a0 = "j++"
			mv a1, s0	# a1 = endereco array
			mv a2, s1	# a2 = endereco linha atual (pos)
			mv a3, s2	# a3 = endereco end
			jal moveDown
			lw s1, POS
			lw s2, END
			addi a1, s1, -4	# a1 = endereco antes do da linha atual ("pos -= 1")
			mv a0, s0	# a0 = endereco array
			jal insertLines
			lw s1, POS
			lw s2, END
			j E_c
			
			# else (j>=pos)
		else3_c:
			mv a0, s6	# a0 = "j"
			mv a1, s0	# a1  = endereco array
			mv a2, s1	# a2 = endereco linha atual (pos)
			mv a3, s2	# a3 = endereco end
			jal moveUp
			lw s1, POS
			lw s2, END
			addi a1, s1, -4	# a1 = endereco antes do da linha atual ("pos -= 1")
			mv a0, s0	# a0 = endereco array
			jal insertLines
			lw s1, POS
			lw s2, END
			j E_c
		# ----	
			# y != 0 -> change intervalo
			# faz sempre delete do intervalo de linhas e coloca x e y a 0
		else_c:			
			# se change inclui a ultima linha fazer apend
			li t0, 36
			lw t1, 0(s3)		# t1 = x
			beq t0, t1, if2_c
			li t0, 37
			beq t0, t1, if2_c
			
			mv a0, s1	# a0 = endereco linha atual (pos)
			mv a1, s2	# a1 = endereco end
			lw a2, 0(s4)	# a2 = y
			jal FindIndex
			sw a0, 0(sp)	# por na pilha valor de retorno de FindIndex
			mv a0, s1	# a0 = endereco linha atual (pos)
			mv a1, s2	# a1 = endereco end
			jal LastIndex
			mv t0, a0	# t0 = endereco ultima linha escrita
			lw t1, 0(sp)	# t1 = endereco linha y
			beq t0, t1, if2_c	# fi=li entra no if
			beqz s5, else4_c	# truechar a 0 nao inclui ultima linha nao entra neste if
						# truechar a 1 e y=36 ou y=37 entra neste if, senap vai pro else
			
		if2_c:	mv a0, s0	# s0 = endereco array
			mv a1, s1	# s1 = endereco linha atual (pos)
			mv a2, s2	# s2 = endereco end
			mv a3, s3	# s3 = endereco x
			mv a4, s4	# s4 = endereco y
			mv a5, s5	# s5 = valor truechar
			jal d
			li t0, 0
			sw t0, 0(s3)	# x=0
			sw t0, 0(s4)	# y=0
			
			mv a0, s0	# a0 = endereco array
			lw a1, POS	# a1 = endereco linha atual (pos)
			lw a2, END	# a2 = endereco end
			mv a3, s3	# a3 = endereco x
			mv a4, s4	# a4 = endereco y
			mv a5, s5	# a5 = valor truechar
			jal a
			j E_c
			
			# nao inclui ultima linha fazer insert
		else4_c:
			mv a0, s0	# s0 = endereco array
			mv a1, s1	# s1 = endereco linha atual (pos)
			mv a2, s2	# s2 = endereco end
			mv a3, s3	# s3 = endereco x
			mv a4, s4	# s4 = endereco y
			mv a5, s5	# s5 = valor truechar
			jal d
			li t0, 0
			sw t0, 0(s3)	# x=0
			sw t0, 0(s4)	# y=0
			
			mv a0, s0	# s0 = endereco array
			lw a1, POS	# a1 = endereco linha atual (pos)
			lw a2, END	# a2 = endereco end
			mv a3, s3	# s3 = endereco x
			mv a4, s4	# s4 = endereco y
			mv a5, s5	# s5 = valor truechar
			jal i
			j E_c
		#----	
		E_c:	
			lw s6, 4(sp)
			lw s5, 8(sp)
			lw s4, 12(sp)
			lw s3, 16(sp)
			lw s2, 20(sp)
			lw s1, 24(sp)
			lw s0, 28(sp)
			lw ra, 32(sp)
			addi sp, sp, 36
			ret	

# ------------------------------------------------------------------------------------------------------
# p - mostra na consola intervalo linhas (ou so uma)
# a0 - endereco do array
# a1 - endereco da linha atual no array
# a2 - endereco da primeira pos vazia a contar do fim do array
# a3 - endereco x
# a4 - endereco y
# a5 - valor de TRUECHAR
# nao retorna nada
p:
			addi sp, sp, -40
			sw ra, 36(sp)
			sw s0, 32(sp)
			sw s1, 28(sp)
			sw s2, 24(sp)
			sw s3, 20(sp)
			sw s4, 16(sp)
			sw s5, 12(sp)
			sw s6, 8(sp)
			sw s7, 4(sp)
			sw s8, 0(sp)
			
			mv s0, a0	# s0 -> endereço do array
			mv s1, a1	# s1 -> endereço do pos
			mv s2, a2	# s2 -> endereço do end
			mv s3, a3	# s3 -> endereço do x	
			mv s4, a4	# s4 -> endereço do y
			li s5, 0	# s5 -> start
			li s6, 0	# s6 -> nextpos
			lw s7, 0(s3)	# s7 -> x
			lw s8, 0(s4)	# s8 -> y
					
			li t0, 37
			li t1, 36
			
			# if(*px == 37 || *px == 36)
			beqz a5, step4_p	# truechar = 0 -> branch
			beq s7, t0, step2_p
			beq s7, t1, step2_p
			beq s8, t1, step2_p
			j step4_p
			
			# if(*px == 37)
	step2_p:	bne s7, t0, elseif1_p
			la s5, ARRAY
			mv a0, s1
			mv a1, s2
			jal LastIndex
			mv s6, a0
			mv a0, s0 
			mv a1, s1
			mv a2, s2
			mv a3, s6
			jal changePos
			lw s1, POS
			lw s2, END
			j for_p
			
			# if(y == 36)
	elseif1_p:	li t0, 36
			bne s8, t0, else1_p
			mv a0, s1
			mv a1, s2
			mv a2, s7
			jal FindIndex
			mv s5, a0
			mv a0, s1
			mv a1, s2
			jal LastIndex
			mv s6, a0
			mv a0, s0 
			mv a1, s1
			mv a2, s2
			mv a3, s6
			jal changePos
			lw s1, POS
			lw s2, END
			j for_p		
			
			# else x != 37
	else1_p:	mv a0, s1
			mv a1, s2
			jal LastIndex
			mv s6, a0
			mv a0, s0 
			mv a1, s1
			mv a2, s2
			mv a3, s6
			jal changePos
			lw s1, POS
			lw s2, END
			mv a0, s1
			mv a1, s2
			jal LastIndex
			mv s5, a0
			j for_p	
			
			
			# if py = 0
	step4_p:	bnez s8, step5_p 
			#if x != 0		
			beqz s7, conti_p
			mv a0, s1
			mv a1, s2
			mv a2, s7
			jal FindIndex
			mv s6, a0
			la a0, ARRAY
			mv a1, s1
			mv a2, s2
			mv a3, s6
			jal changePos
			lw s1, POS
			lw s2, END
			
			#pertence ao final do else if
	conti_p:	mv s5, s1	
			j for_p
			
			#else final
	step5_p:	mv a0, s1
			mv a1, s2
			mv a2, s8
			jal FindIndex
			mv s6, a0
			la a0, ARRAY
			mv a1, s1
			mv a2, s2
			mv a3, s6
			jal changePos
			lw s1, POS
			lw s2, END
			mv a0, s1
			mv a1, s2
			mv a2, s7
			jal FindIndex
			mv s5, a0

	for_p:		bgt s5, s1, end_p
			lw a0, 0(s5)		 
			jal puts
			addi s5, s5, 4
			j for_p
		
	end_p:		
			lw s8, 0(sp)
			lw s7, 4(sp)
			lw s6, 8(sp)
			lw s5, 12(sp)
			lw s4, 16(sp)
			lw s3, 20(sp)
			lw s2, 24(sp)
			lw s1, 28(sp)
			lw s0, 32(sp)
			lw ra, 36(sp)
			
			addi sp, sp, 40
			ret

# Files:

# ------------------------------------------------------------------------------------------------------
# Distri - divide a string a cada "\n"
# a0 - adress do READ
# a1 - adress onde escrever
# nao retorna nada
Distri:		mv t0, a1 
		
		mv t2, a0	# string de onde se vai ler
		
	Di_bl:	lw t1, 0(t0)	# string onde se escreve
		
	Di_l:	lbu t3, 0(t2)	# copia do read um char
		beqz t3, e_ed	# if(str[i] != 0)
		sb t3, 0(t1)	# insere o caracter na string destino
		addi t2, t2, 1	# avança no READ
		addi t1, t1, 1	# avança na string destino
		
		li t4, 10	# t4 = '\n'
		bne t3, t4, Di_l
		addi t0, t0, 4
		j Di_bl
		
	e_ed:	addi t0, t0, -4
		la t1, POS
		sw t0, 0(t1)
		la t0, ARRAY
		addi t0, t0, 396
		la t1, END
		sw t0, 0(t1)
		ret
					
		
# ------------------------------------------------------------------------------------------------------
# e - abre ficheiro e copia tudo para array
# a0 - endereco de string com diretorio do ficheiro
# a1 - endereco do array
# a2 - endereco da linha atual no array
# a3 - adress do end
# nao retorna nada
e:			addi sp, sp, -40
			sw s8, 36(sp)
			sw s7, 32(sp)
			sw s6, 28(sp)
			sw s5, 24(sp)
			sw s4, 20(sp)
			sw s3, 16(sp)
			sw s2, 12(sp)
			sw s1, 8(sp)
			sw s0, 4(sp)
			sw ra, 0(sp)
			
			mv s0, a0		# s0 -> filename
			mv s1, a1		# s1 -> adress do ARRAY
			lw s2, 0(a2) 		# s2 -> valor pos
			lw s3, 0(a3)		# s3 -> valor end
			mv s4, a2		# s10 -> adress do pos
			mv s5, a3		# s11 -> adress do end 
			
			# abrir o ficheiro em modo leitura #
			li a7, 1024		# system call for open file
  			la a0, ORIGIN		# nome do ficheiro 
  			li a1, 0		# Open for reading (flags are 0: read, 1: write)
  			ecall			# open a file (file descriptor returned in a0)
  			mv s6, a0		# save the file descriptor
  			mv s7, a0
			# operacoes no ficheiro #
			
			li s8, 0
		l_e:	bge s8, s7, end_e	
			li a7, 63		# service
			mv a0, s6		# file descriptor
			la a1, READ		# endereco onde meter
			li a2, 100		# buffer size
			ecall 
			
			la a0, READ
			mv a1, s1
			jal Distri
			addi s1, s1, 4
			
			addi s8, s8, 1
			j l_e
			
			#fechar o ficheiro
			li   a7, 57       # system call for close file
 			mv   a0, s6       # file descriptor to close
			ecall             # close file
			
		end_e:	lw ra, 0(sp)
			lw s0, 4(sp)
			lw s1, 8(sp)
			lw s2, 12(sp)
			lw s3, 16(sp)
			lw s4, 20(sp)
			lw s5, 24(sp)
			lw s6, 28(sp)
			lw s7, 32(sp)
			lw s8, 36(sp)
			addi sp, sp, 40 
			ret	
	

# ------------------------------------------------------------------------------------------------------
# w - guarda a informacao do array num ficheiro
# a0 - endereco de string com diretorio do ficheiro
# a1 - endereco do array
# a2 - endereco da linha atual no array
# a3 - endereco da primeira pos vazia a contar do fim do array
# valor de retorno: a0 -> caso haja sucesso retorna 1
w:			
			addi sp, sp, -40
			sw s8, 36(sp)
			sw s7, 32(sp)
			sw s6, 28(sp)
			sw s5, 24(sp)
			sw s4, 20(sp)
			sw s3, 16(sp)
			sw s2, 12(sp)
			sw s1, 8(sp)
			sw s0, 4(sp)
			sw ra, 0(sp)
			
			lw s0, FILESIZE
			mv s1, a2 		# s1 -> endereço do pos
			mv s2, a3		# s2 -> endereço do end
			sub s3, s2, s1		# s3 -> pos - end
		
			la s4, ARRAY
			addi s4, s4, -4
			la s5, ARRAY
			addi s5, s5, 396
			
			beq s1, s4, end2_w	# if pos == -1 -> termina	
	#w_empty1:	#bne s2, s5, w_empty2	# if(end > max )
			#li s7, 0		# sz = 0
			
			
			## Abre o ficheiro ##
	w_empty2:	
			li a7, 1024		# system call for open file
  			la a0, ORIGIN		# nome do ficheiro onde vai guardar
  			li a1, 1		# Open for writing (flags are 0: read, 1: write)
  			ecall			# open a file (file descriptor returned in a0)
  			mv s6, a0		# save the file descriptor
			
			#operacoes no ficheiro
			la s8, ARRAY		
	loop_w:		bgt s8, s1, bloop2_w	#for(int i = 0; i <= pos; i++)
			lw t0, 0(s8)
			li   a7, 64       	# system call for write to file
  			mv   a0, s6       	# file descriptor
  			mv   a1, t0     	# Endereco da frase de onde escrever
  			li   a2, 100       	# tamanho da frase
  			ecall             	# write to file
  			addi s8, s8, 4
			j loop_w
			
	bloop2_w:	mv s8, s2
			addi s8, s8, 4
	loop2_w:	bgt s8, s5, end_w	#for(int i = end; i <= ultima posição; i++)
			lw t0, 0(s8)
			li   a7, 64       	# system call for write to file
  			mv   a0, s6       	# file descriptor
  			mv   a1, t0     	# Endereco da frase de onde escrever
  			li   a2, 100       	# tamanho da frase
  			ecall             	# write to file
  			addi s8, s8, 4
			j loop2_w
	end_w:	
			#fecha ficheiro
			li   a7, 57       	# system call for close file
  			mv   a0, s6       	# file descriptor to close
  			ecall             	# close file
  			
  	end2_w:		li a0, 1
  	
  			lw ra, 0(sp)
			lw s0, 4(sp)
			lw s1, 8(sp)
			lw s2, 12(sp)
			lw s3, 16(sp)
			lw s4, 20(sp)
			lw s5, 24(sp)
			lw s6, 28(sp)
			lw s7, 32(sp)
			lw s8, 36(sp)
			addi sp, sp, 40 
  			ret

# Main stuff:

# ------------------------------------------------------------------------------------------------------
# FindDaWae - identifica a funcao a chamar e invoca-a
# a0 - endereco de string com input do utilizador
# a1 - endereco do array
# a2 - endereco da linha atual no array
# a3 - endereco da primeira pos vazia a contar do fim do array
# a4 - endereco do inteiro que indica se ficheiro esta salvo ou nao (0/1)
# a5 - endereco da string com o nome do ficheiro de input
# nao retorna nada

FindDaWae:	
		addi sp, sp, -36
		sw ra, 32(sp)
		sw s0, 28(sp)
		sw s1, 24(sp)
		sw s2, 20(sp)
		sw s3, 16(sp)
		sw s4, 12(sp)
		sw s5, 8(sp)
		sw s6, 4(sp)
		sw s7, 0(sp)
		
		mv s0, a0		# adress do command
		mv s1, a1		# adress do array
		lw s2, POS		# adress do pos
		lw s3, END		# adress do end
		mv s4, a4		# adress do saved
		mv s5, a5		# adress do filename
		
		jal stop
		lw t0, X
		lw t1, Y
		
		lw t0, X		# verifica se numeros inseridos pelo usar estao fora do intervalo de linhas escritas
		lw t1, Y
		li t2, 36
		li t3, 37
		beq t0, t2, C_fdw
	A_fdw:	beq t0, t3, C_fdw
	B_fdw:	bne t1, t3, N_fdw
	C_fdw:	la t0, TRUECHAR
		li t1, 1
		sw t1, 0(t0)		# truechar a 1 se tiver sido inserido caracter especial
		
	N_fdw:	mv a0, s2		# teste para ver se numeros inseridos sao invalidos
		mv a1, s3
		jal LastIndex
		mv s6, a0		# s6 = ultimo endere�o escrito
		mv a0, s2
		mv a1, s3
		lw a2, X
		lw t0, TRUECHAR
		# se truechar && x=36 ou x=37 vai pra bi_fdw
		beqz t0, N1_fdw
		li t0, 36
		beq a2, t0, bi_fdw
		li t0, 37
		beq a2, t0, bi_fdw
	N1_fdw:	jal FindIndex
		mv s7, a0		# s7 = endereco da linha x
		lw t0, X
		bltz t0, INV
		bgt s7, s6, INV
		
	bi_fdw:	la a0, INP
		li a1, 105		# "i"
		jal FindFunction
		beqz a0, a_fdw
		li t4, 0		# saved = 0
		sw t4, 0(a4)
		# if pos = -1, pos++
		la t0, ARRAY
		addi t0, t0, -4
		bgt s2, t0, i_fdw
		mv a0, s1		# a0 = endereco arraay
		mv a1, s2		# a1 = adress de pos
		mv a2, s3		# a2 = adress de end
		la a3, X		# a3 = adress de x
		la a4, Y		# a4 = adress de y
		lw a5, TRUECHAR		# a5 = valor do truechar
		jal a
		j E_fdw
	i_fdw:	mv a0, s1		# a0 = adress do array
		mv a1, s2		# a1 = adress do pos
		mv a2, s3		# a2 = adress do end
		la a3, X		# a3 = endereco x
		la a4, Y		# a4 = endereco y
		lw a5, TRUECHAR
		jal i
		j E_fdw

		
	a_fdw:	la a0, INP
		li a1, 97		# "a"
		jal FindFunction
		beqz a0, c_fdw
		li t4, 0		# saved = 0
		sw t4, 0(a4)
		mv a0, s1		# a0 = endereco arraay
		mv a1, s2		# a1 = adress de pos
		mv a2, s3		# a2 = adress de end
		la a3, X		# a3 = adress de x
		la a4, Y		# a4 = adress de y
		lw a5, TRUECHAR		# a5 = valor do truechar
		jal a
		lw t0, POS
		lw t1, END
		j E_fdw
		
	c_fdw:	la a0, INP
		li a1, 99		# "c"
		jal FindFunction
		beqz a0, d_fdw
		li t4, 0		# saved = 0
		sw t4, 0(a4)
		mv a0, s1		# a0 = endereco array
		mv a1, s2		# a1 = adress de pos
		mv a2, s3		# a2 = adress de end
		la a3, X		# a3 = adress de x
		la a4, Y		# a4 = adress de y
		lw a5, TRUECHAR		# a5 = valor de truechar
		jal c
		j E_fdw
		
	d_fdw:	la a0, INP
		li a1, 100		# "d"
		jal FindFunction
		beqz a0, p_fdw
		li t4, 0		# saved = 0
		sw t4, 0(a4)
		mv a0, s1		# a0 = adress de array
		mv a1, s2		# a1 = adress de pos
		mv a2, s3		# a2 = adress de end
		la a3, X		# a3 = adress de x
		la a4, Y		# a4 = adress de y
		
		lw a5, TRUECHAR		# a5 = valor de truechar
		jal d			
		j E_fdw

		
	p_fdw:	la a0, INP
		li a1, 112		# "p"
		jal FindFunction
		beqz a0, e_fdw

		mv a0, s1		# a0 = adress de array
		mv a1, s2		# a1 = adress de pos
		mv a2, s3		# a2 = adress de end
		la a3, X		# a3 = adress de x
		la a4, Y		# a4 = adress de y
		lw a5, TRUECHAR		# a5 = valor de truechar
		jal p
		j E_fdw
		
	e_fdw:
		la a0, INP
		li a1, 101		# "e"
		jal FindFunction
		beqz a0, f_fdw
		la a0, INP		# a0 = adress de "command"
		jal GetOrigin		
		la a1, ORIGIN		# a1 = adress da string origem
		la a0, FN		# a0 = adress da string destino (filename)
		jal copy
		li t4, 1		# saved = 1
		sw t4, 0(s4)
		la a0, ORIGIN		# a0 = adress de ORIGIN
		la a1, ARRAY		# a1 = adress do array
		mv a2, s2		# a2 = adress de pos
		mv a3, s3		# a3 = adress de end
		jal e			
		j E_fdw
		
	f_fdw:	
		la a0, INP
		li a1, 102		# "f"
		jal FindFunction
		
		beqz a0, w_fdw
		li t4, 0		# saved= 0
		sw t4, 0(a4)
		la a0, INP		# a0 = adress de command
		jal GetOrigin
		la a0, FN		# a0 = adress de filename
		la a1, ORIGIN		# a1 = adress de origin
		jal copy		
		la a0, FN		# a0 = adress de filename		
		jal puts 		# mostra nome do ficheiro
		la a0, ENTER
		jal puts
		j E_fdw			
		
	w_fdw:	la a0, INP
		li a1, 119		# "w"
		jal FindFunction
		beqz a0, q_fdw
		lbu t5, FN		# t5 = primeiro char de "filename"
		beqz t5, INV		# se filename == NULL invalido
		la a0, FN		# a0 = endereco "filename"
		la a1, ARRAY		# a1 = endereco array
		mv a2, s2		# a2 = adress de pos
		mv a3, s3		# a3 = adress de end
		jal w
		la t6, SAVED
		sw a0, 0(t6)		# saved = 1 se sucesso
		j E_fdw
		
	q_fdw:	la a0, INP
		li a1, 113		# "q"
		jal FindFunction
		beqz a0, Q_fdw
		lw t5, SAVED
		li t6, 1
		bne t5, t6, INV
		jal exit
		j E_fdw
		
	Q_fdw:	la a0, INP
		li a1, 81	# "Q"
		jal FindFunction
		beqz a0, cp_fdw
		jal exit
		j E_fdw
		
	cp_fdw:	lw t5, X	# t5 = x
		blez t5, INV	# se x <= 0 -> invalid
		mv a0, s2	# a0 = adress de pos
		mv a1, s3	# a1 = adress de end
		lw a2, X	# a2 = valor de X
		jal FindIndex
		mv a3, a0	# a3 = adress de x
		mv a0, s1	# a0 = endereco array
		mv a1, s2	# a1 = adress de pos
		mv a2, s3	# a2 = adress de end
		jal changePos
		# a0 - endereco da string a fazer print
		jal puts
		j E_fdw
				
	INV:	la a0, QM
		jal puts
				
	E_fdw:	
		lw ra, 32(sp)
		lw s0, 28(sp)
		lw s1, 24(sp)
		lw s2, 20(sp)
		lw s3, 16(sp)
		lw s4, 12(sp)
		lw s5, 8(sp)
		lw s6, 4(sp)
		lw s7, 0(sp)
		addi sp, sp, 36
		ret

# ------------------------------------------------------------------------------------------------------
# puts - mostra uma string da consola
# a0 - endereco da string
# nao retorna nada
puts:
	li a7, 4	# printstring
	ecall
	ret

# ------------------------------------------------------------------------------------------------------
# gets - obtem uma string da consola
# a0 - endereco da string
# a1 - tamanho maximo da string
# nao retorna nada
gets:		
		li a7, 8
		ecall
		ret

# ------------------------------------------------------------------------------------------------------
main:		
		addi sp, sp, -12
		lw s0, 0(sp)
		lw s1, 4(sp)
		lw s2, 8(sp)
		
		la a0, ARRAY
		jal mallocArray
		
		la s0, ARRAY		# s0 = adress do array
		addi s0, s0, -4		# s0 = adress do pos ?
		la t0, POS		
		sw s0, 0(t0)		# valor do pos =  ?
		la s1, ARRAY		# s1 = adress do array
		addi s1, s1, 396	# s1 = adress do end (99*4=396)
		la t0, END
		sw s1, 0(t0)		
		la s2, SAVED		# s2 = adress do saved

	while:	la a0, INP		# a0 = adress do input
 		li a1, 100		# a1 = sz do input
 		jal gets		# obter 100 chars do input
 		la a0, INP		# a0 = adress do input
 		la a1, ARRAY		# a1 = adress do array
 		mv a2, s0		# a2 = adress do POS
 		mv a3, s1		# a3 = adress do END
 		mv a4, s2		# a4 = adress do saved
 		la a5, FN		# a5 = adress do filename
 		jal FindDaWae
		j while
		
		sw s0, 0(sp)
		sw s1, 4(sp)
		sw s2, 8(sp)
		addi sp, sp, 12
