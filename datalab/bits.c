/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
//1
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  int not_x = ~x;
  int not_y = ~y;
  return ~(not_x & not_y);
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return x & 1;
}
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  int not_x = ~x;
  int not_y = ~y;
  return not_x & not_y;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int not_x = ~x;
  int not_y = ~y;
  return ~(not_x & not_y) & ~(x & y);
}
//2
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  int mascara_par = 0x55; // 0101 0101
  mascara_par = mascara_par | (mascara_par << 8); // mascara_par = 0101 0101 0101 0101
  mascara_par = mascara_par | (mascara_par << 16); // mascara_par = 0101 0101 0101 0101 0101 0101 0101 0101
  return mascara_par;
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
  int resultado;
  int mascara_impar = 0xAA; // 1010 1010
  mascara_impar = mascara_impar | (mascara_impar << 8); // mascara_impar = 1010 1010 1010 1010
  mascara_impar = mascara_impar | (mascara_impar << 16); // mascara_impar = 1010 1010 1010 1010 1010 1010 1010 1010
  resultado = x & mascara_impar; // si x tiene un 1 en algun bit impar => resultado != 0, caso contrario resultado = 0
  return !!resultado; // resultado = 0 => !resultado = 1 => !1 = 0. resultado != 0 => !resultado = 0 => !0 = 1
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int shift_n = n << 3; // n * 8
  int shift_m = m << 3; // m * 8
  int byte_n = (x >> shift_n) & 0xFF;
  int byte_m = (x >> shift_m) & 0xFF;

  int mascara_n = 0xFF << shift_n;
  int mascara_m = 0xFF << shift_m;

  x = x & ~mascara_n; // con x = 0x12345678 --> x = 0x12340078
  x = x & ~mascara_m; // x = 0x00340078

  x = x | (byte_n << shift_m); // x = 0x56340078
  x = x | (byte_m << shift_n); // x = 0x56341278
  return x;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int shift = 32 + (~n + 1); // 32 - n
  int resultado = x ^ ((x << shift) >> shift);
  return !resultado;
}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
  int mascara_impar = 0xAA; // 1010 1010
  mascara_impar = mascara_impar | (mascara_impar << 8); // mascara_impar = 1010 1010 1010 1010
  mascara_impar = mascara_impar | (mascara_impar << 16); // mascara_impar = 1010 1010 1010 1010 1010 1010 1010 1010
  return mascara_impar;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
    int signo = x >> 31; // positivo => 0 ; negativo => -1
    return signo | !!x; // !!x = 0 si x = 0 ; !!x = 1 si x != 0
}
//3
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int suma = x + y;
  int overflow = ((x ^ suma) & (y ^ suma)) >> 31; // overflow != 0 si hay overflow ; overflow = 0 si no hay overflow 
  return !overflow;
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
  int not_0 = ~0;
  int a = not_0 << highbit;
  int resultado = (not_0 << lowbit) & (~(a << 1));
  return resultado;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int mascara = !!x;      // Si x es diferente de 0, mask = 1; de lo contrario, mask = 0
  mascara = ~mascara + 1;    // Si mask = 1, entonces es -1 (todos los bits en 1); si mask = 0, entonces sigue siendo 0
  return (mascara & y) | (~mascara & z);  
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int mascara1 = 0x55 | (0x55 << 8);
  int mascara2 = 0x33 | (0x33 << 8);
  int mascara4 = 0x0F | (0x0F << 8);
  int mascara8 = 0xFF | (0xFF << 16);
  int mascara16 = 0xFF | (0xFF << 8);
  mascara1 |= (mascara1 << 16);
  mascara2 |= (mascara2 << 16);
  mascara4 |= (mascara4 << 16);

  x = (x & mascara1) + ((x >> 1) & mascara1);
  x = (x & mascara2) + ((x >> 2) & mascara2);
  x = (x & mascara4) + ((x >> 4) & mascara4);
  x = (x & mascara8) + ((x >> 8) & mascara8);
  x = (x & mascara16) + ((x >> 16) & mascara16);

  return x;
}
/* 
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and & 
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ & |
 *   Max ops: 14
 *   Rating: 1
 */
