#include <iostream>
#include <polaris/experimental/cstring>
#include <cstring>

int
__glibc_strcmp (const char *p1, const char *p2)
{
  const unsigned char *s1 = (const unsigned char *) p1;
  const unsigned char *s2 = (const unsigned char *) p2;
  unsigned char c1, c2;

  do
    {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\0')
	return c1 - c2;
    }
  while (c1 == c2);

  return c1 - c2;
}

int main()
{
    /*
	std::cout << (pol::cstring("aaa") == "aaab") << '\n';
	std::cout << pol::length("fuck qyw") << '\n';
	std::cout << pol::length((const char*)nullptr) << '\n';
	std::cout << (pol::cstring("aaa") < "aaab") << '\n';
	std::cout << (std::string("aaa") < "aaab") << '\n';
	std::cout << (std::string("aaa").compare("aaaz")) << '\n';
	std::cout << ::strcmp("aaa", "aaaz") << '\n';
	std::cout << ::__glibc_strcmp("aaa", "aaaz") << '\n';
    int r = pol::strcmp("aaa", "aaaz");
    std::cout << r << '\n';
    */
    //std::cout << (pol::wcstring(L"aaa") == L"aaaz") << '\n';
    //std::ios_base::sync_with_stdio(false);
    std::cout << pol::u8cstring(u8"qyw") << '\n';
	return 0;
}
