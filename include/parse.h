#ifndef PARSE_H
#define PARSE_H

#include <utility>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>

long double ruleA();
long double ruleB();
long double ruleC();
long double ruleD();

std::pair<char, long double> redirectA();
std::pair<char, long double> redirectB();
std::pair<char, long double> redirectC();
std::pair<char, long double> redirect(const char *, long double (*)(), std::pair<char, long double> (*)());

long double operate(long double (*)(), std::pair<char, long double> (*)());
bool match(char);

long double parseToken();
bool parseExpression();

const char *const ERROR_BRACKET = "BRACKET";
const char *const ERROR_DIGIT = "DIGIT";
const char *const ERROR_OPERATOR = "OPERATOR";

#endif
