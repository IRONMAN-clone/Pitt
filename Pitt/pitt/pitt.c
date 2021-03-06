//TODO: Make recursive macros work properly
//TODO: Optimize the language properly
//TODO: Safety for String mechanism
//TODO: bsp , ssp , msp , offset

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <time.h>

#define bool int
#define true 1
#define false 0

int error_count = 0;

int isNumber(char *string)
{
  int __expect = strlen(string);
  int __found = 0;
  if(string[0] == '-' && (int)strlen(string) > 1){
      __found += 1;
  }
  for(int i = 0; i < (int)strlen(string)+1; i++){
    if(string[i] >= '0' && string[i] <= '9'){
      __found  += 1;
    }
  }
  if(__found == __expect){
    return true;
  }
  else{
    return false;
  }
}

#define byte char

// Intrinsics
#define OP_PLUS 0
#define OP_MINUS 1
#define OP_MUL 2
#define OP_DIV 3
#define OP_DUMP 4
#define OP_EQUAL 5
#define OP_DUP 6
#define OP_GT 7
#define OP_LT 8
#define OP_IF 9
#define OP_ELSE 10
#define OP_ELIF 11
#define OP_END 12
#define OP_WRITE 13
#define OP_WHILE 14
#define OP_DO 15
#define OP_BOR 16
#define OP_BAND 17
#define OP_XOR 18
#define OP_SHR 19
#define OP_SHL 20
#define OP_SWAP 21
#define OP_MOD 22
#define OP_PUTS 23
#define OP_MEM 24
#define OP_LOAD 26
#define OP_BREAK 27
#define MACRO 28
#define IDENTIFIER 29
#define KW_EXIT 30
#define KW_INCLUDE 31
#define BLOCK_PROC 32
#define OP_OVER 33
#define OP_DROP 34
#define OP_ROT 35
#define SYSCALL3 36
#define ARGC 37
#define ARGV 38
#define GE 39
#define LE 40
#define NE 41
#define PSTRLEN 42
#define PSTRCMP 43
#define OP_AND 44
#define OP_OR 45
#define INTRINSIC_TOINT 46
#define INTRINSIC_LOAD8 47
#define INTRINSIC_STORE8 48
#define CSTR_TO_PSTR 49
#define MAX 50
#define MIN 51
#define STR_DROP 52
#define TYPE_INT 53
#define TYPE_STR 54
#define TYPE_BOOL 55
#define TYPE_PTR 56
#define PROC_STDIN 57
#define PROC_STDOUT 58
#define READ 59
#define OP_EDIV 60
#define SYSCALL1 61
#define PUTCHAR 62
#define OP_STRCHAR 63
#define OP_CSTRDUP 64
#define INTRINSIC_STORE16 65
#define INTRINSIC_LOAD16 66
#define INTRINSIC_MEMORY 67
#define OP_SIZEOF 68
#define OP_PTROF 69
#define IN_BIND 70
#define STORE_INT 71
#define LOAD_INT 72
#define OFFSET 73
#define P_TYPE_INT 74
#define P_TYPE_STR 75
#define BSP 76
#define AMP_BSP 77
#define SSP 78
#define AMP_SSP 79
#define MSP 80
#define AMP_MSP 81
#define P_TYPE_PTR 82
#define STDERR   83
#define FPUT     84
#define OP_PUSHABLE 85
int OP_COUNT = OP_PUSHABLE + 1;
#define OP_PUSH_STR 25

const char* readable[] = {"PLUS","MINUS","MULTIPLY","DIVISION","DUMP","EQUAL","DUP","GREATER","LESS","IF","ELSE","ELIF","END","PRINT","WHILE","THEN","BOR","BAND","XOR","SHR","SHL","SWAP","MOD","PUTS","MEM","STRING","LOAD","BREAK","MACRO","IDENTIFIER","EXIT","INCLUDE","PROC","OVER","DROP","ROT","SYSCALL3","ARGC","ARGV","GREATER EQUAL","LESSER EQUAL","NOT EQUAL","CSTRLEN","CSTRCMP","AND","OR","TO-INT","LOAD8","STORE8","CSTR-TO-PSTR","MAX","MIN","STR-DROP","INT","STRING","BOOL","POINTER","STDIN","STDOUT","READ","EDIV","SYSCALL1","PUTCHAR","STR-CHAR","CSTRDUP","STORE16","LOAD16","MEMORY","SIZEOF","PTR-OF","BIND","STORE-INT","LOAD-INT","OFFSET","PITT-CODE-INT","PITT-CODE-STRING","BASE POINTER","AMPERAND BASE POINTER","STRING STACK POINTER","AMPERAND STRING STACK POINTER","MEMORY STACK POINTER","AMPERAND MEMORY STACK POINTER","PITT-CODE-POINTER","STDERR","FPUT","INT","UNEXPECTED"};

const char* inbuilt[] = {"+","-","*","/",".","=",">","<",",",">=","<=","!=","dup","print","if","end","else","elif","while","then","bor","band","xor","shr","shl","swap","puts","mod","mem","macro","exit","include","proc","rot","drop","over","syscall3","argc","argv","pstrlen","pstrcmp","and","or","to-int","@8","!8","cstr-to-pstr","max","min","str-drop","stdin","stdout","read","ediv","syscall1","putchar","str-char","cstrdup","!16","@16","malloc","sizeof","ptr-of","bind","!int","@int","offset","int","str","bsp","&bsp","msp","&msp","ssp","&ssp","ptr","stderr","fput"};
// @ load ! store

const char *sof = "sizeof";
const char *ptr_of = "ptr-of";

const char typePlus = '+';
const char typeMinus = '-';
const char typeMul = '*';
const char typeDiv = '/';
const char typeDump = '.';
const char typeEqual = '=';
const char typeGt = '>';
const char typeLt = '<';
const char typeLoad = ',';

const char* typeGE = ">=";
const char* typeLE = "<=";
const char* typeNE = "!=";
const char* dup = "dup";
const char* write = "print";
const char* block_if = "if";
const char* block_end = "end";
const char* block_else = "else";
const char* block_elif = "elif";
const char* block_while = "while";
const char* block_do = "then";
const char* bor = "bor";
const char* band = "band";
const char* xor = "xor";
const char* shr = "shr"; // >>
const char* shl = "shl"; // <<
const char* swap = "swap";
const char* putz = "puts";
const char* mod = "%";
const char* mem = "mem";
const char* macro = "define";
const char* ex_it = "exit";
const char* inc = "import";
const char* proc = "proc";
const char* rot = "rot";
const char* drop = "drop";
const char* over = "over";
const char* syscall3 = "sys3";
const char* __arg_count = "argc";
const char* __arg_vect = "argv";
const char* pstrlen = "cstrlen";
const char* pstrcmp = "cstrcmp";
const char* typeAnd = "and";
const char* typeOr = "or";
const char* TO__INT = "str-to-int";
const char* cstr_to_pstr = "cstr-to-pstr";
const char* __max = "max";
const char* __min = "min";
const char* str_drop = "str-drop";
const char* typeread = "read";
const char* typestdin = "stdin";
const char* typestdout = "stdout";
const char* typestderr = "stderr";
const char* divmod = "ediv";
const char* syscall1 = "sys1";
const char* put__c = "putchar";
const char* cstr_dp = "cstrdup";
const char* bind = "bind";
const char* offset = "offset";

const char* load8 = "@8";
const char* store8 = "!8";
const char* str_char = "char-at";
const char* load16 = "@16";
const char* store16 = "!16";
const char* mem_all = "malloc";

const char* store_int = "!int";
const char* load_int = "@int";
const char* pint = "int";
const char* pstr = "str";
const char* pptr = "ptr";
const char* fp__ = "fput";


#define STR_CAP 640000
#define MEM_CAP 640000
#define MEMORY_HEAP_CAP 640000 //Allocatable memory heap size


// A struct containing lexemes and token values
struct ipair{
  int opType;
  int val;
  int line;
  int col;
  char *opStr;
  int toInclude; // include keyword has been seized for some reasons
};

// A struct containing 'bind'
struct binding{
  char *bind_name;
  int bind_val1;
  char *bind_val2;
  int type;
};



int find_end_block(struct ipair *pair,int loc,int len)
{
  int end_block = -1;
  int move = 0;
  for(int i = loc; i <= len; i++){
    
    if(pair[i].opType == OP_DO){
      move += 1;
    }
    
    if(pair[i].opType == MACRO){
      move += 1;
    }
    
    if(pair[i].opType == INTRINSIC_MEMORY){
      move+=1;
    }
    
    if(pair[i].opType == OP_END){
      if(move == 0){
        end_block += i;
        break;
      }
      else{
	move -= 1;
      }
    }
  }
  return end_block;
}


int find_else_block(struct ipair *pair,int loc,int len)
{
  int else_block = -1;
  for(int i = loc+1; i <= len; i++){    
    if(pair[i].opType == OP_ELSE){
      else_block += i;
      break;
    }
  }
  return else_block;
}

//Validating file type
int __isvalidfile(const char* file){
  int ext = 0;
  char *load = strdup(file);
  
  int pos = 0;
  
  char *str = strtok(load,".");

  while(str != NULL){
    pos++;
    str = strtok(NULL,".");

    if(pos = 2){
      if(strcmp(str,"pitt")==0){
	return true;
	break;
      }
      else{
	return false;
	break;
      }
    }
  }
}


int find_if_block(struct ipair *pair,int loc,int len)
{
  int if_block = -1;
  for(int i = loc; i <= len; i++){    
    if(pair[i].opType == OP_IF){
      if_block += i;
      break;
    }
  }
  return if_block;
}

void error_with_stack_id(char *message,int stack_portion)
{
  printf("STACK:%d: Error %s\n",stack_portion,message);
}



