#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <vector>
#include <string>
void translate(std::string& input);
void redukcja_stosu(std::vector<char>& stos, const char& znak, std::string& wynik);
void redukcja_stosu_nawias(std::vector<char>& stos, const char& znak, std::string& wynik);
bool try_to_add_to_stack(std::vector<char>& stos, const char& znak, std::string& wynik);
void final_stack_cleanup(std::vector<char> stos, std::string wynik, std::string& input);
int check_priority(const char& znak);
#endif
