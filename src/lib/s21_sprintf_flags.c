#include "s21_sprintf.h"

void StarPriority(PrintParams *params, va_list *arg_ptr) {
  if ((params->flags & STARFLAG) && !(params->flags & DOTSTARFLAG)) {
    ApplyStarFlags(params, arg_ptr);
  } else if (!(params->flags & STARFLAG) && (params->flags & DOTSTARFLAG)) {
    params->accuracy = va_arg(*arg_ptr, int);
  } else if ((params->flags & STARFLAG) && (params->flags & DOTSTARFLAG)) {
    ApplyStarFlags(params, arg_ptr);
    params->accuracy = va_arg(*arg_ptr, int);
  }
}

void ApplyStarFlags(PrintParams *params, va_list *arg_ptr) {
  int width = 0;
  if (params->flags & STARFLAG) width = va_arg(*arg_ptr, int);
  if (width < 0) {
    params->flags |= MINUSFLAG;
    if (params->flags & ZEROFLAG) params->flags ^= ZEROFLAG;
    width *= -1;
  }
  if (params->width == 0) params->width = width;
}

char *ApplyMinusFlag(char *dest, PrintParams *params) {
  int src_len = s21_strlen(dest);
  char *spaces_aray = GetSymbolsArray(' ', params->width - src_len);
  return AddSymbArrayToStr(dest, LEFT, spaces_aray);
}

char *ApplyWidth(char *dest, PrintParams *params) {
  int src_len = s21_strlen(dest);
  char *spaces_aray = GetSymbolsArray(' ', params->width - src_len);
  return AddSymbArrayToStr(dest, RIGHT, spaces_aray);
}

char *ApplyZeroFlag(Specs type, char *dest, PrintParams *params) {
  int src_len = s21_strlen(dest);

  int count_zeros = params->set_accuracy && params->accuracy >= 0 &&
                            IsCorrespond(type, 7, OSpec, xSpec, XSpec, DSpec,
                                         ISpec, USpec, PSpec)
                        ? params->accuracy - src_len
                        : params->width - src_len;

  char *zeros_aray = GetSymbolsArray('0', count_zeros);
  char *res = AddSymbArrayToStr(dest, RIGHT, zeros_aray);

  if (IsCorrespond(type, 3, xSpec, XSpec, PSpec) &&
      (params->flags & HASHFLAG)) {
    res = HandleZeroAndHashFlagHex(res, params);
  }

  res = HandleZeroAndSign(res, params);

  return res;
}

char *HandleZeroAndHashFlagHex(char *dest, PrintParams *params) {
  int x_position = GetSymbPosition(dest, params->symbol);
  if (x_position != -1) {
    dest[x_position] = '0';
    dest[1] = params->symbol;
  }
  return dest;
}

char *HandleZeroAndSign(char *dest, PrintParams *params) {
  char sign = '-';
  int x_position = GetSymbPosition(dest, sign);
  int not_symb_sign =
      x_position - 1 < 0
          ? 1
          : dest[x_position - 1] !=
                params->symbol;  // check that's not a exponent sign
  if ((params->flags & PLUSFLAG) &&
      (x_position == -1 ||
       !not_symb_sign)) {  // Handle situatoion, when set PLUSFLAG, but the
                           // digit is negative
    sign = '+';
    x_position = GetSymbPosition(dest, sign);
  }
  not_symb_sign =
      x_position - 1 < 0 ? 1 : dest[x_position - 1] != params->symbol;
  if (x_position != -1 && not_symb_sign) {
    dest[x_position] = '0';
    dest[0] = sign;
  }
  return dest;
}

char *HandleZeroAndSpaceFlag(char *dest) {
  int x_position = GetSymbPosition(dest, ' ');
  if (x_position != -1) {
    dest[x_position] = '0';
    dest[0] = ' ';
  }
  return dest;
}

// TO-DO handle n spec()
char *ApplyFlags(Specs type, char *dest, PrintParams *params) {
  if (params->flags || params->width != 0) {
    if (params->flags & HASHFLAG) {
      dest = ApplyHashFlag(type, dest, params);
    }

#ifndef LINUX
    if (!IsCorrespond(type, 7, CSpec, SSpec, USpec, xSpec, XSpec, OSpec,
                      PSpec)) {
#else
    if (!IsCorrespond(type, 6, CSpec, SSpec, USpec, xSpec, XSpec, OSpec)) {
#endif
      if ((params->flags & PLUSFLAG)) {
        dest = ApplyPlusFlag(dest, params);
      } else if (params->flags & SPACEFLAG) {
        dest = ApplySpaceFlag(dest, params);
      }
    }

    int src_len = s21_strlen(dest);
    if (params->flags & MINUSFLAG) {
      dest = ApplyMinusFlag(dest, params);
    }
#ifndef LINUX
    else if ((params->flags & ZEROFLAG) && type != SSpec) {
#else
    else if ((params->flags & ZEROFLAG) &&
             !IsCorrespond(type, 2, CSpec, SSpec)) {
#endif
      dest = ApplyZeroFlag(type, dest, params);
    } else if (src_len < params->width) {
      dest = ApplyWidth(dest, params);
    }

    if ((params->flags & ZEROFLAG) && (params->flags & SPACEFLAG) &&
        !(params->flags & PLUSFLAG) && !(params->flags & MINUSFLAG) &&
        !IsCorrespond(type, 7, CSpec, SSpec, USpec, xSpec, XSpec, OSpec,
                      PSpec)) {
      dest = HandleZeroAndSpaceFlag(dest);
    }

    if ((params->flags & ZEROFLAG) && params->set_accuracy &&
        src_len < params->width) {
      dest = ApplyWidth(dest, params);
    }
  }

  return dest;
}

char *ApplyHashFlag(Specs type, char *dest, PrintParams *params) {
  char *res = dest;
  if (type == OSpec)
    res = ApplyHashFlagOctal(dest, params);
  else if (IsCorrespond(type, 3, xSpec, XSpec, PSpec))
    res = ApplyHashFlagHex(type, dest, params);

  return res;
}

char *ApplyHashFlagOctal(char *dest, PrintParams *params) {
  char *result = NULL;

  if (dest[0] != '0') {  // If digit equal 0, it wouldn't be true, because hashflag
                         // handling first
    char *prefix = malloc(2);
    prefix[0] = '0';
    prefix[1] = '\0';
    result = AddSymbArrayToStr(dest, RIGHT, prefix);
  } else {
    result = dest;
  }

  return result;
}

char *ApplyHashFlagHex(Specs type, char *dest, PrintParams *params) {
  char *result = NULL;

  if (!(OtherZero(dest, 0) && type != PSpec)) {
    char *prefix = malloc(3);
    prefix[0] = '0';
    prefix[1] = params->symbol;
    ;
    prefix[2] = '\0';
    result = AddSymbArrayToStr(dest, RIGHT, prefix);
  } else {
    result = dest;
  }

  return result;
}

char *ApplyPlusFlag(char *dest, PrintParams *params) {
  if (dest[0] != '-') {
    dest = AddSymbAtBegining(dest, '+');
  }
  return dest;
}

char *ApplySpaceFlag(char *dest, PrintParams *params) {
  if (dest[0] != '-') {
    dest = AddSymbAtBegining(dest, ' ');
  }
  return dest;
}