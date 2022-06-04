%{
/*
parser.y - yacc source for Mini C
programmer - 장민지 1976336
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include "glob.h"
#include "tn.h"

int type_int = 0;
int type_void = 0;

void line(int);
extern printError();
extern yylex();
extern yyerror(s);

%}

%token TIDENT TNUMBER TFLOAT TCONST TELSE TIF TINT TRETURN TVOID TWHILE
%token TADDASSIGN TSUBASSIGN TMULASSIGN TDIVASSIGN TMODASSIGN
%token TOR TAND TEQUAL TNOTEQU TGREAT TLESS TGREATE TLESSE TINC TDEC
%token TPLUS TMINUS TMULTIPLY TDIVIDE TMOD TNOT TASSIGN TLPAREN TRPAREN TCOMMA TSEMICOLON
%token TLBRACKET TRBRACKET TLBRACE TRBRACE TERROR
%nonassoc LOWER_THEN_ELSE
%nonassoc TELSE 

%%
mini_c 		: translation_unit			
			;
translation_unit 	: external_dcl				
			| translation_unit external_dcl	
			;
external_dcl 		: function_def			
		  	| declaration				
			| TIDENT TSEMICOLON
			| TIDENT error
			{
				yyerrok;
				printError(wrong_st);
			}
			;
function_def 		: function_header compound_st		
			| function_header TSEMICOLON
			| function_header error
			{
				/*에러 발생시 type 수정을 위해 default값 '0' 세팅*/
				/*identifier about parse error*/
				look_tmp->type = 0;
				yyerrok;
				/*wrong function definition error*/
				printError(wrong_funcdef);
			}
			;
function_header 	: dcl_spec function_name formal_param	
			;
dcl_spec 		: dcl_specifiers			
			;
dcl_specifiers 	: dcl_specifier				
		 	| dcl_specifiers dcl_specifier		
			;
dcl_specifier 		: type_qualifier				
			| type_specifier			
			;
type_qualifier 	: TCONST				
			;
type_specifier 	: TINT	 {type_int=1;} /*type : integer*/				
		 	| TVOID  {type_void=1;} /*type : void*/				
			;
function_name 	: TIDENT					
			{ /*identifier about parse error or not defined identifier/function*/
				if(look_id->type==0 || look_id->type == 5)
				{
					look_id->type = 4; /*function name*/
					type_int=0; /*not integer*/
					type_void=0; /*not void*/
					look_tmp = look_id;
				}
			}
			;
formal_param 	: TLPAREN opt_formal_param TRPAREN 		
			;
opt_formal_param 	: formal_param_list			
		   	|					
			;
formal_param_list 	: param_dcl				
		    	| formal_param_list TCOMMA param_dcl 	
			;
param_dcl 		: dcl_spec declarator			
			;
compound_st 	: TLBRACE compound TRBRACE 	
			| TLBRACE compound error
			{
				yyerrok;
				printError(nobrace); /*no brace error*/
			}
			;
compound		: opt_dcl_list opt_stat_list
			;
opt_dcl_list 		: declaration_list			
			|					
			;
declaration_list 	: declaration				
			| declaration_list declaration 		
			;
declaration 		: dcl_spec init_dcl_list TSEMICOLON		
			{
				type_int = 0; /*not integer*/
				type_void = 0; /*not void*/
			}
			| dcl_spec init_dcl_list error
			{
				look_tmp->type = 0; /*identifier about parse error*/
				yyerrok;
				type_int = 0; /*not integer*/
				type_void=0; /*not void*/
				printError(nosemi);  /*no semicolon error*/
			}
			;
init_dcl_list 		: init_declarator			
			| init_dcl_list TCOMMA init_declarator 	
			;
init_declarator 	: declarator					
		 	| declarator TASSIGN TNUMBER		
			;
