#include <iostream>
#include <string>
#include <polaris/switch>
using namespace std;
using namespace polaris;

int main()
{

string s;

while (cin >> s)
{

try
{
	cout << switch_case(
	/* switch (s) */
		s,
	/* default: */
		[]{return "identifier";},
	/* case {"int", "long", "short"}: */
		make_pair(make_tuple("alignas", "alignof", "and", "and_eq", "asm", \
			"atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", \
			"bitand", "bitor", "bool", "break", "case", "catch", "char", \
			"char16_t", "char32_t", "class", "compl", "concept", "const", \
			"constexpr", "const_cast", "continue", "co_await", "co_return", \
			"co_yield", "decltype", "default", "delete", "do", "double", \
			"dynamic_cast", "else", "enum", "explicit", "export", "extern", \
			"false", "float", "for", "friend", "goto", "if", "import", \
			"inline", "int", "long", "module", "mutable", "namespace",
			"new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", \
			"or_eq", "private", "protected", "public", "register", \
			"reinterpret_cast", "requires", "return", "short", "signed", \
			"sizeof", "static", "static_assert", "static_cast", "struct", \
			"switch", "synchronized", "template", "this", "thread_local", \
			"throw", "true", "try", "typedef", "typeid", "typename", \
			"union", "unsigned", "using", "virtual", "void", "volatile", \
			"wchar_t", "while", "xor", "xor_eq"), []{return "keyword";}),
	/* case isnumber(s): */
		make_tuple([](const string& s)
		{
			bool f=isdigit(s.front());
			bool hex=false;
			for (char c : s)
				if (!isdigit(c))
				{
					if (c=='x'&&!hex)
						hex=true;
					else if (switch_case(
						/* switch(c): */
							c,
						/* default: */
							[]{return false;},
						/* case {'l', 'r', '.'}: */
							make_pair(make_tuple('l', 'f', '.'), 
								[]{return true;})
						))
						continue;
					else if (hex && switch_case(
						/* switch(c): */
							c,
						/* default: */
							[]{return false;},
						/* case {...}: */
							make_pair(make_tuple('a', 'b', 'c', 'd', \
								'e', 'f'), 
								[]{return true;})
						))
						continue;
					else if (f) throw exception();
					else return false;
				}
			return true;
		},
			true, []{return "number";}),
	/* case ispreprocessor(s): */
		make_tuple([](const string& s)
		{
			return s.front()=='#';
		},
			true, []{return "preprocessor";}),
	/* case ischaracter(s): */
		make_tuple([](const string& s)
		{
			bool f=s.front()=='\'';
			bool b=s.back()=='\'';
			if (f&&b) return true;
			if (f||b) throw exception();
			return false;
		},
			true, []{return "character";}),
	/* case isstring(s): */
		make_tuple([](const string& s)
		{
			bool f=s.front()=='\"';
			bool b=s.back()=='\"';
			if (f&&b) return true;
			if (f||b) throw exception();
			return false;
		},
			true, []{return "string";}),
	/* case operator: */
		make_tuple([](const string& s)
		{
			for (char ch:s)
				if (!ispunct(ch)) return false;
			return true;
		},
			true, []{return "operator";})
	) << endl;
}
catch (...)
{
	cout << "error" << endl;
}

}

return 0;

}
