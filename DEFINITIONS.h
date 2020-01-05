#pragma once

//   Plik, do którego nale¿y wrzucaæ wszystkie #define i sta³e, które bêd¹ u¿ywane wiele razy, jak np. œcie¿ki plików itp. ¿eby móc zmieniæ to tylko tu i mieæ zmienione wszêdzie.

constexpr auto EMPTY = 999;

enum class Direction {LEFT, RIGHT, STOP};
enum class Operation {ADD, SUB, MUL, DIV};