int get_size_of_file(const char* path)
{
  FILE *program = fopen(path,"r");

  if(!program){
    printf("Error: Expected a valid program file path\n");
    printf("FILE:\n");
    printf("    Can't open    '%s'\n",path);    
  }
  
  fseek(program,0,SEEK_END);
  int size = ftell(program)+1;
  fseek(program,0,SEEK_SET);

  return size;
}

int find_space(char *line,int index)
{
  int col = 0;
  for(int i = index; i < (int)strlen(line)+1; i++){
    if(line[i] == ' '){
      col = i;
      break;
    }
  }
  return col;
}

void human_readable_type(int id)
{
  printf("%s\n",readable[id]);
}

// Parsing garbage values
char *lex_str(char *line)
{
  int len = strlen(line)+1;
  char *newstr = NULL;
  int bp1 = 0;
  bool isstr = false;
  int size = 0;
  
  for(int i = 0; i < len; i++){
    if(line[i] == '\"'){
      bp1 = i;
      isstr = true;
      break;
    }
  }

  for(int i2 = bp1+1; i2 < len; i2++){
    if(line[i2+1] == '\"'){
      size = i2;
      break;
    }
  }
  
  int ix = 0;
  if(isstr == true){
    newstr = (char*)malloc(sizeof(char)*size);
    for(int i3 = bp1+1; i3 <= size; i3++){
      newstr[ix] = line[i3];
      ix += 1;
    }
    newstr[ix] = '\0';
     return newstr;
  }
  else{
    return NULL;
  }
  
}

int strip_col(char *txt,int *col)
{
  int ret = -1;
  for(int i = *col + 1; i < (int)strlen(txt)+1; i++){
    if((txt[i] == ' ' || txt[i] == '\0' || txt[i] == '\n')&& (txt[i+1] != ' ' && txt[i+1] != '\0' && txt[i+1] != '\n')){
      ret = i;
      *col = i;
      break;
    }
  }
  return ret;
}

int word_count_str(char *s)
{
  int i = 0;
  int words = 0;

  int b = false;
  words += 1;
  for(int i = 0; i <= strlen(s); i++){
    if(s[i] == ' ' && b == false){
      words += 1;
      b = true;
    }
    if(s[i] != ' '){
      b = false;
    }
		    
  }
  
  return words;
}

void refine_and_print(char *line,const char* f,int lin)
{
  int len = strlen(line);
  char *nstr = (char*)malloc(sizeof(char)*len+1);
  int push = 0;
  
  for(int i = 0; i < len; i++){
    nstr[push] = line[i];
    if(line[i] == '\\'){
      i += 1;
      switch(line[i]){
      case 'n':
	nstr[push] = '\n';
	i += 1;
	break;
      case 't':
	nstr[push] = '\t';
	i += 1;
	break;
      case 'b':
	nstr[push] = '\b';
	i += 1;
	break;
      case '0':
	nstr[push] = '\0';
	i += 1;
	break;
      case '\\':
	nstr[push] = '\\';
	i += 1;
	break;
      default:
	printf("\n%s:%d: ERROR: unknown type of escape character `%c`\n",f,lin,nstr[i]);
	exit(0);
      }
    }
    printf("%c",nstr[push]);
    push += 1;
  }


}

bool not_Inbuilt(char *word){
  bool notinbuilt = true;

  if(strcmp(word,dup) == 0){notinbuilt = false;}
  if(strcmp(word,write)==0){notinbuilt = false;}
  if(strcmp(word,block_if)==0){notinbuilt = false;}
  if(strcmp(word,block_end)==0){notinbuilt = false;}
  if(strcmp(word,block_else)==0){notinbuilt = false;}
  if(strcmp(word,block_elif)==0){notinbuilt = false;}
  if(strcmp(word,block_while)==0){notinbuilt = false;}
  if(strcmp(word,block_do)==0){notinbuilt = false;}
  if(strcmp(word,bor)==0){notinbuilt = false;}
  if(strcmp(word,band)==0){notinbuilt = false;}
  if(strcmp(word,xor)==0){notinbuilt = false;}
  if(strcmp(word,shr)==0){notinbuilt = false;}
  if(strcmp(word,shl)==0){notinbuilt = false;}
  if(strcmp(word,swap)==0){notinbuilt = false;}
  if(strcmp(word,"puts")==0){notinbuilt = false;}
  if(strcmp(word,mod)==0){notinbuilt = false;}
  if(strcmp(word,mem)==0){notinbuilt = false;}
  if(strcmp(word,macro)==0){notinbuilt = false;}
  if(strcmp(word,inc)==0){notinbuilt = false;}

  return notinbuilt;
}

bool is_id(char *word,int line,const char* file)
{
  bool is_id = true;
  char *not_str = lex_str(word);
  if(not_str == NULL && not_Inbuilt(word) == true && isNumber(word) == false){
    if(word[0] < '0' || word[0] > '9'){
      for(int i = 0; i < (int)strlen(word)+1; i++){
	if(word[i] == '*' ||  word[i] == ',' || word[i] == '/' || word[i] == '-' || word[i] == '+' || word[i] == '=' || word[i] == '.' || word[i] == '"' || word[i] == '['  || word[i] == ']'  || word[i] == '<' || word[i] == '>' || word[i] == ' ' || word[i] == '\"'){
	  is_id = false;
	  break;
	}
      }
    }
  }
  else if(not_Inbuilt(word) == false){
    is_id = false;
  }
  return is_id;
}

int com_enab = false;
int mark = 0;

// Parser
struct ipair *load_program_from_file(const char* path)
{
    //Format check
    if(__isvalidfile(path) == false){
      char format[256];
      int f = 0;
      for(int i = 0; path[i] != '\0'; i++){
	if(path[i] == '.'){
	  for(int i2 = i+1; path[i2] != '\0'; i2++){
	    format[f] = path[i2];
	    f++;
	  }
	  break;
	}
      }
      printf("%s:1: ERROR: unsupported file format -> %s\n",path,format);
      printf("%s:1: NOTE: supported Formats: pitt\n",path);
      exit(0);
    }
  
    FILE *program = fopen(path,"r");
    int lines = 0;

    if(!program){
      printf("%s:%d: ERROR: Expected a valid file\n",path,1);
      printf("FILE:\n");
      printf("    Can't open    '%s'\n",path);
    }

    fseek(program,0,SEEK_END);
    int size = ftell(program)+1;
    fseek(program,0,SEEK_SET);

    if(size < 1){
      exit(0);
    }

    struct ipair *pitt_pairs = (struct ipair*)malloc(sizeof(struct ipair)*size+1);
    // ---- Parsing Words & tokens ----
    char *tm = (char*)malloc(sizeof(char)*size+1);
    int pair_trace = 0;
    char delim[] = {' ','\n','\0'};

    char *tmtm[size+1];
    int tmtm_push = -1;

    for(int i = 0; i <= size; i++){
      pitt_pairs[i].opType = -1;
    }
    

