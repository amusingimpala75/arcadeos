#pragma once

/* return of zero is false, one is true */

/* isdigit | isalpha */
int isalnum(int ch);

/* (isupper | islower) && !(iscntrl | isdigit | ispunct | isspace)
 or also locale-specific values
 */
int isalpha(int ch);

/* ' ' | '\t'
 or other locale-specific values
 */
int isblank(int ch);

/* tests for control character */
int iscntrl(int ch);

/* tests for decimal digit (5.2.1) */
int isdigit(int ch);

/* every non ' ' printing character */
int isgraph(int ch);

/* lowercase && !(iscntrl | isdigit | ispunct | isspace)
 or other locale specific values
 */
int islower(int ch);

/* tests for printing character */
int isprint(int ch);

/* locale-specific value && !(isspace | isalnum) */
int ispunct(int ch);

/* (' ' | '\f' | '\n' | '\r' | '\t' | '\v') && !alnum
 or other locale-specific values
 */
int isspace(int ch);

/* uppercase && !(iscntrl | isdigit | ispunct | isspace)
 or other locale-specific values
 */
int isupper(int ch);

/* hex digit character */
int isxdigit(int ch);

/*
if !isupper | no conversion, return c
else convert to lowercase
  */
int tolower(int c);

/*
if !islower | no conversion, return c
else conver to uppercase
 */
int toupper(int c);
