#pragma once

//   Plik, do kt�rego nale�y wrzuca� wszystkie #define i sta�e, kt�re b�d� u�ywane wiele razy, jak np. �cie�ki plik�w itp. �eby m�c zmieni� to tylko tu i mie� zmienione wsz�dzie.

constexpr auto EMPTY = 999;

enum class Direction {LEFT, RIGHT, STOP};
enum class Operation {ADD, SUB, MUL, DIV};