/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tk_Size = 258,
    tk_Fit = 259,
    tk_Unit = 260,
    tk_Path = 261,
    tk_Type = 262,
    tk_Delete = 263,
    tk_Name = 264,
    tk_Add = 265,
    tk_ID = 266,
    tk_MKd = 267,
    tk_RMd = 268,
    tk_Fd = 269,
    tk_Mount = 270,
    tk_UnMount = 271,
    tk_Rep = 272,
    tk_Exec = 273,
    tk_Bf = 274,
    tk_Ff = 275,
    tk_Wf = 276,
    tk_Fast = 277,
    tk_Full = 278,
    numero = 279,
    decimal = 280,
    cadena = 281,
    id = 282,
    ruta = 283,
    mas = 284,
    menos = 285,
    por = 286,
    division = 287,
    potencia = 288,
    igual = 289,
    parentA = 290,
    parentC = 291,
    llaveA = 292,
    llaveC = 293,
    corcheA = 294,
    corcheC = 295,
    exclama = 296,
    puntoComa = 297,
    coma = 298,
    simple = 299,
    UMINUS = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 31 "Sintactico.y" /* yacc.c:1909  */

//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
class Nodo_AST *nodo;
//struct Nodo_MBR *NodoMbr;

#line 107 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
