%{
#include <jeason.tab.h>
#include <iostream>

#define YY_INPUT(buf, result, max_size) jeason_yy_input(buf, result, max_size); 

void jeason_yy_input( char*, int&, size_t );
const char* strip_quotes( char* );

std::istream* jeason_input_stream_ptr;

%}

%%

[ \t\n]+                     
\{                           { return OPEN_BRACE;    }
\}                           { return CLOSE_BRACE;   }
,			     { return COMMA;         }
\[                           { return OPEN_BRACKET;  }
]                            { return CLOSE_BRACKET; }
\:                           { return COLON;         }
null                         { return NULL_REF;      }

[+-]?[0-9]+\.[0-9]+f         { yylval.s = yytext; return FLOAT;   }
[+-]?[0-9]+\.[0-9]+          { yylval.s = yytext; return DOUBLE;  }
[+-]?[0-9]+                  { yylval.s = yytext; return INTEGER; }

true                  { yylval.s = yytext; return BOOL; }
false                 { yylval.s = yytext; return BOOL; }

\"[^\"]*\"            { yylval.s = strip_quotes(yytext); return STRING; }
\'[^\']*\'            { yylval.s = strip_quotes(yytext); return STRING; }

.                            { fprintf(stderr, "bad token: %s\n", yytext);  return 1; }

%%


int yywrap() { return 1; }

const char* strip_quotes( char* source )
{
  source[ strlen(source)-1 ] = '\0';
  return &source[1];
}

void jeason_yy_input(char* buf, int& result, size_t max_size)
{
  if ( jeason_input_stream_ptr && !jeason_input_stream_ptr->eof() )
  {
    jeason_input_stream_ptr->read( buf, max_size );
    result = jeason_input_stream_ptr->gcount();
  }
  else
  {
    result = YY_NULL;
  }
}
