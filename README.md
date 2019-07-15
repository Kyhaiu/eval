# EVAL #

## Analisador de expressões aritméticas ##

**Neste algoritmo o usuário poderá entrar com uma expressão aritmética genérica (em uma string), como:**

* A + B * C

* A * (B + C/D)

* –A * (–B + C)

* A * –(C – log(B))

* A + 4 * log(3 / (abs(1 – X)) + sen(–B/4 + PI)

* (3 * Sin(PI * X)) ^ 2 – (2 * cos(PI * Y)) ^ 2


Caso necessário para o cálculo da expressão, o avaliador de expressões deverá ser
capaz de reconhecer e solicitar ao usuário os valores de todas as variáveis (A, B, C, D,
X, Y, por exemplo) envolvidas na expressão. As variáveis ficarão limitadas às 26 letras
do alfabeto(ASCII).

Os operadores que são suportados neste avaliador de expressões são:

1. <code><b>-(menos) </b>unário</code>;

2.  Adição e subtração (<code><b>+</b> e <b>-</b></code>);

3. Multiplicação e divisão (<code><b>*</b> e <b>/</b></code>);

4. <code><b>^</b></code> (operador de exponenciação);

5. Funções transcendentais: 

	* <b><code>log (base 10);</code>
	
	* <code>sen;</code> 
	
	* <code>cos;</code>

	* <code>tan</code>

	* <code>sqrt (raiz quadrada);</code>
 
	* <code>abs(módulo);</code></b>

6. A constante <code>**PI**</code> deve é definida como <b>3,1415926535898</b> 
