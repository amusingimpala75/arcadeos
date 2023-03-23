#include "ctype.h"

// TODO: locale support

int isalnum(int ch) { return isdigit(ch) || isalpha(ch); }

int isalpha(int ch) {
  return (isupper(ch) || islower(ch)) &&
         !(iscntrl(ch) || isdigit(ch) || ispunct(ch) || isspace(ch));
}

int isblank(int ch) { return ch == ' ' || ch == '\t'; }

// TODO
int iscntrl(int ch) { return 0; }

int isdigit(int ch) { return ch >= '0' && ch <= '9'; }

// int isgraph(int ch);

int islower(int ch) {
  return (ch >= 'a' && ch <= 'z') &&
         !(iscntrl(ch) || isdigit(ch) || ispunct(ch) || isspace(ch));
}

// int isprint(int ch);

// TODO
int ispunct(int ch) { return 0; }

int isspace(int ch) {
  return (ch == ' ' || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t' ||
          ch == '\v') &&
         !isalnum(ch);
}

int isupper(int ch) {
  return (ch >= 'A' && ch <= 'Z') &&
         !(iscntrl(ch) || isdigit(ch) || ispunct(ch) || isspace(ch));
}

int isxdigit(int ch) {
  return (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F') ||
         (ch >= '0' && ch <= '9');
}

// int tolower(int ch);

// int toupper(int ch);
