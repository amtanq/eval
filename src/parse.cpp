#include "parse.h"

char lookahead;
int32_t lookcount;
int32_t precision;

long double ruleA() {
  return operate(ruleB, redirectA);
}

long double ruleB() {
  return operate(ruleC, redirectB);
}

long double ruleC() {
  return operate(ruleD, redirectC);
}

long double ruleD() {
  if (match('(')) {
    long double result = ruleA();
    if (!match(')')) throw ERROR_BRACKET;
    return result;
  }

  long double sign = 1.0L;
  if (match('+')) sign = +1.0L;
  if (match('-')) sign = -1.0L;

  long double result = parseToken();
  if (match('.')) {
    long double subResult = parseToken();
    long double exponent = floorl(log10l(subResult) + 1);
    if (exponent > precision) precision = exponent;
    result += subResult / powl(10, exponent);
  }
  return sign * result;
}

std::pair<char, long double> redirectA() {
  return redirect("+-", ruleB, redirectA);
}

std::pair<char, long double> redirectB() {
  return redirect("*/", ruleC, redirectB);
}

std::pair<char, long double> redirectC() {
  return redirect("^", ruleD, redirectC);
}

std::pair<char, long double> redirect(const char *operations, long double (*ruleFunction)(), std::pair<char, long double> (*redirectFunction)()) {
  if (!strchr(operations, lookahead)) return std::make_pair(0, 0.0L);
  char operation = lookahead;
  match(operation);
  return std::make_pair(operation, operate(ruleFunction, redirectFunction));
}

long double operate(long double (*ruleFunction)(), std::pair<char, long double> (*redirectFunction)()) {
  long double x = ruleFunction();
  std::pair<char, long double> y = redirectFunction();
  switch (y.first) {
    case '^': return powl(x, y.second);
    case '*': return x * y.second;
    case '/': return x / y.second;
    case '+': return x + y.second;
    case '-': return x - y.second;
    default: return x;
  }
}

bool match(char character) {
  if (character != lookahead) return false;
  do {
    lookahead = getchar();
    ++lookcount;
  } while (lookahead == ' ');
  return true;
}

long double parseToken() {
  if (!isdigit(lookahead)) throw ERROR_DIGIT;
  long double result = 0.0L;
  do {
    result = result * 10.0L + lookahead - '0';
    match(lookahead);
  } while (isdigit(lookahead));
  return result;
}

bool parseExpression() {
  lookahead = precision = lookcount = 0;
  printf("> ");
  match(lookahead);

  try {
    if (lookahead == '\n') return false;
    long double result = ruleA();
    if (lookahead != '\n') throw ERROR_OPERATOR;
    printf("< %.*Lf\n", precision, result);
  } catch (const char *expected) {
    printf("%*c\nERROR: %s EXPECTED\n", lookcount + 2, '^', expected);
    fflush(stdin);
  }
  return true;
}
