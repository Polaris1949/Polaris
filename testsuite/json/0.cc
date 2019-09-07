#include <pol/json>
#include <iostream>

int main()
{
	pol::json j = pol::json::parse("{\"gay\": \"you\"}");
	std::cout << j << '\n';
}
