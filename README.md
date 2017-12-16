# Recursive_parser_C
A recursive descent parser for a context-free language </br >
A recursive-descent parser that evaluates arithmetic expressions defined by the following context-free grammar described in EBNF:
</br >
command → expr ‘\n’
</br >
expr → term { + term | - term }
</br >
term → power { ∗ power | / power | % power }
</br >
power → factor [ ^ power ]
</br >
factor → [-] factor1
</br >
factor1 → ( expr ) | NUMBER
</br >
NUMBER = [0 - 9]+
</br >
</br >
Sample Execution 1:
</br >
Input: 5 + 6 ∗ 2 ∧ 2 ∧ 2
</br >
Output:
</br >
5 	NUMBER
</br >
`+` 	PLUS
</br >
6 	NUMBER
</br >
∗ 	MULT
</br >
2 	NUMBER
</br >
∧ 	POWER
</br >
2 	NUMBER
</br >
∧ 	POWER
</br >
2 	NUMBER 
</br >
Result: 101
</br >
</br >
Sample Execution 2:
</br >
Input: 19 % 5 ∗ 10 / ( 2 ∧ 2 ) Output:
</br >
19 	NUMBER
</br >
% 	REMAINDER
</br >
5 	NUMBER
</br >
∗ 	MULT
</br >
10 	NUMBER
</br >
/ 	DIVIDE
</br >
( 	LPAREN
</br >
2 	NUMBER
</br >
∧ 	POWER
</br >
2 	NUMBER
</br >
) 	RPAREN 
</br >
Result: 10
</br >

