%option case-insensitive
%option yylineno
%{
#include <cstdlib>
#include "parser.h"
#include <QString>
#include <stdio.h>
#include <iostream>
#include <Nodo_AST.h>
#include "qlist.h"

int yylex();
void yyerror(const char *s);
int linea=0; // Para contar lineas
int columna = 1; // para las columnas
int anterior = 0;
QString coment = "";
Nodo_AST *raiz;
%}

%option header-file="scanner.h"
%option outfile="scanner.cpp"
%option noyywrap
%option nounput

letra [a-zñA-ZÑ]+
numero [0-9]+
id {letra}({letra}|{numero}|"_")*
cadena "\""[^"\""]*"\""
ruta ("\/"{id}+)*("\/"{id}+"\."{id}+)
simple "\#"[^("\n"|"\r")]*("\n"|"\r")

%x COM COMM

%%
<INITIAL>"-size"           {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Size;} 
<INITIAL>"-fit"            {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Fit;} 
<INITIAL>"-unit"           {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Unit;} 
<INITIAL>"-path"           {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Path;} 
<INITIAL>"-type"           {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Type;} 
<INITIAL>"-delete"         {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Delete;} 
<INITIAL>"-name"           {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Name;}
<INITIAL>"-add"            {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Add;}
<INITIAL>"-id"             {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_ID;}

<INITIAL>"mkdisk"          {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_MKd;}
<INITIAL>"rmdisk"          {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_RMd;}
<INITIAL>"fdisk"           {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Fd;}
<INITIAL>"mount"           {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Mount;}
<INITIAL>"unmount"         {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_UnMount;}
<INITIAL>"rep"             {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Rep;}
<INITIAL>"exec"            {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Exec;}
<INITIAL>"bf"              {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Bf;}
<INITIAL>"ff"              {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Ff;}
<INITIAL>"wf"              {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Wf;}
<INITIAL>"fast"            {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Fast;}
<INITIAL>"full"            {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return tk_Full;}

<INITIAL>{numero}          {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return numero;}
<INITIAL>{cadena}          {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return cadena;}
<INITIAL>{id}              {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return id;} 
<INITIAL>{ruta}            {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return ruta;} 
<INITIAL>{simple}          {columna=columna+ anterior; columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext); return simple;} 


<INITIAL>"+"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mas; }
<INITIAL>"-"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return menos; }
<INITIAL>"*"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return por; }
<INITIAL>"/"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return division; }
<INITIAL>"^"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return potencia;} 
<INITIAL>"="               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return igual;}
<INITIAL>"("               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return parentA;}
<INITIAL>")"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return parentC;}
<INITIAL>"{"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return llaveA;}
<INITIAL>"}"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return llaveC;}
<INITIAL>"["               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return corcheA;}
<INITIAL>"]"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return corcheC;}
<INITIAL>"!"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return exclama;}
<INITIAL>";"               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return puntoComa;}
<INITIAL>","               {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return coma;}
 

"\t"                       {strcpy(yylval.TEXT, yytext); columna=26;}
[[:blank:]]                {columna++; }
"\n"                       {linea++; columna = 0; anterior = 0;}
.                          {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);
                            /* errorT *nuevoE = new errorT("Lexico",yytext,linea, columna);
                            listaErrores->append(*nuevoE); */
                            std::cout <<yytext <<" Error Lexico en la linea "<< linea << " Columna:"<< columna<<std::endl;
                            }


%%
