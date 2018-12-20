#pragma once
#include <string>

typedef void(*LinkSymbol)(const std::string& sym);

void linkSymbols(LinkSymbol linkSymbol);
