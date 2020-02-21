#include <pol/file>

#if __GNUC__
#include <ext/stdio_filebuf.h>
#include <ext/stdio_sync_filebuf.h>

namespace pol
{

namespace __file
{
using sync_buffer_t = __gnu_cxx::stdio_sync_filebuf<char>;
using buffer_t = __gnu_cxx::stdio_filebuf<char>;
}

c_file_t*
c_file(const std::istream& __f)
{
    if (std::ios_base::sync_with_stdio())
        return (static_cast<__file::sync_buffer_t*>(__f.rdbuf()))->file();
    else
        return (static_cast<__file::buffer_t*>(__f.rdbuf()))->file();
}

c_file_t*
c_file(const std::ostream& __f)
{
    if (std::ios_base::sync_with_stdio())
        return (static_cast<__file::sync_buffer_t*>(__f.rdbuf()))->file();
    else
        return (static_cast<__file::buffer_t*>(__f.rdbuf()))->file();
}

c_file_t*
c_file(const std::ifstream& __f)
{ return (static_cast<__file::buffer_t*>(__f.rdbuf()))->file(); }

c_file_t*
c_file(const std::ofstream& __f)
{ return (static_cast<__file::buffer_t*>(__f.rdbuf()))->file(); }

}

#else
#error library extension required
#endif
