
/*  A Bison parser, made from parser.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	TIDENT	258
#define	TNUMBER	259
#define	TFLOAT	260
#define	TCONST	261
#define	TELSE	262
#define	TIF	263
#define	TINT	264
#define	TRETURN	265
#define	TVOID	266
#define	TWHILE	267
#define	TADDASSIGN	268
#define	TSUBASSIGN	269
#define	TMULASSIGN	270
#define	TDIVASSIGN	271
#define	TMODASSIGN	272
#define	TOR	273
#define	TAND	274
#define	TEQUAL	275
#define	TNOTEQU	276
#define	TGREAT	277
#define	TLESS	278
#define	TGREATE	279
#define	TLESSE	280
#define	TINC	281
#define	TDEC	282
#define	TPLUS	283
#define	TMINUS	284
#define	TMULTIPLY	285
#define	TDIVIDE	286
#define	TMOD	287
#define	TNOT	288
#define	TASSIGN	289
#define	TLPAREN	290
#define	TRPAREN	291
#define	TCOMMA	292
#define	TSEMICOLON	293
#define	TLBRACKET	294
#define	TRBRACKET	295
#define	TLBRACE	296
#define	TRBRACE	297
#define	TERROR	298
#define	LOWER_THEN_ELSE	299

#line 1 "parser.y"

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


#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		165
#define	YYFLAG		-32768
#define	YYNTBASE	45

#define YYTRANSLATE(x) ((unsigned)(x) <= 299 ? yytranslate[x] : 91)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     7,     9,    11,    14,    17,    20,    23,
    26,    30,    32,    34,    37,    39,    41,    43,    45,    47,
    49,    53,    55,    56,    58,    62,    65,    69,    73,    76,
    78,    79,    81,    84,    88,    92,    94,    98,   100,   104,
   106,   111,   116,   118,   119,   121,   122,   124,   127,   130,
   132,   134,   136,   138,   140,   143,   146,   148,   149,   155,
   163,   169,   173,   175,   177,   181,   185,   189,   193,   197,
   201,   203,   207,   209,   213,   215,   219,   223,   225,   229,
   233,   237,   241,   243,   247,   251,   253,   257,   261,   265,
   267,   270,   273,   276,   279,   281,   286,   291,   294,   297,
   299,   300,   302,   304,   308,   310,   312
};

static const short yyrhs[] = {    46,
     0,    47,     0,    46,    47,     0,    48,     0,    64,     0,
     3,    38,     0,     3,     1,     0,    49,    60,     0,    49,
    38,     0,    49,     1,     0,    50,    55,    56,     0,    51,
     0,    52,     0,    51,    52,     0,    53,     0,    54,     0,
     6,     0,     9,     0,    11,     0,     3,     0,    35,    57,
    36,     0,    58,     0,     0,    59,     0,    58,    37,    59,
     0,    50,    67,     0,    41,    61,    42,     0,    41,    61,
     1,     0,    62,    69,     0,    63,     0,     0,    64,     0,
    63,    64,     0,    50,    65,    38,     0,    50,    65,     1,
     0,    66,     0,    65,    37,    66,     0,    67,     0,    67,
    34,     4,     0,     3,     0,     3,    39,    68,    40,     0,
     3,    39,    68,     1,     0,     4,     0,     0,    70,     0,
     0,    71,     0,    70,    71,     0,    70,    64,     0,    60,
     0,    72,     0,    74,     0,    75,     0,    76,     0,    73,
    38,     0,    77,     1,     0,    77,     0,     0,     8,    35,
    77,    36,    71,     0,     8,    35,    77,    36,    71,     7,
    71,     0,    12,    35,    77,    36,    71,     0,    10,    73,
    38,     0,    78,     0,    79,     0,    85,    34,    78,     0,
    85,    13,    78,     0,    85,    14,    78,     0,    85,    15,
    78,     0,    85,    16,    78,     0,    85,    17,    78,     0,
    80,     0,    79,    18,    80,     0,    81,     0,    80,    19,
    81,     0,    82,     0,    81,    20,    82,     0,    81,    21,
    82,     0,    83,     0,    82,    22,    83,     0,    82,    23,
    83,     0,    82,    24,    83,     0,    82,    25,    83,     0,
    84,     0,    83,    28,    84,     0,    83,    29,    84,     0,
    85,     0,    84,    30,    85,     0,    84,    31,    85,     0,
    84,    32,    85,     0,    86,     0,    29,    85,     0,    33,
    85,     0,    26,    85,     0,    27,    85,     0,    90,     0,
    86,    39,    77,    40,     0,    86,    35,    87,    36,     0,
    86,    26,     0,    86,    27,     0,    88,     0,     0,    89,
     0,    78,     0,    89,    37,    78,     0,     3,     0,     4,
     0,    35,    77,    36,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    32,    34,    35,    37,    38,    39,    40,    46,    47,    48,
    58,    60,    62,    63,    65,    66,    68,    70,    71,    73,
    84,    86,    87,    89,    90,    92,    94,    95,   101,   103,
   104,   106,   107,   109,   114,   123,   124,   126,   127,   129,
   142,   148,   154,   155,   157,   158,   160,   161,   162,   164,
   165,   166,   167,   168,   170,   171,   177,   178,   180,   181,
   183,   185,   187,   189,   190,   191,   192,   193,   194,   195,
   197,   198,   200,   201,   203,   204,   205,   207,   208,   209,
   210,   211,   213,   214,   215,   217,   218,   219,   220,   222,
   223,   224,   225,   226,   228,   229,   230,   231,   232,   234,
   235,   237,   239,   240,   242,   243,   244
};

static const char * const yytname[] = {   "$","error","$undefined.","TIDENT",
"TNUMBER","TFLOAT","TCONST","TELSE","TIF","TINT","TRETURN","TVOID","TWHILE",
"TADDASSIGN","TSUBASSIGN","TMULASSIGN","TDIVASSIGN","TMODASSIGN","TOR","TAND",
"TEQUAL","TNOTEQU","TGREAT","TLESS","TGREATE","TLESSE","TINC","TDEC","TPLUS",
"TMINUS","TMULTIPLY","TDIVIDE","TMOD","TNOT","TASSIGN","TLPAREN","TRPAREN","TCOMMA",
"TSEMICOLON","TLBRACKET","TRBRACKET","TLBRACE","TRBRACE","TERROR","LOWER_THEN_ELSE",
"mini_c","translation_unit","external_dcl","function_def","function_header",
"dcl_spec","dcl_specifiers","dcl_specifier","type_qualifier","type_specifier",
"function_name","formal_param","opt_formal_param","formal_param_list","param_dcl",
"compound_st","compound","opt_dcl_list","declaration_list","declaration","init_dcl_list",
"init_declarator","declarator","opt_number","opt_stat_list","statement_list",
"statement","expression_st","opt_expression","if_st","while_st","return_st",
"expression","assignment_exp","logical_or_exp","logical_and_exp","equality_exp",
"relational_exp","additive_exp","multiplicative_exp","unary_exp","postfix_exp",
"opt_actual_param","actual_param","actual_param_list","primary_exp",""
};
#endif

static const short yyr1[] = {     0,
    45,    46,    46,    47,    47,    47,    47,    48,    48,    48,
    49,    50,    51,    51,    52,    52,    53,    54,    54,    55,
    56,    57,    57,    58,    58,    59,    60,    60,    61,    62,
    62,    63,    63,    64,    64,    65,    65,    66,    66,    67,
    67,    67,    68,    68,    69,    69,    70,    70,    70,    71,
    71,    71,    71,    71,    72,    72,    73,    73,    74,    74,
    75,    76,    77,    78,    78,    78,    78,    78,    78,    78,
    79,    79,    80,    80,    81,    81,    81,    82,    82,    82,
    82,    82,    83,    83,    83,    84,    84,    84,    84,    85,
    85,    85,    85,    85,    86,    86,    86,    86,    86,    87,
    87,    88,    89,    89,    90,    90,    90
};

static const short yyr2[] = {     0,
     1,     1,     2,     1,     1,     2,     2,     2,     2,     2,
     3,     1,     1,     2,     1,     1,     1,     1,     1,     1,
     3,     1,     0,     1,     3,     2,     3,     3,     2,     1,
     0,     1,     2,     3,     3,     1,     3,     1,     3,     1,
     4,     4,     1,     0,     1,     0,     1,     2,     2,     1,
     1,     1,     1,     1,     2,     2,     1,     0,     5,     7,
     5,     3,     1,     1,     3,     3,     3,     3,     3,     3,
     1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
     3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
     2,     2,     2,     2,     1,     4,     4,     2,     2,     1,
     0,     1,     1,     3,     1,     1,     3
};

static const short yydefact[] = {     0,
     0,    17,    18,    19,     1,     2,     4,     0,     0,    12,
    13,    15,    16,     5,     7,     6,     3,    10,     9,    31,
     8,    40,     0,     0,    36,    38,    14,     0,     0,    46,
    30,    32,    44,    23,    11,    35,     0,    34,     0,    40,
    28,    27,   105,   106,     0,    58,     0,     0,     0,     0,
     0,     0,    50,    29,    45,    47,    51,     0,    52,    53,
    54,     0,    63,    64,    71,    73,    75,    78,    83,    86,
    90,    95,    33,    43,     0,     0,     0,    22,    24,    37,
    39,     0,     0,    57,     0,    93,    94,    91,    92,     0,
    49,    48,    55,    56,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    98,    99,   101,     0,    42,    41,    26,
    21,     0,     0,    62,     0,   107,    72,    86,    74,    76,
    77,    79,    80,    81,    82,    84,    85,    87,    88,    89,
    66,    67,    68,    69,    70,    65,   103,     0,   100,   102,
     0,    25,    58,    58,    97,     0,    96,    59,    61,   104,
    58,    60,     0,     0,     0
};

static const short yydefgoto[] = {   163,
     5,     6,     7,     8,    28,    10,    11,    12,    13,    23,
    35,    77,    78,    79,    53,    29,    30,    31,    14,    24,
    25,    26,    75,    54,    55,    56,    57,    58,    59,    60,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
    71,   148,   149,   150,    72
};

static const short yypact[] = {    87,
    15,-32768,-32768,-32768,    87,-32768,-32768,     5,     4,    24,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    24,
-32768,    -7,   -15,    13,-32768,     6,-32768,    39,     2,   107,
    24,-32768,    41,    24,-32768,-32768,    39,-32768,    51,    31,
-32768,-32768,-32768,-32768,    40,   127,    67,   127,   127,   127,
   127,   127,-32768,-32768,    68,-32768,-32768,    74,-32768,-32768,
-32768,    16,-32768,    90,    86,    61,   141,     8,    17,    70,
    -8,-32768,-32768,-32768,    12,    39,    77,    79,-32768,-32768,
-32768,   127,    76,-32768,   127,-32768,-32768,-32768,-32768,    82,
-32768,-32768,-32768,-32768,   127,   127,   127,   127,   127,   127,
   127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
   127,   127,   127,-32768,-32768,   127,   127,-32768,-32768,-32768,
-32768,    24,    88,-32768,    92,-32768,    86,-32768,    61,   141,
   141,     8,     8,     8,     8,    17,    17,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    96,-32768,    89,
    83,-32768,   117,   117,-32768,   127,-32768,   128,-32768,-32768,
   117,-32768,   137,   138,-32768
};

static const short yypgoto[] = {-32768,
-32768,   134,-32768,-32768,     0,-32768,   131,-32768,-32768,-32768,
-32768,-32768,-32768,    25,   143,-32768,-32768,-32768,   -16,-32768,
   112,    81,-32768,-32768,-32768,   -54,-32768,   109,-32768,-32768,
-32768,   -44,   -87,-32768,    64,    65,    -9,    69,   -12,   -39,
-32768,-32768,-32768,-32768,-32768
};


#define	YYLAST		171


static const short yytable[] = {     9,
    92,    84,    41,    32,     9,    18,    22,    90,    86,    87,
    88,    89,   118,    36,    73,    15,    94,   114,   115,    34,
   141,   142,   143,   144,   145,   146,   116,   -20,   147,     2,
   117,    33,     3,    76,     4,   103,   104,   123,    91,    39,
   125,    40,    19,    42,    74,    20,   105,   106,   107,    37,
    38,   119,    16,   -57,    81,   128,   128,   128,   128,   128,
   128,   128,   128,   128,   128,   138,   139,   140,   160,    33,
    43,    44,   151,     2,    82,    45,     3,    46,     4,    47,
    97,    98,   108,   109,   110,   111,   112,   130,   131,     1,
   136,   137,     2,    48,    49,     3,    50,     4,   158,   159,
    51,    85,    52,   113,    96,   -58,   162,    95,    20,    43,
    44,    93,   121,   124,    45,   122,    46,   126,    47,    43,
    44,    76,   157,   153,    45,   156,    46,   154,    47,    43,
    44,   155,    48,    49,   161,    50,   164,   165,    17,    51,
    27,    52,    48,    49,   -58,    50,   152,    20,    80,    51,
    21,    52,    48,    49,    83,    50,   120,    20,   127,    51,
   129,    52,    99,   100,   101,   102,     0,   132,   133,   134,
   135
};

static const short yycheck[] = {     0,
    55,    46,     1,    20,     5,     1,     3,    52,    48,    49,
    50,    51,     1,     1,    31,     1,     1,    26,    27,    35,
   108,   109,   110,   111,   112,   113,    35,    35,   116,     6,
    39,    39,     9,    34,    11,    28,    29,    82,    55,    34,
    85,     3,    38,    42,     4,    41,    30,    31,    32,    37,
    38,    40,    38,    38,     4,    95,    96,    97,    98,    99,
   100,   101,   102,   103,   104,   105,   106,   107,   156,    39,
     3,     4,   117,     6,    35,     8,     9,    10,    11,    12,
    20,    21,    13,    14,    15,    16,    17,    97,    98,     3,
   103,   104,     6,    26,    27,     9,    29,    11,   153,   154,
    33,    35,    35,    34,    19,    38,   161,    18,    41,     3,
     4,    38,    36,    38,     8,    37,    10,    36,    12,     3,
     4,   122,    40,    36,     8,    37,    10,    36,    12,     3,
     4,    36,    26,    27,     7,    29,     0,     0,     5,    33,
    10,    35,    26,    27,    38,    29,   122,    41,    37,    33,
     8,    35,    26,    27,    46,    29,    76,    41,    95,    33,
    96,    35,    22,    23,    24,    25,    -1,    99,   100,   101,
   102
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 7:
#line 41 "parser.y"
{
				yyerrok;
				printError(wrong_st);
			;
    break;}
case 10:
#line 49 "parser.y"
{
				/*에러 발생시 type 수정을 위해 default값 '0' 세팅*/
				/*identifier about parse error*/
				look_tmp->type = 0;
				yyerrok;
				/*wrong function definition error*/
				printError(wrong_funcdef);
			;
    break;}
