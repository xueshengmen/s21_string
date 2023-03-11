#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  int written_symbols = 0;
  va_list arg_ptr;
  PrintParams params;

  str[0] = '\0';
  params.written_symbols = 0;
  SetDefaultPrintParams(&params);
  va_start(arg_ptr, format);

  s21_sprintf_internal(str, format, &arg_ptr, &params);
  written_symbols = params.written_symbols;

  va_end(arg_ptr);

  return written_symbols;
}

void SetDefaultPrintParams(PrintParams *params) {
  params->symbol = 0;        // default symbol = '\0'
  params->flags = 0;         // flags turned off by default
  params->width = 0;         // default 0 width means no fixed width set
  params->set_accuracy = 0;  // default 0 means accuracy wasn't set
  params->accuracy = 6;      // default accuracy = 6
  // default 0 lenght means neither short or long set
  // < 0 - short; > 0 - long
  params->lenghtInt = 0;
  params->lenghtDouble = 0;
}

void s21_sprintf_internal(char *str, const char *format, va_list *arg_ptr,
                          PrintParams *params) {
  Specs spec;
  int status = 0;
  while (((spec = GetPrintSpec(format, params)) != End) && status != 1) {
    switch (spec) {
      case NonSpec:
        ApplyNonSpec(str, params, arg_ptr);
        break;
      case CSpec:
        ApplyCSpec(str, params, arg_ptr);
        break;
      case ISpec:
      case DSpec:
        ApplyDSpec(str, params, arg_ptr);
        break;
      case fSpec:
        ApplyFSpec(str, params, arg_ptr);
        break;
      case SSpec:
        ApplySSpec(str, params, arg_ptr);
        break;
      case USpec:
        ApplyUSpec(str, params, arg_ptr);
        break;
      case eSpec:
      case ESpec:
        ApplyESpec(str, params, arg_ptr);
        break;
      case OSpec:
        ApplyOSpec(str, params, arg_ptr);
        break;
      case xSpec:
      case XSpec:
        ApplyXSpec(str, params, arg_ptr);
        break;
      case PSpec:
        ApplyPSpec(str, params, arg_ptr);
        break;
      case NSpec:
        ApplyNSpec(str, params, arg_ptr);
        break;
      case GSpec:
      case gSpec:
        ApplyGSpec(str, params, arg_ptr);
        break;
    }
    if (spec == SSpec && params->lenghtInt > 0) {
      str[0] = '\0';
      status = 1;
    }
    SetDefaultPrintParams(params);
  }
}

Specs GetPrintSpec(const char *format, PrintParams *params) {
  Specs spec = NonSpec;
  static size_t i = 0;

  if (format[i] == '%') {
    while (!IsSpec(format[++i]) && IsPrintSpecialSymbol(format[i])) {
      if (format[i] == '-') {
        // Adds minus flag to flags variable
        params->flags |= MINUSFLAG;
      } else if (format[i] == '+') {
        // Adds plus flag to flags variable
        params->flags |= PLUSFLAG;
      } else if (format[i] == '#') {
        // Adds plus flag to flags variable
        params->flags |= HASHFLAG;
      } else if (format[i] == ' ') {
        // Adds space flag to flags variable
        params->flags |= SPACEFLAG;
      } else if (format[i] == '*') {
        if (format[i - 1] != '.') params->flags |= STARFLAG;
      } else if (format[i] == 'h') {
        // Set lenght as short
        params->lenghtInt--;
      } else if (format[i] == 'l') {
        // Set lenght as long
        params->lenghtInt++;
      } else if (format[i] == 'L') {
        params->lenghtDouble++;
      } else if ((format[i]) == '0') {
        params->flags |= ZEROFLAG;
      } else if (IsDigit(format[i], 10)) {
        // Reads width and writes to width variable
        params->width = format[i] - '0';
        while (IsDigit(format[++i], 10))
          params->width = params->width * 10 + (format[i] - '0');
        i--;
      } else if (format[i] == '.') {
        // Reads accuracy and writes to accuracy variable
        params->flags |= DOTFLAG;
        params->set_accuracy = 1;
        if (format[i + 1] == '*') {
          params->flags |= DOTSTARFLAG;
        } else {
          params->accuracy = 0;
        }
        while (IsDigit(format[++i], 10))
          params->accuracy = params->accuracy * 10 + (format[i] - '0');
        i--;
      }
    }

    if (IsSpec(format[i])) {
      spec = format[i];
    }
    params->symbol = format[i];
  } else if (format[i] == '\0') {
    spec = End;
    i = -1;  //
  } else {
    // if (format[i+1] == '%' && format[i] == '%') i++;
    params->symbol = format[i];
  }

  i++;  // Moves right over format string for next iteration

  return spec;
}

