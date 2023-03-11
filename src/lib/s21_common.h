#ifndef SRC_S21_COMMON_H_
#define SRC_S21_COMMON_H_

#include <stdio.h>
/*
 *  Represents all specs as enum elements
 */
typedef enum Specs {
  End = 0,  // Represents \0 in "format" string
  NonSpec = 1,
  CSpec = 'c',
  DSpec = 'd',
  ISpec = 'i',
  fSpec = 'f',
  gSpec = 'g',
  GSpec = 'G',
  eSpec = 'e',
  ESpec = 'E',
  SSpec = 's',
  USpec = 'u',
  NSpec = 'n',
  PSpec = 'p',
  xSpec = 'x',
  XSpec = 'X',
  OSpec = 'o'
} Specs;

int IsSpec(char symbol);
int IsDigit(char symbol, int base);
int IsFloat(char symbol);
#endif  // SRC_S21_COMMON_H_