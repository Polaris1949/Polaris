#include <iostream>
#include <string>
#include <polaris/switch>

int main()
{
	std::string s;

	while (std::cin >> s)
	{
		try
		{
			std::cout << pol::switch_case(
/* switch (s) */
	s,
/* default: */
	[] { return "identifier"; },
/* case {"alignas", "alignof", "and", ..., "xor_eq"}: */
	std::make_pair(std::make_tuple("alignas", "alignof", "and", "and_eq",
		"asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto",
		"bitand", "bitor", "bool", "break", "case", "catch", "char",
		"char16_t", "char32_t", "class", "compl", "concept", "const",
		"constexpr", "const_cast", "continue", "co_await", "co_return",
		"co_yield", "decltype", "default", "delete", "do", "double",
		"dynamic_cast", "else", "enum", "explicit", "export", "extern",
		"false", "float", "for", "friend", "goto", "if", "import",
		"inline", "int", "long", "module", "mutable", "namespace",
		"new", "noexcept", "not", "not_eq", "nullptr", "operator", "or",
		"or_eq", "private", "protected", "public", "reflexpr", "register",
		"reinterpret_cast", "requires", "return", "short", "signed",
		"sizeof", "static", "static_assert", "static_cast", "struct",
		"switch", "synchronized", "template", "this", "thread_local",
		"throw", "true", "try", "typedef", "typeid", "typename",
		"union", "unsigned", "using", "virtual", "void", "volatile",
		"wchar_t", "while", "xor", "xor_eq"), [] { return "keyword"; }),
/* case is_number(s): */
	std::make_tuple(true, [] { return "number"; },
		[](const std::string& s)
	{
		bool f = isdigit(s.front());
		bool hex = false;

		for (char c : s)
			if (!isdigit(c))
			{
				if (c == 'x' && !hex)
					hex = true;
				else if (pol::switch_case(
/* switch(c): */
	c,
/* default: */
	[] { return false; },
/* case {'l', 'r', '.'}: */
	std::make_pair(std::make_tuple('l', 'f', '.'),
		[] { return true; })
						))
					continue;
				else if (hex && pol::switch_case(
/* switch(c): */
	c,
/* default: */
	[] { return false; },
/* case {'a', 'b', 'c', ..., 'f'}: */
	std::make_pair(std::make_tuple('a', 'b', 'c', 'd', 'e', 'f'),
		[] { return true; })
						))
					continue;
				else if (f) throw std::exception();
				else return false;
			}

		return true;
	}),
/* case is_preprocessor(s): */
	std::make_tuple(true, [] { return "preprocessor"; },
		[](const std::string& s) { return s.front() == '#'; }),
/* case is_character(s): */
	std::make_tuple(true, [] { return "character"; },
		[](const std::string& s)
	{
		bool f = (s.front() == '\'');
		bool b = (s.back() == '\'');
		if (f && b) return true;
		if (f || b) throw std::exception();
		return false;
	}),
/* case is_string(s): */
	std::make_tuple(true, [] { return "string"; },
		[](const std::string& s)
	{
		bool f = (s.front() == '\"');
		bool b = (s.back() == '\"');
		if (f && b) return true;
		if (f || b) throw std::exception();
		return false;
	}),
/* case is_operator(s): */
	std::make_tuple(true, [] { return "operator"; },
		[](const std::string& s)
	{
		for (char ch : s) if (!ispunct(ch)) return false;
		return true;
	})
				) << std::endl;
		}
		catch (...)
		{ std::cout << "error" << std::endl; }
	}

	return 0;
}
