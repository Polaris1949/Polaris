#include <iostream>
#include <string>
#include <polaris/switch>
using namespace std;
using namespace polaris;

int main()
{
	string s;
	cin >> s;
	
	try
	{
		cout << switch_case(
			/* switch (s) */
				s,
			/* default: */
				[]{return "identifier";},
			/* case {"int", "long", "short"}: */
				make_pair(make_tuple("int", "long", "short"),
					[]{return "keyword";}),
			/* case isnumber(s): */
				make_tuple([](const string& s)
				{
					bool f=isdigit(s.front());
					for (char c : s)
						if (!isdigit(c))
						{
							if (switch_case(
								/* switch(c): */
									c,
								/* default: */
									[]{return false;},
								/* case {'l', 'r', '.'}: */
									make_pair(make_tuple('l', 'f', '.'), 
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
					true, []{return "string";})
			) << endl;
	}
	catch (...)
	{
		cout << "error" << endl;
	}
	
	return 0;
}