int bitMatch(int x, int y) {
  return (x & y) | (~x & ~y);
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int shift = n << 3;  // (n * 8)
  int mascara = 0xFF << shift;
  int nuevo_byte = c << shift;
  return (x & ~mascara) | nuevo_byte;
}
//4
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum negative value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  int suma = x + y;

  int signo_x = x >> 31;
  int signo_y = y >> 31;
  int signo_suma = suma >> 31;

  int suma_es_cero = !suma;

  int signo_xy = signo_x ^ signo_y;
  int signo_xsuma = signo_x ^ signo_suma;

  int temp = suma_es_cero & signo_x;
  int overflow = (~signo_xy) & signo_xsuma & (~temp);

  int INT_MIN = 1 << 31;
  int INT_MAX = ~INT_MIN;

  int sat_value = (signo_x & INT_MIN) | (~signo_x & INT_MAX);

  int result = (overflow & sat_value) | (~overflow & suma);

  return result;
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x80000001) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
    int doubled = x << 1;  // Multiplicamos por 2
    int Tmin = 1 << 31;    // Tmin es 0x80000000
    int Tmax = ~Tmin;      // Tmax es 0x7FFFFFFF

    // Determinamos si hay overflow comparando los signos
    int sign_x = x >> 31;        // Signo de x
    int sign_doubled = doubled >> 31;  // Signo del resultado multiplicado
    int overflow = sign_x ^ sign_doubled;  // Si los signos son distintos, hay overflow

    // Si hay overflow, seleccionamos Tmin o Tmax según el signo original
    int result_if_overflow = (sign_x & Tmin) | (~sign_x & Tmax);
    
    // Si no hay overflow, el resultado es simplemente el doble
    return (overflow & result_if_overflow) | (~overflow & doubled);
}
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
  int msb_sign = x | (~x + 1); // (~x + 1) = -x
  msb_sign = (msb_sign >> 31);
  return msb_sign & 1;
} 
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x187654321
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  return (x >> n) ^ ((x ^ (x >> 31)) << (31 ^ n) << 1);
}
//float
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  unsigned mask = 0x7FFFFFFF;   // Máscara para borrar el bit de signo
  unsigned absVal = uf & mask;  // Obtener el valor absoluto

  unsigned exp = (uf >> 23) & 0xFF;  // Extraer el exponente (bits 30-23)
  unsigned frac = uf & 0x7FFFFF;     // Extraer la mantisa (bits 22-0)

  // Detectar si es NaN: exp == 0xFF y frac != 0
  unsigned isNaN = (exp == 0xFF) & (frac != 0);

  // Si es NaN, retornar el número original; de lo contrario, retornar el valor absoluto
  return (isNaN ? uf : absVal);
}
/* 
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) {
  unsigned exp_mask = 0xFF << 23;  // Máscara para el exponente
  unsigned frac_mask = 0x7FFFFF;   // Máscara para la mantisa

  // Si uf o ug son NaN, devolver 0
  unsigned is_nan_uf = ((uf & exp_mask) == exp_mask) && (uf & frac_mask);
  unsigned is_nan_ug = ((ug & exp_mask) == exp_mask) && (ug & frac_mask);
  unsigned is_nan = is_nan_uf || is_nan_ug;

  // Si ambos son +0.0 o -0.0, devolver 1
  unsigned zero_case = ((uf & 0x7FFFFFFF) == 0) && ((ug & 0x7FFFFFFF) == 0);

  // Compara los números directamente
  return !is_nan && (zero_case || uf == ug);
}
/* 
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
  unsigned exp = (uf >> 23) & 0xFF;  // Extraer el exponente
  unsigned frac = uf & 0x7FFFFF;     // Extraer la mantisa

  // Si es NaN, devolver el número sin cambios
  if (exp == 0xFF && frac != 0) {
      return uf;
  }

  // De lo contrario, invertir el bit de signo
  return uf ^ 0x80000000;  // Invertir el bit de signo
}
/* 
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug) {
  unsigned sign_uf = uf >> 31;  // Bit de signo de uf
  unsigned sign_ug = ug >> 31;  // Bit de signo de ug

  unsigned exp_uf = (uf >> 23) & 0xFF;  // Exponente de uf
  unsigned exp_ug = (ug >> 23) & 0xFF;  // Exponente de ug

  unsigned frac_uf = uf & 0x7FFFFF;  // Mantisa (fracción) de uf
  unsigned frac_ug = ug & 0x7FFFFF;  // Mantisa (fracción) de ug

  // Comprobar si cualquiera de los números es NaN (exponente = 255 y mantisa no es 0)
  int is_nan_uf = (exp_uf == 0xFF) && (frac_uf != 0);
  int is_nan_ug = (exp_ug == 0xFF) && (frac_ug != 0);
  if (is_nan_uf || is_nan_ug) {
    return 0;  // Si alguno es NaN, devolvemos 0
  }

  // Comprobar si ambos son +0.0 o -0.0 (se consideran iguales, por lo que no hay "menor que")
  if ((uf & 0x7FFFFFFF) == 0 && (ug & 0x7FFFFFFF) == 0) {
    return 0;
  }

  // Si los signos son diferentes
  if (sign_uf != sign_ug) {
    return sign_uf > sign_ug;  // Si uf es negativo y ug es positivo, devolver 1 (uf < ug)
  }

  // Ambos tienen el mismo signo
  if (sign_uf == 0) {
    // Si ambos son positivos, comparar normalmente
    return uf < ug;
  } else {
    // Si ambos son negativos, la comparación es inversa
    return uf > ug;
  }
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int sign = (uf >> 31) & 1;
  int exp = ((uf >> 23) & 0xFF) - 127;
  unsigned frac = (uf & 0x7FFFFF) | 0x800000;
  int result;

  if (exp >= 31) {
    return 0x80000000;
  }
  if (exp < 0) {
    return 0;
  }

  
  if (exp > 23) {
    result = frac << (exp - 23);
  } else {
    result = frac >> (23 - exp);
  }

  return sign ? -result : result;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  if (x < -126) {
    return 0;
  }
  if (x > 127) {
    return 0x7F800000;
  }
  return (x + 127) << 23;
}
