# [THE PITT] The pitt programming Language :-

# IMPORTANT:- 
Pitt is not fully developed / stabilized language any thing could change at any moment source code is open but it is not free

# Performace / Scripting NOTE:-
if C-Like string is not working just convert it to pitt string by <memory_beg> cstr-to-pstr


## Updates && Milestones
# (Unknown Date) (New-Feature Update)
  `Supports nested ifs`
# (Unknown Date) (New-Feature Update)
  `Supports while-then-end` 
# (Unknown Date) (New-Feature Update)
  `Supports basic stdout statements like puts with string`
# Date (20.3.22) (New-Feature Update and Major-Improvement Update)
  `now supports exit keyword -> <exitid> exit`
  `fixed some of major string issues`
# Date (21.3.22) (Major-Improvement Update)
  `now supports macros`
  `now supports whiles in macros`
# Date (22.3.22) (Minor-Improvement Update)
  `fixed false if condition jumping and some other minor fixes`
# Date (23.3.22) (New-Stack Operator Update)
  `added rot drop and over stack operator`
# Date (26.3.22) (ARGC and ARGV)
  `added argument counter and argument vector`
  Little Note :- so you simulate it like this -> `pitt sim file`
  also you may give some arguments `pitt sim file abcd` so here my language ignores `pitt sim file` and directly reads from ab  cd as its argv
# Date (27.3.22) (GE NE LE && String-Stack Updates)
  `added >= <= and != operators`
  `added string functions :- pstrlen (to-get the string length) , pstrcmp (to compare strings)`
# Date (28.3.22) (AND OR Update and Some updates)
  `added and or keyword for stack condition manipulation`
  `added intrinsic : str-to-int`
  `memory-updates : !8 to store a byte at a given position and @8 to load a byte from a given position`
# Date (29.3.22) (Function Update)
  `added cstring to pitt string converter : cstr-to-pstr`
  `max and min keyword`
# Date (30.3.22) (Include Update)
 `CONTRIBUTOR: TopchetoEU (TopchetoEU#1072)`
 `keyword: include -> <token-file-name> include`
# Date (31.3.22) (Major Update)
 `added buffered input scanning by read -> <buffersize> <filedescriptor> read`
 `for now only supports stdin as file descriptor`
# Date (2.4.22) (Function Update)
 `added syscall1 just like syscall3 but with 1 argument ([place -- ptr])`
# Date (4.4.22) (Memory Update)
 `added 16 bit memory store and load`
# Date (8.4.22) (Memory)
 `added malloc type keyword  mem-alloc`
 [From now 0 is an invalid pointer in the memory stack for the normal pushes]

# Date (9.4.22) (Bind)
 `added bind keyword that binds a identifier to a data type`
 
# Date (13.4.22) (Big Update)
  `added sub-commands -t , -S and a new type -d for base command`
  `added data-types for some special needs (for bind and offset keyword) int (indicates integer) str (indicates string) ptr (indicates memory)`
  `added offset keyword offset just adds the given amount to the stack-head so that it ignores that much amount of space`

# Date (14.4.2022) 
 `added import function (finally)`



## Basic Keywords/Operators Usages :-
  Known Operators [+,-,*,/,=,<,>]
  block instructions [if-else-end,while-end,macro-end]
  <if>-<else> statements are common
  <nestedif> statements are now supported
  <end> is used to end block instructions
  <print> statement for writing string to stdout
  <macro> keyword usage :- `macro <identifier> <definition> end`
  <exit> keyword usage :-  `<exitid> exit`
  `<rot> <drop> <over>`
  `!= <= >=`
  `and or`
  `cstr-to-pstr takes 1 arguments : <memory_beginning> cstr-to-pstr`
  `2byte ptr !16 ptr @16`

  
  

## Implementations todo :-
  implement better if-else-end label [else]
  implement functions
  implement string errors
  support nested while loop properly

## Faults :-
  Doesn't support/has any warning for recursive macros (mutually,direct,dead) // needs an expansion


## Data Types
  INT
  STRING
  PITT-STRING (loads as bytes)
  CHAR/BYTE 
  BOOL [Coming]
  PTR [Coming]

  
## Ints
  Ints gets pushed onto the stack after isInt check succeds else it continues
  
## Strings
  Strings are actuall string literals unlike a part of memory 
  Strings gets pushed to string stack
  
  ```pascal
  "Hello World" puts
  ```
  here "Hello World" is pushed onto the string stack
  and puts pops the stack top and writes it to stdout
  

## Examples
  `examples/showcase of this language is at ` ./tests/simulated-tests


## Feedback
  `if you find some bugs/glitches report at I/O Mixture#5239 (discord)`


## Hello World
  ```pascal
  "Hello, World" puts
  ```
  
## Loop
  ```pascal
  <int> while dup <int> <operator> then
    <body>
  <end>
  ```
## Conditions
  ```pascal
  <condition> if
    <body>
  <end>
  ```

## Include
  ```pascal
  <file> include
  ```
  