    while(fgets(tm,size+1,program) != NULL){     
      lines += 1;

      char *lexed = lex_str(tm);
      bool is_str = false;
      int count = 0;
      int be_ = 0;

      // String-Type ignore
      if(lexed != NULL){
	is_str = true;
	count = word_count_str(lexed);
	be_ = count - count;
	if(count == 0){
	  be_ -= 2;
	}
	else{
	  be_ -= 1;
	}
      }

      char *pitt_words = strtok(tm,delim);
      //int colx = 0;
      while(pitt_words != NULL){
	//printf("WORD - %s\n",pitt_words);
	//int cols = colx;
	//colx += strlen(pitt_words);
	int has_op_type = false;

	if(com_enab == true){
	  mark = lines + 1;
	}
	if(lines != mark){
	  has_op_type = true;
	}
	else{
	  has_op_type = false;
	  com_enab = false;
	  mark = 0;
	}
	
	// String-Type push
	if(is_str == true){
	  pitt_pairs[pair_trace].opStr = lexed;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].opType = OP_PUSH_STR;
	  pitt_pairs[pair_trace].line = lines;
          //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  is_str = false;
	  has_op_type = true;
	}

	// String Major fix applied
	if(count != be_){
	  count -= 1;
	  has_op_type = true;
	}
	if(count == be_){
	  has_op_type = false;
	}

	//String-Guard
	if(has_op_type == false){
         if(strcmp(pitt_words,"//") == 0){
	    com_enab = true;
	    has_op_type = true;
	    break;
	  }
	
	 else if(isNumber(pitt_words) == 1){
	  pitt_pairs[pair_trace].opType = OP_PUSHABLE;
	  pitt_pairs[pair_trace].val = atoi(pitt_words);
	  pitt_pairs[pair_trace].line = lines;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	
	//macro
	else if(strcmp(pitt_words,macro)==0){
	  pitt_pairs[pair_trace].opType = MACRO;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,proc)==0){
	  pitt_pairs[pair_trace].opType = BLOCK_PROC;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,__max)==0){
	  pitt_pairs[pair_trace].opType = MAX;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,offset) == 0){
	  pitt_pairs[pair_trace].opType = OFFSET;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,str_char)==0){
	  pitt_pairs[pair_trace].opType = OP_STRCHAR;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,__min)==0){
	  pitt_pairs[pair_trace].opType = MIN;
	  pitt_pairs[pair_trace].line = lines;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,sof)==0){
	  pitt_pairs[pair_trace].opType = OP_SIZEOF;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,ptr_of)==0){
	  pitt_pairs[pair_trace].opType = OP_PTROF;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	
	else if(strcmp(pitt_words,inc)==0){
	  pitt_pairs[pair_trace].opType = KW_INCLUDE;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].toInclude = true;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,ex_it)==0){
	  pitt_pairs[pair_trace].opType = KW_EXIT;
	  pitt_pairs[pair_trace].line = lines;
	  pitt_pairs[pair_trace].toInclude = true;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,pstrlen)==0){
	  pitt_pairs[pair_trace].opType = PSTRLEN;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,store_int) == 0){
	  pitt_pairs[pair_trace].opType = STORE_INT;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,load_int) == 0){
	  pitt_pairs[pair_trace].opType = LOAD_INT;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,put__c)==0){
	  pitt_pairs[pair_trace].opType = PUTCHAR;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,__arg_count)==0){
	  pitt_pairs[pair_trace].opType = ARGC;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,load8)==0){
	  pitt_pairs[pair_trace].opType = INTRINSIC_LOAD8;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,store8)==0){
	  pitt_pairs[pair_trace].opType = INTRINSIC_STORE8;
	  pitt_pairs[pair_trace].line = lines;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,TO__INT)==0){
	  pitt_pairs[pair_trace].opType = INTRINSIC_TOINT;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,syscall1)==0){
	  pitt_pairs[pair_trace].opType = SYSCALL1;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,dup)==0){
	  pitt_pairs[pair_trace].opType = OP_DUP;
	  // pitt_pairs[pair_trace].col = cols;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,mem)==0){
	  pitt_pairs[pair_trace].opType = OP_MEM;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,mod)==0){

	  pitt_pairs[pair_trace].opType = OP_MOD;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,mem_all)==0){
	  pitt_pairs[pair_trace].opType = INTRINSIC_MEMORY;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	
	else if(strcmp(pitt_words,block_if)==0){
	  pitt_pairs[pair_trace].opType = OP_IF;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  //pitt_pairs[pair_trace].col = cols;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,typeAnd)==0){
	  pitt_pairs[pair_trace].opType = OP_AND;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,bind) == 0){
	  pitt_pairs[pair_trace].opType = IN_BIND;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,block_else)==0){
	  pitt_pairs[pair_trace].opType = OP_ELSE;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,divmod)==0){
	  pitt_pairs[pair_trace].opType = OP_EDIV;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,cstr_dp)==0){
	  pitt_pairs[pair_trace].opType = OP_CSTRDUP;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,block_elif)==0){
	  pitt_pairs[pair_trace].opType = OP_ELIF;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	 else if(strcmp(pitt_words,pint) == 0){
	  pitt_pairs[pair_trace].opType = P_TYPE_INT;
	  pitt_pairs[pair_trace].val = P_TYPE_INT;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	 else if(strcmp(pitt_words,pstr) == 0){
	  pitt_pairs[pair_trace].opType = P_TYPE_STR;
	  pitt_pairs[pair_trace].val = P_TYPE_STR;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	 else if(strcmp(pitt_words,pptr) == 0){
	   pitt_pairs[pair_trace].opType = P_TYPE_PTR;
	   pitt_pairs[pair_trace].val = P_TYPE_PTR;
	   pitt_pairs[pair_trace].line = lines;
	   pair_trace += 1;
	   has_op_type = true;
	 }
	
	else if(strcmp(pitt_words,cstr_to_pstr)==0){
	  pitt_pairs[pair_trace].opType = CSTR_TO_PSTR;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,block_end)==0){
	  pitt_pairs[pair_trace].opType = OP_END;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
        else if(strcmp(pitt_words,drop)==0){
	  pitt_pairs[pair_trace].opType = OP_DROP;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,str_drop)==0){
	  pitt_pairs[pair_trace].opType = STR_DROP;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,rot)==0){
	  pitt_pairs[pair_trace].opType = OP_ROT;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,over)==0){
	  pitt_pairs[pair_trace].opType = OP_OVER;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	

	else if(strcmp(pitt_words,block_while)==0){
     	  pitt_pairs[pair_trace].opType = OP_WHILE;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,pstrcmp)==0){
	  pitt_pairs[pair_trace].opType = PSTRCMP;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	
	else if(strcmp(pitt_words,typeread)==0){
	  pitt_pairs[pair_trace].opType = READ;
	  pitt_pairs[pair_trace].line = lines;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,typestdin)==0){
	  pitt_pairs[pair_trace].opType = PROC_STDIN;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,typestdout)==0){
	  pitt_pairs[pair_trace].opType = PROC_STDOUT;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,fp__) == 0){
	  pitt_pairs[pair_trace].opType = FPUT;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,typestderr) == 0){
	  pitt_pairs[pair_trace].opType = STDERR;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	
	
	else if(strcmp(pitt_words,block_do)==0){
	  pitt_pairs[pair_trace].opType = OP_DO;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}


	else if(strcmp(pitt_words,write)==0){
	  pitt_pairs[pair_trace].opType = OP_WRITE;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,store16)==0){
	  pitt_pairs[pair_trace].opType = INTRINSIC_STORE16;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,load16)==0){
	  pitt_pairs[pair_trace].opType = INTRINSIC_LOAD16;
	  pitt_pairs[pair_trace].line = lines;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,bor) == 0){
	  pitt_pairs[pair_trace].opType = OP_BOR;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}

	else if(strcmp(pitt_words,shl)==0){
	  pitt_pairs[pair_trace].opType = OP_SHL;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,typeOr)==0){
	  pitt_pairs[pair_trace].opType = OP_OR;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,shr)==0){
	  pitt_pairs[pair_trace].opType = OP_SHR;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}

	else if(strcmp(pitt_words,band) == 0){
	  pitt_pairs[pair_trace].opType = OP_BAND;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}

	else if(strcmp(pitt_words,xor) == 0){
	  pitt_pairs[pair_trace].opType = OP_XOR;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
        else if(strcmp(pitt_words,swap) == 0){
	  pitt_pairs[pair_trace].opType = OP_SWAP;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,putz) == 0){
	  pitt_pairs[pair_trace].opType = OP_PUTS;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,__arg_vect)==0){
	  pitt_pairs[pair_trace].opType = ARGV;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,syscall3) == 0){
	  pitt_pairs[pair_trace].opType = SYSCALL3;
	  pitt_pairs[pair_trace].val = 0;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}

	else if(is_id(pitt_words,lines,path) == true && has_op_type == false){
	   pitt_pairs[pair_trace].opType = IDENTIFIER;
	   pitt_pairs[pair_trace].val = 0;
	   pitt_pairs[pair_trace].line = lines;
	   char *n = (char*)malloc(sizeof(char)*strlen(pitt_words)+1);
	   for(int i2 = 0; i2 < strlen(pitt_words)+1; i2++){
	     n[i2] = pitt_words[i2];
	   }
	   n[strlen(n)] = '\0';
	   pitt_pairs[pair_trace].opStr = n;
	   //pitt_pairs[pair_trace].col = cols;
	   pair_trace += 1;
	   has_op_type = true;
	}
	 
	else if(strcmp(pitt_words,typeGE)==0){
	  pitt_pairs[pair_trace].opType = GE;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}

	else if(strcmp(pitt_words,typeLE)==0){
	  pitt_pairs[pair_trace].opType = LE;
	  pitt_pairs[pair_trace].line = lines;
	  //pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	else if(strcmp(pitt_words,typeNE)==0){
	  pitt_pairs[pair_trace].opType = NE;
	  pitt_pairs[pair_trace].line = lines;
	  // pitt_pairs[pair_trace].col = cols;
	  pair_trace += 1;
	  has_op_type = true;
	}
	
	// Checking Sign
	else if(has_op_type == false){
	for(int i = 0; i < strlen(pitt_words)+1; i++){
	  if(pitt_words[i] == typePlus){
	    pitt_pairs[pair_trace].opStr = pitt_words;
	    pitt_pairs[pair_trace].opType = OP_PLUS;
	    pitt_pairs[pair_trace].val = 0;
	    pitt_pairs[pair_trace].line = lines;
	    //pitt_pairs[pair_trace].col = cols;
	    pair_trace += 1;
            has_op_type = true;
	  }

	  else if(pitt_words[i] == typeLt){
	    pitt_pairs[pair_trace].opType = OP_LT;
	    pitt_pairs[pair_trace].val = 0;
	    pitt_pairs[pair_trace].line = lines;
	    //pitt_pairs[pair_trace].col = cols;
	    pair_trace += 1;
	    has_op_type = true;
	  }

	  else if(pitt_words[i] == typeMinus){
	    pitt_pairs[pair_trace].opType = OP_MINUS;
	    pitt_pairs[pair_trace].val = 0;
	    pitt_pairs[pair_trace].line = lines;
	    //pitt_pairs[pair_trace].col = cols;
	    pair_trace += 1;
	    has_op_type = true;
	  }

	  else if(pitt_words[i] == typeDiv){
	    pitt_pairs[pair_trace].opType = OP_DIV;
	    pitt_pairs[pair_trace].val = 0;
	    pitt_pairs[pair_trace].line = lines;
	    //pitt_pairs[pair_trace].col = cols;
	    pair_trace += 1;
	    has_op_type = true;
	  }

	  else if(pitt_words[i] == typeMul){
	    pitt_pairs[pair_trace].opType = OP_MUL;
	    pitt_pairs[pair_trace].val = 0;
	    pitt_pairs[pair_trace].line = lines;
	    //pitt_pairs[pair_trace].col = cols;
	    pair_trace += 1;
	    has_op_type = true;
	  }

	  else if(pitt_words[i] == typeDump){
	    pitt_pairs[pair_trace].opType = OP_DUMP;
	    pitt_pairs[pair_trace].val = 0;
	    pitt_pairs[pair_trace].line = lines;
	    //pitt_pairs[pair_trace].col = cols;
	    pair_trace += 1;
	    has_op_type = true;
	  }
	  else if(pitt_words[i] == typeLoad){
	    pitt_pairs[pair_trace].opType = OP_LOAD;
	    pitt_pairs[pair_trace].val = 0;
	    pitt_pairs[pair_trace].line = lines;
	    // pitt_pairs[pair_trace].col = cols;
	    pair_trace += 1;
	    has_op_type = true;
	  }
	  else if(pitt_words[i] == typeEqual){
	    pitt_pairs[pair_trace].opType = OP_EQUAL;
	    pitt_pairs[pair_trace].val = 0;
	    pitt_pairs[pair_trace].line = lines;
	    //pitt_pairs[pair_trace].col = cols;
	    pair_trace += 1;
	    has_op_type = true;
	  }
	  else if(pitt_words[i] == typeGt){
	    pitt_pairs[pair_trace].opType = OP_GT;
	    pitt_pairs[pair_trace].val = 0;
	    pitt_pairs[pair_trace].line = lines;
	    //pitt_pairs[pair_trace].col = cols;
	    pair_trace += 1;
	    has_op_type = true;
	  }
	}
	}

	if(has_op_type == false){
	  error_count += 1;
	  printf("%s:%d: PARSER: unexpected keyword `%s`\n",path,lines,pitt_words);
	}
     }
	//pitt_words = strtok(NULL," ");
	pitt_words = strtok(NULL,delim);
      }
    }
    
    return pitt_pairs;
}

