#include "translator.h"
#include <string>
#include <vector>

void redukcja_stosu(std::vector<char>& stos, const char& znak, std::string& wynik)
{
	int priorytet_znaku = check_priority(znak);
	int i = stos.size()-1;
	while (i >= 0)
	{
		if (priorytet_znaku > check_priority(stos[i]) || stos[i] == '(')
		{
			break;
		}
		else if (priorytet_znaku <= check_priority(stos[i]))
		{
			wynik += stos[i];
			stos.erase(stos.begin()+i);
		}
		i -= 1;
	}
	stos.push_back(znak);
}

void redukcja_stosu_nawias(std::vector<char>& stos, const char& znak, std::string& wynik)
{
	int i = stos.size() - 1;
	while (i >= 0)
	{
		if (stos[i] != '(')
		{
			wynik += stos[i];
			stos.erase(stos.begin() + i);
		}
		else
		{
			stos.erase(stos.begin() + i);
			break;
		}
		i -= 1;
	}
}

bool try_to_add_to_stack(std::vector<char> &stos, const char& znak, std::string &wynik)
{
	int priorytet_znaku = check_priority(znak);
	for (int i = stos.size() - 1; i >= 0; i--)
	{
		if (znak == '(' || stos[i] == '(')
		{
			stos.push_back(znak);
			return true;
		}
		else if (check_priority(stos[i]) >= priorytet_znaku)
		{
			return false;
		}
	}
	stos.push_back(znak);
	return true;
}

int check_priority(const char &znak)
{
	if (znak == '+' || znak == '-')
	{
		return 1;
	}
	else if (znak == '*' || znak == '/')
	{
		return 2;
	}
	else if(znak == '^')
	{
		return 3;
	}
}

void final_stack_cleanup(std::vector<char> stos, std::string wynik, std::string& input)
{
	for (int i = stos.size() - 1; i >= 0; i--)
	{
		wynik += stos[i];
	}
	input = wynik;
}

void translate(std::string& input)
{
	std::vector<char> stos;
	std::string wynik="";
	for (const auto &a : input)
	{
		if (a != '+' && a != '-' && a != '*' && a != '/' && a != '^' && a != '(' && a != ')')
		{
			wynik += a;
		}
		else if (a == '(')
		{
			stos.push_back(a);
		}
		else if (a != '(' && a != ')')
		{
			if (!try_to_add_to_stack(stos, a, wynik))
			{
				redukcja_stosu(stos, a, wynik);
			}
		}
		else
		{
			redukcja_stosu_nawias(stos, a, wynik);
		}
	}
	final_stack_cleanup(stos, wynik, input);
}