declarator 		: TIDENT
			{
				if(look_id->type==0){ /*현재 identifier가 type field를 가리키면*/
				
					if(type_int == 1) /*type : integer*/	
						look_id->type = 1;
					 /*integer scalar variable*/
					if(type_int != 1 && type_void == 1)/*type : void*/	
						look_id->type = 2;
					 /*void scalar variable*/
				}
				look_tmp = look_id;
			}
	     		| TIDENT TLBRACKET opt_number TRBRACKET
			{
				if(look_id->type==0) /*현재 identifier가 type field를 가리키면*/
					look_id->type = 3; /*array integer variable*/
				look_tmp = look_id;
			}
			| TIDENT TLBRACKET opt_number error
			{
				yyerrok;
				printError(nobracket); /*no bracket error*/
			}
			;
opt_number 		: TNUMBER				
	     		|					
			;
opt_stat_list 		: statement_list			
		 	| 					
			;
statement_list 	: statement	
		 	| statement_list statement 		
			| statement_list declaration
			;
statement 		: compound_st			
	   		| expression_st			
	   		| if_st					
	   		| while_st				
	   		| return_st				
	   		;
expression_st 	: opt_expression TSEMICOLON			
			| expression error
			{
				yyerrok;
				printError(nosemi); /*no semicolon error*/
			}
			;
opt_expression 	: expression				
		 	|					
			;
if_st 			: TIF TLPAREN expression TRPAREN statement %prec LOWER_THEN_ELSE	
			| TIF TLPAREN expression TRPAREN statement TELSE statement 	
			;
while_st 		: TWHILE TLPAREN expression TRPAREN statement 	
			;
return_st 		: TRETURN opt_expression TSEMICOLON		
			;
expression 		: assignment_exp			
			;
assignment_exp 	: logical_or_exp			
			| unary_exp TASSIGN assignment_exp 		
			| unary_exp TADDASSIGN assignment_exp 	
			| unary_exp TSUBASSIGN assignment_exp 	
			| unary_exp TMULASSIGN assignment_exp 	
			| unary_exp TDIVASSIGN assignment_exp 	
			| unary_exp TMODASSIGN assignment_exp 	
			;
logical_or_exp 	: logical_and_exp			
			| logical_or_exp TOR logical_and_exp 	
			;
logical_and_exp 	: equality_exp				
		 	| logical_and_exp TAND equality_exp 	
			;
equality_exp 		: relational_exp			
			| equality_exp TEQUAL relational_exp 	
			| equality_exp TNOTEQU relational_exp 
			;
relational_exp 	: additive_exp 			
			| relational_exp TGREAT additive_exp 	
			| relational_exp TLESS additive_exp 	
			| relational_exp TGREATE additive_exp 	
			| relational_exp TLESSE additive_exp 	
			;
additive_exp 		: multiplicative_exp			
			| additive_exp TPLUS multiplicative_exp 	
			| additive_exp TMINUS multiplicative_exp 	
			;
multiplicative_exp 	: unary_exp				
		    	| multiplicative_exp TMULTIPLY unary_exp 	
		    	| multiplicative_exp TDIVIDE unary_exp 
		    	| multiplicative_exp TMOD unary_exp 	
			;
unary_exp 		: postfix_exp				
	   		| TMINUS unary_exp				
	   		| TNOT unary_exp			
	   		| TINC unary_exp		
	   		| TDEC unary_exp			
			;
postfix_exp 		: primary_exp			
	      		| postfix_exp TLBRACKET expression TRBRACKET 
	      		| postfix_exp TLPAREN opt_actual_param TRPAREN
	      		| postfix_exp TINC		
	      		| postfix_exp TDEC			
			;
opt_actual_param 	: actual_param			
		  	|					
			;
actual_param 	: actual_param_list			
			;
actual_param_list 	: assignment_exp			
		   	| actual_param_list TCOMMA assignment_exp 	
			;
primary_exp 		: TIDENT		
	     		| TNUMBER			
	     		| TLPAREN expression TRPAREN			
			;
%%

void line(int n)
{	
	printf("\t %d \t",n);
}