// ------ Usage ------
void usage()
{
  printf("Usage: pitt <FILE> <COMMAND> <SUBCOMMAND> [ARGS]\n");
  printf("COMMANDS:\n");
  printf("     -s     Simulate the program\n");
  printf("     -d     Print the lexical analysis of the program file\n");
  printf("SUBCOMMANDS:\n");
  printf("     -T     Simulation time check\n");
  printf("     -S     Silent simulation INFO\n");
  exit(0);
}

int get_sz(struct ipair *dst,int ip){
  int sz = 0;
  int i  = 0;
 
  for(int i = 0; i <= ip; i++){
    if(dst[i].opType > 0 && dst[i].opType < 52){
      sz++;
    }   
  }

  return sz;
}

// main stack type-checking for safe code
void type_check_int(struct ipair *program,int program_counter,const char* filename)
{
  int stack[program_counter];
  int stack_push = -1;
  int stack_check = 0;

  for(int i = 0; i <= program_counter; i++){
    int typ = program[i].opType;

    if(typ > 0 && typ < 71){
      stack_check++;
    }

    if(typ == OP_PUSHABLE){
      stack_push += 1;
      stack[stack_push] = program[i].val;
    }
    else if(typ == OP_PLUS){
      if(stack_push >= 1){
	int a = stack[stack_push];
	stack_push -= 1;
	int b = stack[stack_push];
	stack_push -= 1;

	stack_push += 1;
	stack[stack_push] = a + b;
      }
      else if(stack_push < 1){
	printf("%s:%d: ERROR: found less arguments for PLUS operator\n",filename,program[i].line);
	error_count += 1;
      }
    }
    else if(typ == OP_MINUS){
      if(stack_push >= 1){
	int a = stack[stack_push];
	stack_push -= 1;
	int b = stack[stack_push];
	stack_push -= 1;

	stack_push += 1;
	stack[stack_push] = b - a;
      }
      else if(stack_push < 1){
	printf("%s:%d: ERROR: found less arguments for MINUS operator\n",filename,program[i].line);
	error_count += 1;
      }
    }
    else if(typ == OP_MUL){
      if(stack_push >= 1){
	int a = stack[stack_push];
	stack_push -= 1;
	int b = stack[stack_push];
	stack_push -= 1;

	stack_push += 1;
	stack[stack_push] = a * b;
      }
      else if(stack_push < 1){
	printf("%s:%d: ERROR: found less arguments for MUL operator\n",filename,program[i].line);
	error_count += 1;
      }
    }
    else if(typ == OP_DIV){
      if(stack_push >= 1){
	int a = stack[stack_push];
	stack_push -= 1;
	int b = stack[stack_push];
	stack_push -= 1;

	stack_push += 1;
	stack[stack_push] = b / a;
      }
      else if(stack_push < 1){
	printf("%s:%d: ERROR: found less arguments for DIV operator\n",filename,program[i].line);
	error_count += 1;
      }
    }
    else if(typ == OP_WRITE){
      if(stack_push >= 0){
        stack_push -= 1;
      }
      else if(stack_push < 0){
	printf("%s:%d: ERROR: found less arguments for PRINT intrinsic\n",filename,program[i].line);
	error_count += 1;
      }
    }
    else if(typ == OP_DUP){
      if(stack_push >= 0){
        int a = stack[stack_push];
	stack_push += 1;
	stack[stack_push] = a;
      }
      else if(stack_push < 0){
	printf("%s:%d: ERROR: found less arguments for DUP intrinsic\n",filename,program[i].line);
	error_count += 1;
      }
    }
    else if(typ == SYSCALL3){
      if(stack_push >= 3){
        stack_push -= 4;
      }
      else if(stack_push < 3){
	printf("%s:%d: ERROR: found less arguments for SYS3 call\n",filename,program[i].line);
	error_count += 1;
      }
    }
    else if(typ == INTRINSIC_STORE8){
      if(stack_push >= 1){
	stack_push -= 2;
      }
      else if(stack_push < 1){
	printf("%s:%d: ERROR: found less arguments for STORE8 intrinsic\n",filename,program[i].line);
      }
    }
    else if(typ == INTRINSIC_LOAD8){
      if(stack_push >= 0){
	stack_push -= 1;
      }
      else if(stack_push < 0){
	printf("%s:%d: ERROR: found less arguments for LOAD8 intrinsic\n",filename,program[i].line);
      }
    }
    else if(typ == SYSCALL1){
      if(stack_push >= 1){
	stack_push -= 1;
      }
      else if(stack_push < 1){
	printf("%s:%d: ERROR: found less arguments for SYS1 call\n",filename,program[i].line);
	error_count += 1;
      }
    }
    else if(typ == OP_MOD){
      if(stack_push >= 1){
	int a = stack[stack_push];
	stack_push -= 1;
	int b = stack[stack_push];
	stack_push -= 1;

	stack_push += 1;
	stack[stack_push] =  b % a;
      }
      else if(stack_push < 1){
	printf("%s:%d: ERROR: found less arguments for MOD operator\n",filename,program[i].line);
	error_count += 1;
      }
    }
    else if(typ == OP_OVER){
      if(stack_push >= 1){
	int a = stack[stack_push-1];
	stack_push += 1;
        stack[stack_push] = a;
      }
      else if(stack_push < 1){
	printf("%s:%d: ERROR: found less arguments for OVER intrinsic\n",filename,program[i].line);
	error_count += 1;
      }
    }
    else if(typ == OP_DROP){
      if(stack_push >= 0){
        stack_push -= 1;
      }
      else if(stack_push < 0){
	printf("%s:%d: ERROR: found less arguments for DROP intrinsic\n",filename,program[i].line);
	error_count += 1;
      }
    }
    
  }
  // There could be data left on the stack its not an error
  /*
  if(stack_push > -1){
    printf("%s:%d: ERROR: found unhandled data on the stack\n",filename,program[stack_check].line); 
  }
  */
}

// TODO: workleft
struct ipair* merge(struct ipair* dst,struct ipair *src,int p1,int p2,int current_board_index){
  dst[current_board_index].opType = -1;
  
  int sz = get_sz(dst,p1);
  int sz2 = 0;

  for(int i = 0;i <= p2; i++){
    if(src[i].opType > 0 && src[i].opType < 52){
      sz2++;
    }
  }
  sz2 = p2;
  //printf("%d and %d\n",sz,sz2);

  struct ipair* p = (struct ipair*)malloc(sizeof(struct ipair)*(p1+p2+1+1));
  
  memcpy(p,src,(sz2)*sizeof(struct ipair));
  memcpy((p+sz2),dst,(p1+1)*sizeof(struct ipair));

  /*
  free(dst);
  dst = (struct ipair*)malloc(sizeof(struct ipair)*(sz+sz2));
  
  memcpy(dst,p,(sz+sz2+2)*sizeof(struct ipair));
  */

  /*
  for(int i = 0; i < sz+sz2+2; i++)
    printf("TYPE %d\n",p[i].opType);
  */
  return p;
}


/*
// Backup Code (CONTRIBUTOR :- TopchetoEU)
struct ipair* merge(struct ipair* first, struct ipair *second, int firstN, int secondN) {
    struct ipair* p = (struct ipair*)malloc(sizeof(struct ipair) * (firstN + secondN));

    int sizeFirst = firstN * sizeof(struct ipair);
    int sizeSecond = secondN * sizeof(struct ipair);

    memcpy(p, first, sizeFirst);
    memcpy(p + sizeFirst, second, sizeSecond);

    memcpy(first,p,sizeFirst+sizeSecond);

    return p;
}
*/

