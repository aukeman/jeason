%{
  #include <stdio.h>
  #include <jeason_base.h>

  extern int yylex();

  void yyerror(const jeason_base*, const char* error) 
  { fprintf( stderr, "%s\n", error); }

%}

%union{
  const char* s;
}

%token <s> INTEGER
%token <s> FLOAT
%token <s> DOUBLE
%token <s> STRING
%token <s> BOOL
%token     NULL_REF
%token     OPEN_BRACE
%token     CLOSE_BRACE
%token     COMMA
%token     OPEN_BRACKET
%token     CLOSE_BRACKET
%token     COLON

%type <s> scalar

%parse-param { jeason_base* jeason };

%%

input:     object                        { return 0; }
        |  array                         { return 0; }
         ;

object:    OPEN_BRACE object_contents CLOSE_BRACE
         ;

object_contents: 
         | object_member
         | object_contents COMMA object_member
         ;

object_member: STRING COLON scalar { jeason->apply_value($1, $3); }

             | STRING COLON OPEN_BRACKET { jeason = jeason->begin_array($1); } 
                            array_contents 
                            CLOSE_BRACKET { jeason = jeason->end_array(); }   

             | STRING COLON OPEN_BRACE { jeason = jeason->begin_object($1); } 
                            object_contents 
                            CLOSE_BRACE { jeason = jeason->end_object(); } 
             ;

array:     OPEN_BRACKET array_contents CLOSE_BRACKET
         ;

array_contents:
         | scalar { jeason->apply_array_element( $1 ); }

         | OPEN_BRACE { jeason = jeason->begin_object(); } 
           object_contents 
	   CLOSE_BRACE { jeason = jeason->end_object(); } 

         | OPEN_BRACKET { jeason = jeason->begin_array(); } 
           array_contents 
           CLOSE_BRACKET { jeason = jeason->end_array(); }   

         | array_contents COMMA scalar { jeason->apply_array_element( $3 ); }

         | array_contents 
           COMMA 
           OPEN_BRACE { jeason = jeason->begin_object(); } 
           object_contents 
	   CLOSE_BRACE { jeason = jeason->end_object(); } 

         | array_contents 
           COMMA 
           OPEN_BRACKET { jeason = jeason->begin_array(); } 
           array_contents 
           CLOSE_BRACKET { jeason = jeason->end_array(); }   
         ;

scalar:    INTEGER                       
         | FLOAT                         
         | DOUBLE                        
         | STRING
         | BOOL

%%

