#include "text_handler.h"
#include <string>
void clean_text(std::string &input)
{
	std::string clean_input = "";
	for (auto a : input)
	{
		if (a != ' ' && a != '\n' && a != '\t')
		{
			clean_input += a;
		}
	}
	input = clean_input;
}