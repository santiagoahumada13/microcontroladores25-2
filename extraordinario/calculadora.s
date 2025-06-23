	area Calculadora,code,readonly
	export Suma
	export Resta
	export Multiplicacion
	export Division
	export Exponente
	export SQRT
	export logb4
		
Suma
	add 	r0,r0,r1
	bx		lr
	
Resta
	subs 	r0,r0,r1
	bx		lr
	
Multiplicacion 
	push 	{LR}
	cmp		r1,#0
	beq		mul_0
	
	mov		r2,r1	 ;R2 representa el segundo operando de la multiplicacion
					 ;y cuantas veces se va asumar a si mismo el primer operando 
					 ;(algoritmo de una multiplicación)
	mov		r1,r0	 ;Mueve el primer operando a R1 para hacer la suma a si mismo
	sub		r2,r2,#1 ;Ajusta el contador del ciclo de sumas
loop_mult
	bl		Suma	 ;Llamado a la operacion de suma
	subs	r2,r2,#1 ;Resta el contador
	bne 	loop_mult ; Si no es cero (0) regresa al ciclo, si es cero continua a la siguiente operacion
	pop		{LR}
	bx		lr		 ;Vuelve al programa principal (C)
mul_0
	mov		r0,#0
	pop		{LR}
	bx		lr
	
Division
	sdiv	r0,r0,r1
	bx		lr
		
Exponente
	push	{lr}
	;Casos aislados
	cmp		r1,#0
	beq		exp_0
	
	cmp		r1,#1
	beq		exp_1
	
	;Rutina del exponenete
	mov		r2,r1
	
	sub		r2,r2,#1
	mov		r3,r2
	mov 	r4,r0
	
loop_exp
	mul		r0,r0,r4
	add		r3,r3,#1
	subs	r2,r2,#1
	bne		loop_exp
	pop		{lr}
	bx		lr
exp_0
	mov		r0,#1
	pop		{lr}
	bx		lr
exp_1
	mov		r0,r0
	pop		{lr}
	bx		lr
	
SQRT	 
; Raiz cuadrada de newton: x_k+1=1/2*(x_k+n/x_k)
;en la que x=/sqrt n
	push	{lr}	
	mov		r1,#1 ;Semilla de x_k
x_kp1
	cmp		r5,#1		;mientras que |x_k+1 - x_k | <= 1
	ble		done_sqrt
	
	udiv	r2,r0,r1 	;Divide n entre x_k
	add		r3,r2,r1	;Suma x_k al resultado de la operación
	lsr		r4,r3,#1 	; Usa un desplazamiento logico a la derecha para dividir entre 2 el resultado
	
	sub		r5,r4,r1	;x_k+1 - x_k
	add		r1,r1,#1	;incrementa la semilla para obtener la raiz cuadrada 
	
	b		x_kp1

done_sqrt
	mov		r0,r4
	pop		{LR}
	bx		lr

;Logaritmo base 4 -----------------------------------------------------------------------------------------------------------------------------------------
logb4   

	;En r0 se encuentra el operando al que se busca calcular el logaritmo base 4
	;Por lo que hay que comparar este numero con el resultado de la exponenciacion
	;Cuando sea mayor o igual devuelve el valor al codigo C
	;un ciclo while, mientras que Operando <= Resultado del exponente regresa el exponente que satisface esa expresion
	
	push {LR}
	mov r5,r0 ;Mueve el operando del logaritmo a un registro sin uso
	mov	r6,#0 ;Semilla del registro a comparar
	mov	r1,#1 ;Semilla para el exponente
	mov	r7,#0
	mov	r8,#0
loop_log
	cmp	 	r5,r7
	ble	 	done_log
	
	mov		r0,#4 ;Base del logaritmo
	bl		Exponente
	mov		r7,r0
	mov		r8,r3
	
	add 	r1,r1,#1
	b		loop_log
done_log
	mov		r0,r8
	pop		{LR}
	bx 		lr

	end
		