// 0 is a valid place for mem stack unless 0 is booked
// ------ Simulate Program ------
void simulate(struct ipair *program,int program_counter,const char* filename,int argc,char **argv)
{
  //match_reference(program,0,program_counter);
  if(error_count > 0){
    //printf("[SIM] found errors while simulating program\n");
    // printf("[SIM] simulation terminated abnormally\n");
    exit(0);
  }

  //Argc & Argv
  int actual_argc = argc-3; // removing `pitt` `sim` `filename`
  char *actual_argv[actual_argc];
  int aargv = 0;
  for(int i2 = 3;i2 < argc; i2++){
    actual_argv[aargv] = argv[i2];
    aargv++;
  }
  
  // Base stack
  int stack[program_counter];
  int stack_push = -1;

  // If else end 
  int else_count = 0; // (I think this 1 is not needed)
  int if_ip[program_counter];
  int if_push = -1;
  int else_ip[program_counter];
  int else_push = -1;

  //While stack
  int while_count = 0;
  int while_ip[program_counter];
  int while_push = -1;
  int while_condition[program_counter];  
  int block_if_pushes = 0;

  // Macro Location
  int loc[program_counter];
  int loc_push = -1;
  int rt = 0;

  // String C-Like
  char *str_stack[program_counter];
  int str_push = -1;

  // Memory
  int ARGV_EXTENTION = argc;
  byte mem_stack[STR_CAP + MEM_CAP + ARGV_EXTENTION + MEMORY_HEAP_CAP];
  
  // Macro
  char *macro_def[program_counter];
  int macro_def_push = -1;
  int macro_line[program_counter];
  int left_mac[program_counter];
  int lm = -1;
  int mac_is_in[program_counter];
  int mii = -1;

  int mac_loc[program_counter];
  int mlp = -1;

  // Unused variables set
  int offset_loc[program_counter];
  int off_push = -1;

  //Memory stack
  int memory_heap = 0;
  int memory_begining[program_counter]; // points towards the beginning of the memory on the mem stack
  char *memory_name[program_counter]; // points the name of memory region
  int memory_offset[program_counter]; // points towards the end position of the memory
  int memory_size[program_counter]; // used for sizeof memory keyword
  int memory_pointer[program_counter];
  int memory_push = -1;
  int memory_loc[program_counter];
  // Procceses
  char *proc_stack[program_counter];
  int proc_push = -1;

  // Bind
  struct binding *bstack = (struct binding*)malloc(sizeof(struct binding)*program_counter);
  int bpush = -1;

  int ip = 0;
  for(int i = 0; i <= program_counter; i++){
    ip += 1;


    
    // TODOOOOOOOOOOOOOOOOOOOOO: Fix its faulty ness
    if(program[i].opType == KW_INCLUDE){
      if(program[i].toInclude == true){
      char *file11 = str_stack[str_push];
      str_push -= 1;

      FILE *prog = fopen(file11,"r");

      char *tmp_buf = (char*)malloc(sizeof(char)*256);
      
      int words = 0;

      while(fgets(tmp_buf,256,prog)){
	char *word_c_c = strtok(tmp_buf," ");
	while(word_c_c != NULL){
	  word_c_c = strtok(NULL," ");
	  words++;
	}
      }
      //printf("WORDS %d\n",words);

      struct ipair *__inc = load_program_from_file(file11);
      program = merge(program,__inc,program_counter,words,i);
      
      i = 0;
      program[i].toInclude = false;
      program_counter += words;
      }
   }
    



    
  
    
    if(program[i].opType == IDENTIFIER){
      int go_ = i;
      int is_valid = false;
      
      for(int i2 = 0; i2 < macro_def_push+1; i2++){
	char *tmp = program[i].opStr;
	if(strcmp(tmp,macro_def[i2]) == 0){
	  go_ = macro_line[i2];
	  lm += 1;
          left_mac[lm] = i;
          mii += 1;
          mac_is_in[mii] = true;
          loc_push += 1;
          loc[loc_push] = IDENTIFIER;
	  i = go_ - 1;
	  is_valid = true;
	  break;
	}
      }

      for(int i3 = 0; i3 <= memory_push; i3++){
	char *tmp = program[i].opStr;
	if(strcmp(tmp,memory_name[i3]) == 0){
	  int beg_of_thisreg = memory_begining[i3];
	  int end_ptr = memory_pointer[i3];
	  
	  //stack_push += 1;
	  //stack[stack_push] = beg_of_thisreg;
	  //stack_push += 1;
	  //xstack[stack_push] = end_ptr;
	  
	  if(program[i-1].opType == OP_PUSH_STR){
	    char *str_ptr = str_stack[str_push];
	    str_push -= 1;
	    int tx = 0;
	    for(int i4 = beg_of_thisreg; i4 < end_ptr; i4++){
	      //mem_stack[i4] = program[i-1].opStr[i4];
	      mem_stack[i4] = str_ptr[tx];
	      tx++;
	    }
	  }
	  else if(program[i-1].opType == OP_PUSHABLE){
	    int tval = program[i-1].val;
	    if(tval >= -128 && tval <= 127){
	      mem_stack[beg_of_thisreg] = tval;
	    }
	    else{
	      for(int i4 = beg_of_thisreg; i4 < end_ptr; i4++){
		if(tval > 127){
		  mem_stack[i4] = 127;
		  tval -= 127;

		  if(tval < 127){
		    mem_stack[i4] = tval;
		    break;
		  }
		}
	      }
	    }
	  }
	  
      
	  is_valid = true;
	  break;
	  }
	}

      if(is_valid == false){
	char *tmp = program[i].opStr;
	for(int i2 = 0; i2 <= bpush; i2++){
	  if(strcmp(bstack[i2].bind_name,tmp) == 0){
	    if(bstack[i2].type == OP_PUSHABLE){
	      stack_push += 1;
	      stack[stack_push] = bstack[i2].bind_val1;
	      is_valid = true;
	      break;
	    }
	    else if(bstack[i2].type == OP_PUSH_STR){
	      str_push += 1;
	      str_stack[str_push] = bstack[i2].bind_val2;
	      is_valid = true;
	      break;
	    }
	  }
	}
      }
    
      
      if(is_valid == false){
	printf("%s:%d: ERROR: invalid identifier found `%s`\n",filename,program[i].line,program[i].opStr);
	/*
	for(int i2 = 0; program[i].opStr[i2] != '\0'; i2++){
	  if(program[i].opStr[i2] == 'p' && program[i].opStr[i2+1] == 'u'){
	    printf("%s:%d: NOTE: intrinsics by name `puts` `putchar`\n",filename,program[i].line);
	    break;
	  }
	}
	*/
	printf("simulation terminated abnormally\n");
	exit(0);
      }      
    }
    
    if(program[i].opType == OP_PUSHABLE){
      stack_push += 1;
      stack[stack_push] = program[i].val;
    }

    
    else if(program[i].opType == IN_BIND){
      if(program[i+1].opType != IDENTIFIER){
	printf("%s:%d: ERROR: expected an identifier as bind name but found ",filename,program[i+1].line);
	human_readable_type(program[i+1].opType);
	printf("simulation terminated abnormally\n");
	exit(0);
      }
      char *n = program[i+1].opStr;
      int type = program[i-1].opType;


      if(type == P_TYPE_INT){
	int re_bind = false;
	for(int i2 = 0; i2 <= bpush; i2++){
	  if(strcmp(bstack[i2].bind_name,n) == 0){
	    bstack[i2].bind_val1 = stack[stack_push];
	    bstack[i2].type = OP_PUSHABLE;
	    stack_push -= 1;
	    re_bind = true;
	    break;
	  }
	}
	if(re_bind == false){
	  bpush += 1;
	  bstack[bpush].bind_val1 = stack[stack_push];
	  bstack[bpush].type = OP_PUSHABLE;
	  bstack[bpush].bind_name = n;
	  stack_push -= 1;
	}
	
      }
      else if(type == P_TYPE_STR){
	int re_bind = false;
	for(int i2 = 0; i2 <= bpush; i2++){
	  if(strcmp(bstack[i2].bind_name,n) == 0){
	    bstack[i2].bind_val2 = str_stack[str_push];
	    str_push -= 1;
	    bstack[i2].type = OP_PUSH_STR;
	    re_bind = true;
	    break;
	  }
	}
	if(re_bind == false){
	  bpush += 1;
	  bstack[bpush].bind_val2 = str_stack[str_push];
	  bstack[bpush].type = OP_PUSH_STR;
	  bstack[bpush].bind_name = n;
	  str_push -= 1;
	}
      }
      
      //TODOOOOOOOOOO: This could be an Warning just
      else {
	printf("%s:%d: ERROR: expected a data type to bind",filename,program[i].line);
	printf("but found ");
	human_readable_type(program[i-1].opType);
	printf("\n");
	printf("simulation terminated abnormally\n");
	exit(0);
      }
      i += 1;
    }
    
    //TODO: Underwork Portion
    else if(program[i].opType == INTRINSIC_STORE16){
      int index = stack[stack_push];
      stack_push -= 1;
      int byte_val = stack[stack_push];
      stack_push -= 1;

      if(index > memory_heap){
       if((byte_val > 32767 || byte_val < -32768)){
        continue;
      }
      else if(byte_val < 127){
	mem_stack[index] = byte_val;
      }
      else if(byte_val > 127){
	while(byte_val > 127){
	  byte_val -= 127;
	  index += 1;
	  mem_stack[index] = 127;
	  
	  if(byte_val <= 127){
	    index += 1;
	    mem_stack[index] = byte_val;
	  }
	}
      }
      }
      stack_push += 1;
      stack[stack_push] = index; // Pushes the 16 byte memory ending
    }
    else if(program[i].opType == STDERR){
      stack_push += 1;
      stack[stack_push] = STDERR;
    }
    else if(program[i].opType == FPUT){
      int buf = stack[stack_push];
      stack_push -= 1;

      // PROC_STDOUT and not PROC_STDERR: keep in mind both of them are proccess associated with your program when calling them
      if(buf == STDERR){
        char *msg = str_stack[str_push];
	str_push -= 1;
	fprintf(stderr,msg);
      }
      else if(buf == PROC_STDOUT){
	char *msg = str_stack[str_push];
	str_push -= 1;
	fprintf(stdout,msg);
      }
      else{
	printf("%s:%d: ERROR: invalid fput file descripter type\n",filename,program[i].line);
	printf("simulation terminated abnormally\n");
	exit(0);
      }
    }
    else if(program[i].opType == INTRINSIC_LOAD16){
      int place_ptrt1 = stack[stack_push];
      stack_push -= 1;
      int place_ptr2 = stack[stack_push];
      stack_push -= 1;

      int data = 0;
      int toadd = 0;
      
      for(int i2 = place_ptrt1;i2 <= place_ptrt1+place_ptr2; i2++){
	data += mem_stack[i2];
      }
      if(data > 127){
	//data += 1; // Padding for over 8 bit memories
      }

      stack_push += 1;
      stack[stack_push] = data;
    }
    // `mem`
    else if(program[i].opType == OP_MEM){
      int value = stack[stack_push];
      stack_push -= 1;
      int index = stack[stack_push];
      stack_push -= 1;
      
      mem_stack[index] = value;
    }
    //Needs an improvised version
    else if(program[i].opType == PUTCHAR){
      int place_ptr = stack[stack_push];
      stack_push -= 1;
      //stack_push += 1;
      stack[stack_push] = str_stack[str_push][place_ptr];
      
      printf("%c",stack[stack_push]);
    }
    else if(program[i].opType == OP_DROP){
      stack_push -= 1;
    }
    // TODOOOOOOOO: Fix the glitch in  it
    else if(program[i].opType == STORE_INT){
      int index = stack[stack_push];
      stack_push -= 1;
      int byte32_for = stack[stack_push];
      stack_push -= 1;
      
      stack[index] = byte32_for;
    }
    else if(program[i].opType == LOAD_INT){
      int index = stack[stack_push];
      stack_push -= 1;
      stack_push += 1;
      stack[stack_push] = stack[index];
    }
    else if(program[i].opType == OP_OVER){
      int a = stack[stack_push-1];
      stack_push += 1;
      stack[stack_push] = a;
    }

    //TODO
    else if(program[i].opType == INTRINSIC_MEMORY){
      int eb = find_end_block(program,i+1,program_counter);

      if(eb == -1){
	printf("%s:%d: ERROR: expected an end of memory region\n",filename,program[i].line);
	printf("simulation terminated abnormally\n");
	exit(0);
      }

      if(program[i+1].opType != IDENTIFIER){
	printf("%s:%d: ERROR: expected identifier of this memory region but found ",filename,program[i+1].line);
	human_readable_type(program[i+1].opType);
	printf("simulation terminated abnormally\n");
	exit(0);
      }

      for(int i2 = 0; i2 <= memory_push; i2++){
	if(strcmp(memory_name[i2],program[i+1].opStr) == 0){
	  printf("%s:%d: ERROR: redifinition of memory region %s\n",filename,program[i+1].line,memory_name[i2]);
	  printf("%s:%d: NOTE: here is the actual definition\n",filename,memory_loc[i2]);
	  printf("simulation terminated abnormally\n");
	  exit(0);
	}
      }
      
      loc_push += 1;
      loc[loc_push] = INTRINSIC_MEMORY;

      memory_push += 1;
      memory_begining[memory_push] = memory_heap;
      memory_name[memory_push] = program[i+1].opStr;
      memory_loc[memory_push] = program[i+1].line;
      i += 1;
    }

    
    else if(program[i].opType == OP_ROT){
      int c = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1; // a b c -- b c a
      int a = stack[stack_push];
      stack_push -= 1;

      stack[stack_push] = a;
      stack_push += 1;
      stack[stack_push] = c;
      stack_push += 1;
      stack[stack_push] = b;
    }
    else if(program[i].opType == STR_DROP){
      str_push -= 1;
    }
	
    if(program[i].opType == MACRO){
      bool isValid = true;
      if(program[i+1].opType == IDENTIFIER){
	for(int i2 = 0; i2 <= macro_def_push; i2++){
	  if(strcmp(program[i+1].opStr,macro_def[i2])==0){
	    printf("%s:%d: ERROR: redefinition of macro\n",filename,program[i+1].line);
	    printf("%s:%d: NOTE: here is the actual definition\n",filename,mac_loc[i2]);
	    printf("simulation terminated abnormally\n");
	    isValid = false;
	    exit(0);
	  }
	}
	
	macro_def_push += 1;
	macro_def[macro_def_push] = program[i+1].opStr;
	mac_loc[macro_def_push] = program[i+1].line;
	int eb = find_end_block(program,i+1,program_counter);
	if(eb == -1){
	  printf("%s:%d: ERROR: expected an end of `%s` macro definition\n",filename,program[i+1].line,program[i+1].opStr);
	  printf("simulation terminated abnormally\n");
	  exit(0);
	}
	macro_line[macro_def_push] = i+2;
	i = eb;
 	loc_push += 1;
	loc[loc_push] = IDENTIFIER; //loc[loc_push] = IDENTIFIER;
      }

      else if(program[i+1].opType != IDENTIFIER){
	printf("%s:%d: ERROR: expected an identifier for macro definition but found an intrinsic\n",filename,program[i+1].line);
	printf("%s:%d: NOTE: readable name ",filename,program[i+1].line);
	human_readable_type(program[i+1].opType);
	printf("\n");
	printf("simulation terminated abnormally\n");
	exit(0);
      }
    }

    
    else if(program[i].opType == OP_SIZEOF){
      int yes  = false;
      if(program[i+1].opType == IDENTIFIER){
	for(int i2 = 0; i2 <= memory_push; i2++){
	  if(strcmp(memory_name[i2],program[i+1].opStr) == 0){
	    stack_push += 1;
	    stack[stack_push] = memory_size[i2];
	    yes = true;
	    break;
	  }
	}
	if(yes == false){
	  printf("%s:%d: %s not found in memory\n",filename,program[i+1].line,program[i+1].opStr);
	}
      }
      else{
	printf("%s:%d expected an identifier but found ",filename,program[i+1].line);
	human_readable_type(program[i+1].opType);
	printf("simulation terminated abnormally\n");
	exit(0);
      }
       i += 1;
      
    }
    else if(program[i].opType == OP_PTROF){
      int yes  = false;
      if(program[i+1].opType == IDENTIFIER){
	for(int i2 = 0; i2 <= memory_push; i2++){
	  if(strcmp(memory_name[i2],program[i+1].opStr) == 0){
	    stack_push += 1;
	    stack[stack_push] = memory_begining[i2];
	    yes = true;
	    break;
	  }
	}
	if(yes == false){
	  printf("%s:%d: %s not found in memory\n",filename,program[i+1].line,program[i+1].opStr);
	}
      }
      else{
	printf("%s:%d expected an identifier but found ",filename,program[i+1].line);
	human_readable_type(program[i+1].opType);
	printf("simulation terminated abnormally\n");
	exit(0);
      }
       i += 1;
      
    }
    // TODO: OP_LOAD should push the integer value of the character on the top of the stack
    else if(program[i].opType == OP_LOAD){
      int index = stack[stack_push];
      stack_push -= 1;
      printf("%c",mem_stack[index]);
    }
    // For now simple program stack offset
    // TODOOOOOOOOOOOO: Make better offset for all kind of stack
    else if(program[i].opType == OFFSET){
      off_push += 1;
      int typ = program[i-1].opType;
      if(typ == P_TYPE_INT || typ == P_TYPE_STR || typ == P_TYPE_PTR){
         offset_loc[off_push] = program[i-1].opType;
      }
      else{
	printf("%s:%d: ERROR: invalid stack type mentioned to offset ",filename,program[i-1].line);
	human_readable_type(typ);
	printf("\n");
	printf("simulatation terminated abnormally\n");
	exit(0);
      }

      loc_push += 1;
      loc[loc_push] = OFFSET;
    }
    else if(program[i].opType == OP_OR){
      int top_1 = stack[stack_push];
      stack_push -= 1;
      int top_2 = stack[stack_push];
      stack_push -= 1;

      if(top_1 == true || top_2 == true){
	stack_push += 1;
	stack[stack_push] = true;
      }
      else{
	stack_push += 1;
	stack[stack_push] = false;
      }
    }
    else if(program[i].opType == SYSCALL1){
      int ptr = stack[stack_push];
      stack_push -= 1;

      printf("%c",mem_stack[ptr]);
    }
    
    else if(program[i].opType == PROC_STDIN){
      stack_push += 1;
      stack[stack_push] = PROC_STDIN;
    }
    else if(program[i].opType == PROC_STDOUT){
      stack_push += 1;
      stack[stack_push] = PROC_STDOUT;
    }

    else if(program[i].opType == READ){
      int fd = stack[stack_push];
      stack_push -= 1;
      int buffer = stack[stack_push];
      stack_push -= 1;

      if(fd != PROC_STDIN){
	printf("%s:%d: ASSERTION ERROR: (read syscall) expected the file descriptor to be stdin\n",filename,program[i].line);
	exit(0);
      }

      if(fd == PROC_STDIN){
	char buf[buffer];
        fgets(buf,buffer,stdin);
	str_push += 1;
	str_stack[str_push] = buf;
      }
    }
    // ---------------
    
    else if(program[i].opType == OP_AND){
      int top_1 = stack[stack_push];
      stack_push -= 1;
      int top_2 = stack[stack_push];
      stack_push -= 1;

      if(top_1 == true && top_2 == true){
	stack_push += 1;
	stack[stack_push] = true;
      }
      else{
	stack_push += 1;
	stack[stack_push] = false;
      }
    }
    else if(program[i].opType == PSTRLEN){
      char *str = str_stack[str_push];
      str_push -= 1;

      int len = strlen(str);
      stack_push += 1;
      stack[stack_push] = len;
    }
    else if(program[i].opType == SYSCALL3){
      int syscall_number = stack[stack_push];
      stack_push -= 1;

      int arg1 = stack[stack_push];
      stack_push -= 1;
      int arg2 = stack[stack_push];
      stack_push -= 1;
      int arg3 = stack[stack_push];
      stack_push -= 1;

      if(syscall_number == 1){
	if(arg1 == 1){
	 for(int i2 = arg2; i2 < arg2+arg3; i2++){
	   printf("%c",mem_stack[i2]);
         }
	}
	else if(arg1 == 2){
	  for(int i2 = arg2; i2 < arg2+arg3; i2++){
	    fprintf(stderr,"%c",mem_stack[i2]);
	  }
	}
	else{
	  printf("%s:%d: ERROR: unknown file descriptor %d\n",filename,program[i].line,arg1);
	  printf("simulation terminated abnormally\n");
	  exit(0);
	}
      }
      else{
	printf("%s:%d: ERROR: unknown syscall number %d\n",filename,program[i].line,syscall_number);
	printf("simulation terminated abnormally\n");
	exit(0);
      }
      
    }

    else if(program[i].opType == OP_PLUS){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;
      
      stack_push += 1;
      stack[stack_push] = a + b;
      //printf("%d\n",stack[stack_push]);      
    }
    else if(program[i].opType == MIN){
      int a = stack[stack_push];
      stack_push -= 1;
      int b =  stack[stack_push];
      stack_push -= 1;

      stack_push += 1;

      if(a < b){
	stack_push += 1;
	stack[stack_push] = a;
      }
      else if(b < a){
	stack_push += 1;
	stack[stack_push] = b;
      }
    }
    else if(program[i].opType == OP_STRCHAR){
      int ptr = stack[stack_push];
      stack_push -= 1;

      stack_push += 1;
      stack[stack_push] = str_stack[str_push][ptr];
    }
    else if(program[i].opType == MAX){
      int a = stack[stack_push];
      stack_push -= 1;
      int b =  stack[stack_push];
      stack_push -= 1;

      stack_push += 1;

      if(a > b){
	stack_push += 1;
	stack[stack_push] = a;
      }
      else if(b > a){
	stack_push += 1;
	stack[stack_push] = b;
      }
    }
    

    else if(program[i].opType == OP_DUP){
      int a = stack[stack_push];
      stack_push += 1;
      stack[stack_push] = a;
      //printf("%d\n",a);
    }
    else if(program[i].opType == CSTR_TO_PSTR){
      int beginning_of_memory = stack[stack_push];
      stack_push -= 1;
      char *string = str_stack[str_push];
      str_push -= 1;
      
      int len_of_str = strlen(string);

      stack_push += 1;
      stack[stack_push] = beginning_of_memory;
      
      stack_push += 1;
      stack[stack_push] = len_of_str;

      if((beginning_of_memory + len_of_str) > (MEM_CAP + STR_CAP + ARGV_EXTENTION)){
	printf("%s:%d: ERROR: string is bigger than expected memory stack overflow detected\n",filename,program[i].line);
	printf("simulation terminated abnormally\n");
	exit(0);
      }
      
      //TODO: utf-8 decoding (\n \t \n) etc
      if(beginning_of_memory > memory_heap){
      int tx = 0;
      for(int i2 = beginning_of_memory; i2 < beginning_of_memory+len_of_str; i2++){
	 mem_stack[i2] = string[tx];
	 tx++;
      }
      }
    }
    else if(program[i].opType == OP_MOD){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      stack_push += 1;
      stack[stack_push] = b % a; // 2 4 = 4 % 2
    }

    else if(program[i].opType == OP_MINUS){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;
      
      stack_push += 1;
      stack[stack_push] = b - a;
      //printf("%d\n",stack[stack_push]);      
    }
    else if(program[i].opType == PSTRCMP){
      char *f = str_stack[str_push];
      str_push -= 1;
      char *s = str_stack[str_push];
      str_push -= 1;

      if(strcmp(s,f)==0){
	stack_push += 1;
	stack[stack_push] = true;
      }
      else{
	stack_push += 1;
	stack[stack_push] = false;
      }
    }

    else if(program[i].opType == OP_MUL){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;
      
      stack_push += 1;
      stack[stack_push] = a * b;
      //printf("%d\n",stack[stack_push]);
      
    }
    else if(program[i].opType == OP_CSTRDUP){
      char *str = str_stack[str_push];
      str_push += 1;
      str_stack[str_push] = str;
    }

    else if(program[i].opType == OP_DIV){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;
      
      stack_push += 1;
      stack[stack_push] = b / a;
      //printf("%d\n",stack[stack_push]);     
    }
    else if(program[i].opType == ARGV){
      int argv_number = stack[stack_push];
      stack_push -= 1;
      str_push += 1;
      str_stack[str_push] = actual_argv[argv_number];
      //printf("%s",actual_argv[argv_number]);
    }

    else if(program[i].opType == OP_SWAP){ // 10 2
      int a = stack[stack_push]; // 2
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      stack_push += 1;
      stack[stack_push] = a;
      stack_push += 1;
      stack[stack_push] = b;
    }
    else if(program[i].opType == GE){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      if(b >= a){
	stack_push += 1;
	stack[stack_push] = true;
      }
      else{
	stack_push += 1;
	stack[stack_push] = false;
      }
    }
    else if(program[i].opType == LE){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      if(b <= a){
	stack_push += 1;
	stack[stack_push] = true;
      }
      else{
	stack_push += 1;
	stack[stack_push] = false;
      }
    }
    else if(program[i].opType == NE){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      if(b != a){
	stack_push += 1;
	stack[stack_push] = true;
      }
      else{
	stack_push += 1;
	stack[stack_push] = false;
      }
    }
    
    
    else if(program[i].opType == OP_BOR){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      stack_push += 1;
      stack[stack_push] = b | a;
    }

    else if(program[i].opType == OP_BAND){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      stack_push += 1;
      stack[stack_push] = b & a;
    }

    else if(program[i].opType == OP_XOR){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      stack_push += 1;
      stack[stack_push] = b ^ a;
    }

    else if(program[i].opType == OP_SHR){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      stack_push += 1;
      stack[stack_push] = b >> a;// 5 >> 24
    }
    
    else if(program[i].opType == OP_SHL){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      stack_push += 1;
      stack[stack_push] = b << a; // 5 << 24
    }
    else if(program[i].opType == KW_EXIT){
      int a = stack[stack_push];
      stack_push -= 1;

      exit(a);
    }
 
    else if(program[i].opType == OP_EQUAL){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      if(a == b){
        stack_push += 1;
        stack[stack_push] = true;
        //printf("%d\n",stack[stack_push]);
      }
      else{
	stack_push += 1;
	stack[stack_push] = false;
	//printf("%d\n",stack[stack_push]);
      }
    }

    else if(program[i].opType == OP_GT){
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      if(b > a){
	stack_push += 1;
	stack[stack_push] = true;
      }
      else{
	stack_push += 1;
	stack[stack_push] = false;
      }
    }
    else if(program[i].opType == INTRINSIC_TOINT){
      char *conv = str_stack[str_push];
      str_push -= 1;

      int to_int = atoi(conv);
      stack_push += 1;
      stack[stack_push] = to_int;
    }
    else if(program[i].opType == OP_LT){      
      int a = stack[stack_push];
      stack_push -= 1;
      int b = stack[stack_push];
      stack_push -= 1;

      if(b < a){
	stack_push += 1;
	stack[stack_push] = true;
      }
      else{
	stack_push += 1;
	stack[stack_push] = false;
      }
    }

    else if(program[i].opType == OP_WRITE){
       int a = stack[stack_push];
       printf("%d",a);
       stack_push -= 1;
    }
    else if(program[i].opType == OP_PUTS){
      char *str = str_stack[str_push];
      str_push -= 1;
      refine_and_print(str,filename,program[i].line);
    }
    else if(program[i].opType == INTRINSIC_STORE8){
      int place = stack[stack_push];
      stack_push -= 1;
      int byte__ = stack[stack_push];
      stack_push -= 1;
      if(place > memory_heap){
      if(byte__ > 127 || byte__ < -128){
	continue;
      }
      else{
        mem_stack[place] = byte__;
      }
      }
    }
    else if(program[i].opType == INTRINSIC_LOAD8){
      int place = stack[stack_push];
      stack_push -= 1;
      stack_push += 1;
      stack[stack_push] = mem_stack[place];
    }
    else if(program[i].opType == OP_EDIV){
      int item_b = stack[stack_push];
      stack_push -= 1;
      int item_a = stack[stack_push];
      stack_push -= 1;

      int r = item_a % item_b;
      stack_push += 1;
      stack[stack_push] = r;

      int d = item_a / item_b;
      stack_push += 1;
      stack[stack_push] = d;
    }
    
    else if(program[i].opType == OP_IF){
      block_if_pushes += 1;
      bool get_to_end = false;
      
      int a = stack[stack_push];
      int end_block = find_end_block(program,i,program_counter);
      int else_block = find_else_block(program,i+1,program_counter);
      int _find_next_if_block = find_if_block(program,i+1,program_counter);

      if(else_block != -1){
	else_push += 1;
	else_ip[else_push] = else_block;
      }
      if(else_block == -1){
	get_to_end = true;
      }

      else_push += 1;
      while(find_else_block(program,else_block+1,program_counter) != -1){
	else_block = find_else_block(program,else_block+1,program_counter);
        else_ip[else_push++] = else_block;
      }
     
      if(end_block == -1){
	printf("%s:%d: ERROR: `if` instruction does not have a reference to the end of its block use `end` to reference `if` to the end\n\n",filename,program[i].line);
	printf("simulation terminated abnormally\n");
	  exit(0);
	}

      loc_push += 1;
      loc[loc_push] = OP_IF;
      
      if(a == true && end_block != -1){
	if_push += 1;
	if_ip[if_push] = true;
      }
      else if(a == false && get_to_end == false){
	if_push += 1;
	if_ip[if_push] = false;
	i = else_ip[(else_push-block_if_pushes)];
      }
      else if(a == false && get_to_end == true){
	i = end_block;
      }

      //printf("if_ip - %d\n",if_ip[if_push]);
    }

    else if(program[i].opType == OP_ELSE){
      else_count += 1;
      
      int end_block = find_end_block(program,i,program_counter);

      if(end_block == -1){
	printf("%s:%d: ERROR: `else` instruction does not have a reference to the end of its block use `end` to reference `if` to the end\n\n",filename,program[i].line);
	printf("simulation terminated abnormally\n");
	  exit(0);
	}
      
      int a = if_ip[if_push];
      if_push -= 1;
      
      if(end_block != -1 && a == false){
	if_push += 1;
	if_ip[if_push] = true;
        continue;
      }
      if(a == true){
	i = end_block;
      }
      
    }

    
    else if(program[i].opType == OP_WHILE){
      while_push += 1;
      while_ip[while_push] = i;
      while_count += 1;
    }
    else if(program[i].opType == ARGC){
      stack_push += 1;
      stack[stack_push] = actual_argc;
    }
 
    else if(program[i].opType == OP_DO){
      loc_push += 1;
      loc[loc_push] = OP_WHILE;
       
      int end_block = find_end_block(program,i+1,program_counter);
      if(end_block == -1){
	printf("%s:%d: ERROR: `do` instruction does not have a reference to its end use `end` keyword to reference it\n\n",filename,program[i].line);
	printf("simulation terminated abnormally\n");
	exit(0);
      }

      int a = stack[stack_push];
      stack_push -= 1;
      
      if(a == true){
	while_condition[while_push] = true;
	//while_push += 1;
      }
      else if(a == false){
	while_condition[while_push] = false;
	while_count = -1;
	i = end_block;
      }
    }

    // Extreme glitchy
   else if(program[i].opType == OP_END){
      else_count = 0;
      bool wblock = false;
      int l = (loc_push > -1) ? loc[loc_push] : -1;

      if(l == OP_IF){
	loc[loc_push] = loc[loc_push-1];
	//printf("%d\n",i);
	//loc_push -= 1;
      } 

      else if(l == INTRINSIC_MEMORY){

	int a = stack[stack_push];
	stack_push -= 1;
	memory_heap += a;
	memory_offset[memory_push] = a;
	memory_pointer[memory_push] = memory_begining[memory_push] + a;
	memory_size[memory_push] = a;

	loc[loc_push] = loc[loc_push-1];
	
	//printf("INTRINS MEM\n");
      }

      else if(l == OFFSET){
	 loc[loc_push] = loc[loc_push - 1];
	 int typ = offset_loc[off_push];
	 off_push -= 1;

	 if(typ == P_TYPE_INT){
	   int off_val = stack[stack_push];
	   stack_push -= 1;
	   stack_push += off_val;
	 }
	 else if(typ == P_TYPE_STR){
	   int off_val = stack[stack_push];
	   stack_push -= 1;
	   str_push += off_val;
	 }
	 else if(typ == P_TYPE_PTR){
	   int off_val = stack[stack_push];
	   stack_push -= 1;
	   memory_heap += off_val;
	 }
      }
      
      else if(l == OP_WHILE){
	loc_push -= 1;
        if(while_condition[while_push] == true){
          i = while_ip[while_push];
	  wblock = true;
	  //loc_push -= 1;
        }
      }
      
      else if(l == IDENTIFIER){
	if(mac_is_in[mii] == true){
	   mii -= 1;
	   i = left_mac[lm];
	   lm -= 1;
	   loc_push -= 1;
        }
      }
      else{
	printf("%s:%d: ERROR: unexpected `end` of something\n",filename,program[i].line);
	printf("simulation terminated abnormally\n");
	exit(0);
      }
    }

    else if(program[i].opType == OP_PUSH_STR){
      str_push += 1;
      str_stack[str_push] = program[i].opStr;
    }
  }  
}

