#include <pol/log>
#include <pol/format>
#include <iostream>
#include <sys/time.h>

namespace pol
{

namespace __log
{
std::FILE*
device{stderr};

uint8_t
flag{1};

constexpr fmt::text_style
cl_error{fmt::fg(fmt::terminal_color::bright_red)};

constexpr fmt::text_style
cl_warning{fmt::fg(fmt::terminal_color::bright_magenta)};

constexpr fmt::text_style
cl_note{fmt::fg(fmt::terminal_color::bright_cyan)};

log_fun_t fun = logm_cerr;

std::string file_path = "/dev/stderr";
}

void
__log_set_device(c_file_t* __d) noexcept
{ __log::device = __d; }

c_file_t*
__log_get_device() noexcept
{ return __log::device; }

void
__log_set_flag(uint8_t __f) noexcept
{ __log::flag = __f; }

uint8_t
__log_get_flag() noexcept
{ return __log::flag; }

void
error_easy(const std::string& __s)
{
    std::FILE* device{__log_get_device()};
    if (__log_get_flag())
    {
        fmt::print(device, __log::cl_error, "error: ");
        fmt::print(device, "{}\n", __s);
    }
    else
        fmt::print(device, "error: {}\n", __s);
}

void
warning_easy(const std::string& __s)
{
    std::FILE* device{__log_get_device()};
    if (__log_get_flag())
    {
        fmt::print(device, __log::cl_warning, "warning: ");
        fmt::print(device, "{}\n", __s);
    }
    else
        fmt::print(device, "warning: {}\n", __s);
}

void
note_easy(const std::string& __s)
{
    std::FILE* device{__log_get_device()};
    if (__log_get_flag())
    {
        fmt::print(device, __log::cl_note, "note: ");
        fmt::print(device, "{}\n", __s);
    }
    else
        fmt::print(device, "note: {}\n", __s);
}

void
set_log_fun(log_fun_t f)
{
    __log::fun = f;
}

log_fun_t
get_log_fun()
{
    return __log::fun;
}

const char*
log_prio_name(log_priority n)
{
    switch (n)
    {
        case log_priority::error:
            return "Error";
        case log_priority::warning:
            return "Warning";
        case log_priority::note:
            return "Note";
        case log_priority::info:
            return "Info";
        case log_priority::verbose:
            return "Verbose";
        case log_priority::debug:
            return "Debug";
        case log_priority::event:
            return "Event";
        default:
            return "Unknown";
    }
}

int
logm_cerr(const char* s)
{
    std::cerr << s << '\n';
    return 0;
}

int
logm_file(const char* s)
{
    std::ofstream fout(__log::file_path, std::ios_base::out | std::ios_base::app);
    fout << s << '\n';
    return !fout;
}

std::string
__log_head(log_priority prio, const std::string& mod, int code)
{
    ::timeval now;
    ::gettimeofday(&now, nullptr);
    ::tm *ltm = ::localtime(&now.tv_sec);
    int& year = ltm->tm_year;
    int& mon = ltm->tm_mon;
    int& mday = ltm->tm_mday;
    int& hour = ltm->tm_hour;
    int& min = ltm->tm_min;
    int& sec = ltm->tm_sec;
    int msec = now.tv_usec / 1000;
    std::string s = fmt::format("[{}-{:02}-{:02} {:02}:{:02}:{:02} {:03}] | {} | [{}] |{:#010x}| ",
        1900 + year, 1 + mon, mday, hour, min, sec, msec, log_prio_name(prio), mod,
        static_cast<unsigned int>(code));
    return s;
}

std::string
log_srcloc(srcloc_t loc)
{
    return fmt::format("{}:{}|{}| ", loc.file_name(), loc.line(), loc.function_name());
}

}