int IsPrintSpecialSymbol(char symbol) {
  int result = 0;

  if (IsDigit(symbol, 10)) {
    result = 1;
  }

  for (int i = 0; i < PRINT_SPECIAL_SYMBOLS_COUNT; i++) {
    if (symbol == print_special_symbols[i]) {
      result = 1;
    }
  }

  return result;
}

char print_special_symbols[10] = {
    [0] = '-', [1] = '+', [2] = '#', [3] = ' ', [4] = '*',
    [5] = 'h', [6] = 'l', [7] = 'L', [8] = '0', [9] = '.'};

char *const fract_value[73] = {
    [0] =
        "0."
        "5000000000000000000000000000000000000000000000000000000000000000000000"
        "000",
    [1] =
        "0."
        "2500000000000000000000000000000000000000000000000000000000000000000000"
        "000",
    [2] =
        "0."
        "1250000000000000000000000000000000000000000000000000000000000000000000"
        "000",
    [3] =
        "0."
        "0625000000000000000000000000000000000000000000000000000000000000000000"
        "000",
    [4] =
        "0."
        "0312500000000000000000000000000000000000000000000000000000000000000000"
        "000",
    [5] =
        "0."
        "0156250000000000000000000000000000000000000000000000000000000000000000"
        "000",
    [6] =
        "0."
        "0078125000000000000000000000000000000000000000000000000000000000000000"
        "000",
    [7] =
        "0."
        "0039062500000000000000000000000000000000000000000000000000000000000000"
        "000",
    [8] =
        "0."
        "0019531250000000000000000000000000000000000000000000000000000000000000"
        "000",
    [9] =
        "0."
        "0009765625000000000000000000000000000000000000000000000000000000000000"
        "000",
    [10] =
        "0."
        "0004882812500000000000000000000000000000000000000000000000000000000000"
        "000",
    [11] =
        "0."
        "0002441406250000000000000000000000000000000000000000000000000000000000"
        "000",
    [12] =
        "0."
        "0001220703125000000000000000000000000000000000000000000000000000000000"
        "000",
    [13] =
        "0."
        "0000610351562500000000000000000000000000000000000000000000000000000000"
        "000",
    [14] =
        "0."
        "0000305175781250000000000000000000000000000000000000000000000000000000"
        "000",
    [15] =
        "0."
        "0000152587890625000000000000000000000000000000000000000000000000000000"
        "000",
    [16] =
        "0."
        "0000076293945312500000000000000000000000000000000000000000000000000000"
        "000",
    [17] =
        "0."
        "0000038146972656250000000000000000000000000000000000000000000000000000"
        "000",
    [18] =
        "0."
        "0000019073486328125000000000000000000000000000000000000000000000000000"
        "000",
    [19] =
        "0."
        "0000009536743164062500000000000000000000000000000000000000000000000000"
        "000",
    [20] =
        "0."
        "0000004768371582031250000000000000000000000000000000000000000000000000"
        "000",
    [21] =
        "0."
        "0000002384185791015625000000000000000000000000000000000000000000000000"
        "000",
    [22] =
        "0."
        "0000001192092895507812500000000000000000000000000000000000000000000000"
        "000",
    [23] =
        "0."
        "0000000596046447753906250000000000000000000000000000000000000000000000"
        "000",
    [24] =
        "0."
        "0000000298023223876953125000000000000000000000000000000000000000000000"
        "000",
    [25] =
        "0."
        "0000000149011611938476562500000000000000000000000000000000000000000000"
        "000",
    [26] =
        "0."
        "0000000074505805969238281250000000000000000000000000000000000000000000"
        "000",
    [27] =
        "0."
        "0000000037252902984619140625000000000000000000000000000000000000000000"
        "000",
    [28] =
        "0."
        "0000000018626451492309570312500000000000000000000000000000000000000000"
        "000",
    [29] =
        "0."
        "0000000009313225746154785156250000000000000000000000000000000000000000"
        "000",
    [30] =
        "0."
        "0000000004656612873077392578125000000000000000000000000000000000000000"
        "000",
    [31] =
        "0."
        "0000000002328306436538696289062500000000000000000000000000000000000000"
        "000",
    [32] =
        "0."
        "0000000001164153218269348144531250000000000000000000000000000000000000"
        "000",
    [33] =
        "0."
        "0000000000582076609134674072265625000000000000000000000000000000000000"
        "000",
    [34] =
        "0."
        "0000000000291038304567337036132812500000000000000000000000000000000000"
        "000",
    [35] =
        "0."
        "0000000000145519152283668518066406250000000000000000000000000000000000"
        "000",
    [36] =
        "0."
        "0000000000072759576141834259033203125000000000000000000000000000000000"
        "000",
    [37] =
        "0."
        "0000000000036379788070917129516601562500000000000000000000000000000000"
        "000",
    [38] =
        "0."
        "0000000000018189894035458564758300781250000000000000000000000000000000"
        "000",
    [39] =
        "0."
        "0000000000009094947017729282379150390625000000000000000000000000000000"
        "000",
    [40] =
        "0."
        "0000000000004547473508864641189575195312500000000000000000000000000000"
        "000",
    [41] =
        "0."
        "0000000000002273736754432320594787597656250000000000000000000000000000"
        "000",
    [42] =
        "0."
        "0000000000001136868377216160297393798828125000000000000000000000000000"
        "000",
    [43] =
        "0."
        "0000000000000568434188608080148696899414062500000000000000000000000000"
        "000",
    [44] =
        "0."
        "0000000000000284217094304040074348449707031250000000000000000000000000"
        "000",
    [45] =
        "0."
        "0000000000000142108547152020037174224853515625000000000000000000000000"
        "000",
    [46] =
        "0."
        "0000000000000071054273576010018587112426757812500000000000000000000000"
        "000",
    [47] =
        "0."
        "0000000000000035527136788005009293556213378906250000000000000000000000"
        "000",
    [48] =
        "0."
        "0000000000000017763568394002504646778106689453125000000000000000000000"
        "000",
    [49] =
        "0."
        "0000000000000008881784197001252323389053344726562500000000000000000000"
        "000",
    [50] =
        "0."
        "0000000000000004440892098500626161694526672363281250000000000000000000"
        "000",
    [51] =
        "0."
        "0000000000000002220446049250313080847263336181640625000000000000000000"
        "000",
    [52] =
        "0."
        "0000000000000001110223024625156540423631668090820312500000000000000000"
        "000",
    [53] =
        "0."
        "0000000000000000555111512312578270211815834045410156250000000000000000"
        "000",
    [54] =
        "0."
        "0000000000000000277555756156289135105907917022705078125000000000000000"
        "000",
    [55] =
        "0."
        "0000000000000000138777878078144567552953958511352539062500000000000000"
        "000",
    [56] =
        "0."
        "0000000000000000069388939039072283776476979255676269531250000000000000"
        "000",
    [57] =
        "0."
        "0000000000000000034694469519536141888238489627838134765625000000000000"
        "000",
    [58] =
        "0."
        "0000000000000000017347234759768070944119244813919067382812500000000000"
        "000",
    [59] =
        "0."
        "0000000000000000008673617379884035472059622406959533691406250000000000"
        "000",
    [60] =
        "0."
        "0000000000000000004336808689942017736029811203479766845703125000000000"
        "000",
    [61] =
        "0."
        "0000000000000000002168404344971008868014905601739883422851562500000000"
        "000",
    [62] =
        "0."
        "0000000000000000001084202172485504434007452800869941711425781250000000"
        "000",
    [63] =
        "0."
        "0000000000000000000542101086242752217003726400434970855712890625000000"
        "000",
    [64] =
        "0."
        "0000000000000000000271050543121376108501863200217485427856445312500000"
        "000",
    [65] =
        "0."
        "0000000000000000000135525271560688054250931600108742713928222656250000"
        "000",
    [66] =
        "0."
        "0000000000000000000067762635780344027125465800054371356964111328125000"
        "000",
    [67] =
        "0."
        "0000000000000000000033881317890172013562732900027185678482055664062500"
        "000",
    [68] =
        "0."
        "0000000000000000000016940658945086006781366450013592839241027832031250"
        "000",
    [69] =
        "0."
        "0000000000000000000008470329472543003390683225006796419620513916015625"
        "000",
    [70] =
        "0."
        "0000000000000000000004235164736271501695341612503398209810256958007812"
        "500",
    [71] =
        "0."
        "0000000000000000000002117582368135750847670806251699104905128479003906"
        "250",
    [72] =
        "0."
        "0000000000000000000001058791184067875423835403125849552452564239501953"
        "125",
};