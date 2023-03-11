#include "s21_common.h"

int IsSpec(char symbol) {
  int result = 0;

  switch (symbol) {
    case End:
    case CSpec:
    case DSpec:
    case ISpec:
    case fSpec:
    case gSpec:
    case GSpec:
    case eSpec:
    case ESpec:
    case SSpec:
    case USpec:
    case NSpec:
    case PSpec:
    case xSpec:
    case XSpec:
    case OSpec:
      result = 1;
      break;
  }

  return result;
}

int IsDigit(char symbol, int base) {
  int result = 0;
  if (base == 8) {
    result = (symbol >= '0' && symbol <= '7');
  } else if (base == 10) {
    result = (symbol >= '0' && symbol <= '9');
  } else if (base == 16) {
    result = (symbol >= '0' && symbol <= '9') ||
             (symbol >= 'a' && symbol <= 'f') ||
             (symbol >= 'A' && symbol <= 'F');
  }

  return result;
}

int IsFloat(char symbol) {
  int result = 0;

  if ((symbol >= '0' && symbol <= '9') ||
      (symbol == '.' || symbol == 'e' || symbol == 'E') ||
      (symbol == '+' || symbol == '-')) {
    result = 1;
  }

  return result;
}
