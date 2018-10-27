#include <iostream>
#include <polaris/version>

int main()
{
  std::cout << __POLLIB__ << '.' << __POLLIB_MINOR__
            << '.' << __POLLIB_PATCHLEVEL__ << '\n';
  std::cout << __cplusplus << '\n';
}
