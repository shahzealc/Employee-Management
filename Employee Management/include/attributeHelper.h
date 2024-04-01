#ifndef attribute_flag
#define attribute_flag
#include <string>
#include "validate.h"
#include <functional>
#include <type_traits>

template<typename T, typename Validator>
bool setAttribute(const std::string& attributeName, T& attribute, Validator validator) {

	
	auto attempt{ 0 };

	while (attempt < 3) {
		++attempt;
		std::cout << attributeName << ": ";
		std::string input;
		std::cin >> input;
		//std::getline(std::cin, input);

		if (validator(input)) {
			if constexpr (std::is_same_v<T, int>) {
				attribute = std::stoi(input);
			}
			else if constexpr (std::is_same_v<T, float>) {
				attribute = std::stof(input);
			}
			else {
				attribute = input;
			}
			return true;
		}
		else {
			std::cout << "\033[31mInvalid input! Please try again.\033[0m\n";
		}
	}

	std::cout << "\033[31mMaximum attempts reached!\033[0m\n";
	return false;
}

#endif