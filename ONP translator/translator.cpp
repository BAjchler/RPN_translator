#include "translator.h"
#include <string>
#include <vector>

// Regular case for the "stack" reduction, called when the program stumbles upon any arithmetic operation symbol.
// It ouputs everything of a higher or equal priority that was already in the stack in the LIFO order.
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

// Special case for the "stack" reduction, called when the program stumbles upon the close parenthesis symbol.
// It ouputs everything that was inside the parentheses in the LIFO order.
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

//Function that checks whether a character can be added to the stack, by checking priority of previous characters.
//If a character can be added it adds it and returns true, otherwise it returns false.
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

// A simple function that allows to check what prioirty does a character hold.

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

// At the end of the program, the function adds any characters that are still on the stack, to the final output 
void final_stack_cleanup(std::vector<char> stos, std::string wynik, std::string& input)
{
	for (int i = stos.size() - 1; i >= 0; i--)
	{
		wynik += stos[i];
	}
	input = wynik;
}

//Main function for translation logic. 
//Reads a character, and depending on the character sends to the relevant function
void translate(std::string& input)
{
	std::vector<char> stos;
	std::string wynik="";
	for (const auto &a : input)
	{
		// If a character is a variable or a number it gets written straight into the final string
		if (a != '+' && a != '-' && a != '*' && a != '/' && a != '^' && a != '(' && a != ')')
		{
			wynik += a;
		}
		// If a character is the left parenthesis character, it gets added to the "stack". 
		// Which in this case is represented by a char vector.
		else if (a == '(')
		{
			stos.push_back(a);
		}
		// If a character is an arithmetic operator it is checked if it can be added to the "stack",
		// if not a special function reduces the stack.
		else if (a != '(' && a != ')')
		{
			if (!try_to_add_to_stack(stos, a, wynik))
			{
				redukcja_stosu(stos, a, wynik);
			}
		}
		// If the character is a close parenthesis character, inside of the stack also gets reduced by a special function.
		else
		{
			redukcja_stosu_nawias(stos, a, wynik);
		}
	}
	final_stack_cleanup(stos, wynik, input);
}