// -- TODO: Compiling Program --
void compile(struct ipair *program,char *output,int program_size)
{
  FILE *fp = fopen("output.asm","w");
  fprintf(fp,"segment .text\n");
  fprintf(fp,"dump:\n");
  fprintf(fp,"      movabs r9, -3689348814741910323\n");
  fprintf(fp,"      sub rsp, 40\n");
  fprintf(fp,"      mov BYTE PTR [rsp+31], 10\n");
  fprintf(fp,"      lea rcx,[rsp+30]\n");
  fprintf(fp,".L2:\n");
  fprintf(fp,"      mov rax, rdi\n");
  fprintf(fp,"      mov rsi, rdi\n");
  fprintf(fp,"      lea r8,[rsp+32]\n");
  fprintf(fp,"      mul r9\n");
  fprintf(fp,"      sub r8,rcx\n");
  fprintf(fp,"      shr rdx, 3\n");
  fprintf(fp,"      lea rax, [rdx+rdx*4]\n");
  fprintf(fp,"      add rax, rax\n");
  fprintf(fp,"      sub rsi, rax\n");
  fprintf(fp,"      mov rax, rdi\n");
  fprintf(fp,"      mov rdi, rdx\n");
  fprintf(fp,"      mov rdx, rcx\n");
  fprintf(fp,"      mov BYTE PTR [rcx], sil\n");
  fprintf(fp,"      sub rcx,1\n");
  fprintf(fp,"      cmp rax, 9\n");
  fprintf(fp,"      ja   .L2\n");
  fprintf(fp,"      lea  rax, [rsp+32]\n");
  fprintf(fp,"      mov  edi, 1\n");
  fprintf(fp,"      sub  rdx, rax\n");
  fprintf(fp,"      xor eax, eax\n");
  fprintf(fp,"      lea rsi, [rsp+32+rdx]\n");
  fprintf(fp,"      mov rdx, r8\n");
  fprintf(fp,"      call write\n");
  fprintf(fp,"      add rsp,40\n");
  fprintf(fp,"      ret\n");

  // DUMP
  fprintf(fp,"global main\n");
  fprintf(fp,"main:\n");
  printf("[CMD] Compiling program\n");
  // -- Compiling Program --
  for(int i = 0; i < program_size; i++){
    if(program[i].opType == OP_PUSHABLE){
      fprintf(fp,"     ;; -- push %d --\n",program[i].val);
      fprintf(fp,"     push %d\n",program[i].val);
    }
    else if(program[i].opType == OP_PLUS){
      fprintf(fp,"     ;; -- plus --\n");
      fprintf(fp,"     pop rax\n");
      fprintf(fp,"     pop rbx\n");
      fprintf(fp,"     add rax,rbx\n");
      fprintf(fp,"     push rax\n");
    }
    else if(program[i].opType == OP_MINUS){
      fprintf(fp,"     ;; -- minus --\n");
      fprintf(fp,"     pop rax\n");
      fprintf(fp,"     pop rbx\n");
      fprintf(fp,"     sub rax, rbx\n");
      fprintf(fp,"     push rax\n");
    }
    else if(program[i].opType == OP_WRITE){
      fprintf(fp,"     ;; -- Dump --\n");
      fprintf(fp,"     pop rdi\n");
      fprintf(fp,"     call dump\n");
    }
  }
  fprintf(fp,"     mov rax, 60\n");
  fprintf(fp,"     mov rdi, 0\n");
  fprintf(fp,"     syscall\n");
  //fprintf(fp,"     ret 16\n");

  char buf[256];
  sprintf(buf,"nasm -g -f win64 output.asm -l output.lst -o output.obj");
  system(buf);
  sprintf(buf,"gcc -g -m64 output.obj -o %s.exe",output);
  system(buf);
  
  fclose(fp);
  remove("output.asm");
  remove("output.o");
}
// -- Compiler Work Paused --

