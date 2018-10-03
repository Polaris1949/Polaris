#define POL_DEBUG 1
#include <cerrno>
#include <polaris/tree>

int main()
{
    auto p = (new pol::tree_node_base)->ptr_unique();
}
