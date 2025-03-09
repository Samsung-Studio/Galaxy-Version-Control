%{
    #include "parser.h"
    #include <cstring>   // Use <cstring> for strdup
    using namespace std;
    
    extern "C" int yylex();
    char* yylval;  // ✅ Declare yylval as a global variable
%}

/* No Bison directives here! */

%%

init         { return 1; }  // ✅ Replace token names with integer values
add          { return 2; }
commit       { return 3; }
log          { return 4; }
checkout     { return 5; }
\"[^\"]*\"   { yylval = strdup(yytext); return 6; }  // ✅ STRING replaced with int value
[A-Za-z0-9._/-]+ { yylval = strdup(yytext); return 7; }  // ✅ ARG replaced with int value
[\n\t ]+     { /* Ignore Whitespace */ }
.            { return yytext[0]; }

%%

int yywrap() { return 1; }