case 18:
#line 70 "parser.y"
{type_int=1;;
    break;}
case 19:
#line 71 "parser.y"
{type_void=1;;
    break;}
case 20:
#line 74 "parser.y"
{ /*identifier about parse error or not defined identifier/function*/
				if(look_id->type==0 || look_id->type == 5)
				{
					look_id->type = 4; /*function name*/
					type_int=0; /*not integer*/
					type_void=0; /*not void*/
					look_tmp = look_id;
				}
			;
    break;}
case 28:
#line 96 "parser.y"
{
				yyerrok;
				printError(nobrace); /*no brace error*/
			;
    break;}
case 34:
#line 110 "parser.y"
{
				type_int = 0; /*not integer*/
				type_void = 0; /*not void*/
			;
    break;}
case 35:
#line 115 "parser.y"
{
				look_tmp->type = 0; /*identifier about parse error*/
				yyerrok;
				type_int = 0; /*not integer*/
				type_void=0; /*not void*/
				printError(nosemi);  /*no semicolon error*/
			;
    break;}
case 40:
#line 130 "parser.y"
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
			;
    break;}
case 41:
#line 143 "parser.y"
{
				if(look_id->type==0) /*현재 identifier가 type field를 가리키면*/
					look_id->type = 3; /*array integer variable*/
				look_tmp = look_id;
			;
    break;}
case 42:
#line 149 "parser.y"
{
				yyerrok;
				printError(nobracket); /*no bracket error*/
			;
    break;}
case 56:
#line 172 "parser.y"
{
				yyerrok;
				printError(nosemi); /*no semicolon error*/
			;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 246 "parser.y"


void line(int n)
{	
	printf("\t %d \t",n);
}
