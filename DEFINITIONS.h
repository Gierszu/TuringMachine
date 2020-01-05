#pragma once

//   Plik, do którego należy wrzucać wszystkie #define i stałe, które będą używane wiele razy, jak np. ścieżki plików itp. żeby móc zmienić to tylko tu i mieć zmienione wszędzie.

constexpr auto EMPTY =999;

enum class Direction {LEFT, RIGHT, STOP};
enum class Operation {ADD, SUB, MUL, DIV};