void flag_help(){
  printf("Usage: pitt <FILE> <COMMAND> <SUBCOMMAND> [ARGS]\n");
  printf("COMMANDS:\n");
  printf("     -s     Simulate the program\n");
  printf("     -d     Print the lexical analysis of the program file\n");
  printf("SUBCOMMANDS:\n");
  printf("     -T     Simulation time check\n");
  printf("     -S     Silent simulation INFO\n");
  exit(0);
}

int main(int argc,char **argv)
{
  //TODO: implement flags
  //`-t` flag for time  
  if(argc < 2){
    usage();
    exit(0);
  }
  
  char *mode = argv[2];
  char *file = argv[1];
  char *flag = argv[3]; // supports 1 flag at a time 
  bool flagable = false;
  

  if((strcmp(mode,"-s")!=0) && (strcmp(mode,"-d")!=0)){
    printf("[ERROR] Unknown flag %s\n",mode);
    usage();
    exit(0);
  }


  clock_t t_parse;
  
  struct ipair *_program_file = load_program_from_file(file);
  int size = get_size_of_file(file);

  t_parse = clock() - t_parse;
  double time_taken_parse = ((double)t_parse)/CLOCKS_PER_SEC;

  // -t flag
  double time_taken = 0;
  
  if(strcmp(mode , "-s")==0){
    bool warn = false;
    bool time = false;
    bool sil = false;
    if(argc > 3){
      for(int i = 3; i < argc; i++){
        if(strcmp(argv[i],"-T") == 0){
          time = true;
        }
        else if(strcmp(argv[i],"-S") == 0){
 	  sil = true;
        }
        else{
	  printf("\n[ERROR] Unknown simulation flag %s\n",flag);
	  flag_help();
	  exit(0);
        }
      }
    }
    if(sil == false){
      printf("[INFO] Simulating: %s\n",file,file);
      printf("[INFO] Simulation Type: Unsafe Code\n",file);
      printf("[INFO] Parsing completed in %f seconds\n",time_taken_parse);
      
      if(warn == true){
	printf("[INFO] Simulation flags: -W\n");
	printf("[NOTE] Simulation warnings are enabled\n");
      }

      if(time == true){
	printf("[INFO] Simulation flags: -T\n");
	printf("[NOTE] Simulation time will be displayed\n");
      }
      else{
	printf("[INFO] No simulation flags used\n");
      }
      printf("\n\n\n");
    }

    clock_t t;
    simulate(_program_file,size,file,argc,argv);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    if(time == true){
      printf("\n\n\n[INFO] Simulation completed in %f seconds\n[FILE] %s\n",time_taken,file);
    }
  }
  /*
  else if(strcmp(mode, "-safesim") == 0){
    clock_t t;
    type_check_int(_program_file,size,file);
    simulate(_program_file,size,file,argc,argv);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\nSimulation completed in %f seconds\n",time_taken);
  }
  */
  else if(strcmp(mode , "-d") == 0){
    printf("[INFO] Parsing took %f seconds\n",time_taken_parse);
    printf("[INFO] Lexical Analysis of program\n");
    printf("[FILE] %s\n\n",file);
    int i = 0;
    while(_program_file[i].opType >= 0){
      printf("<(DATA-SERIAL: %d),(DATA-ID: %s)>\n",_program_file[i].opType,readable[_program_file[i].opType]);
      i++;
    }
  }

  
  
  return 0;
}
