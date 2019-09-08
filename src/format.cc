#include <pol/format>

namespace pol
{

namespace __format
{
std::string buffer;
std::mutex mutex;
}

void
cfmt_lock()
{ __format::mutex.lock(); }

void
cfmt_unlock()
{ __format::mutex.unlock(); }

}
