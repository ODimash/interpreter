# Грамматика языка программирование Justy

> <small> :warning: Данные в этой странице считается лишь планом грамматики языка :warning:</small>


### *program*
```
<program> ::= <code_block>
```
*<program\>*: Это главная форма, которая представляет собой программу на языке программирование. Она состоит из списка операторов (<code_block>).

---
### *code_block*
```
<code_block> ::= <statement> | <statement> <code_block>
```
*<code_block>*: Это список операторов программы. Он может содержать один или более операторов (<statement\>).

---
### *Виды операторов*
```
<statement> ::= <assignment> 
		| <if_statement> 
		| <while_loop> 
		| <for_loop> 
		| <function_definition> 
		| <return_statement> 
		| <expression>
```
*<statement\>*: Оператор программы. Это может быть присваивание, условный оператор (if), цикл (while или for), определение функции (fnc), оператор return или выражение.

---
### *Оператор присвоения*
```
<assignment> ::= <identifier> ':=' ( <expression> | <string> | <boolean> | <array> )
```

---
### *Условные операторы*
```
<if_statement> ::= 'if' <expression> '{' <code_block> '}' <elif_statement> <else_statement> 
<elif_statement> ::= 'elif' <expression> '{' <code_block> '}' | ε
<else_statement> ::= 'else' '{' <code_block> '}' | ε
```
> ε- означает, что данный блок могут быть пустым

---
### *Циклы*
```
<while_loop> ::= 'while' <expression> '{' <code_block> '}'
<for_loop> ::= 'for' <identifier> 'in' <expression> '{' <code_block> '}'
<loop_loop> ::= 'loop' <expression> '{' <code_block> '}'
```

### *Функция*
```
<function_definition> ::= 'fnc' <identifier> '(' <parameters> ')' '{' <code_block> '}'
<parameters> ::= <identifier> | <identifier> ',' <parameters> | ε
<return_statement> ::= 'return' <expression>
```

### *Выражении*
```
<expression>     ::= <logical_or> | <call_function> | <system_functions>
<logical_or>     ::= <logical_and> 'or' <logical_or> | <logical_and>
<logical_and>    ::= <equality> 'and' <logical_and> | <equality>
<equality>       ::= <relational> ('=' | '!=') <equality> | <relational>
<relational>     ::= <additive> ('<' | '<=' | '>' | '>=') <relational> | <additive>
<additive>       ::= <multiplicative>  ('+' | '-') <additive> | <multiplicative>
<multiplicative> ::= <unary>     ('*' | '/') <multiplicative> | <unary>
<unary>          ::= <additive_operators> ('+' | '-') | <primary>
<primary>        ::= <identifier> | <number> | '(' <expression> ')'
<call_function> ::= <identifier> '(' <parameters> ')'
```

### *Типы данных*
```
<number> ::= <integer> | <float> | <boolean>
<integer> ::= <decimal> | <hexadecimal> | <binary>
<decimal> ::= <digit> | <digit> <decimal>
<hexdecimal> ::= '0x' <hex_number>
<binary> ::= '0x' <binary_number>
<digit> ::= [0-9]

<string> ::= '"' <text> '"'
<boolean> ::= "true" | "false"
```

### *Массив*
```
<array> ::= '[' <elements> ']'
<elements> ::= <value> | <value> ',' <elements>
<value> ::= <number> | <string> | <boolean> | <array>
```