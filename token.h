#pragma once

#include <sstream>
#include <vector>
using namespace std;

enum class TokenType {
  DATE,//дата
  EVENT,//событие
  COLUMN,//имеется ли date или event
  LOGICAL_OP, //логическая операция
  COMPARE_OP, // операция сравнения
  PAREN_LEFT, // (
  PAREN_RIGHT, // )
};

struct Token {
  const string value;    // значение
  const TokenType type;  // тип этого значения
};

vector<Token> Tokenize(istream& cl); // вектор команды Find или Del разложенный по Token
