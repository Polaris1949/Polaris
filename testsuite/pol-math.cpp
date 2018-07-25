#include <iostream>
#include <sstream>
#include <polaris/math>

std::size_t year_from_date(unsigned __date)
{
    return (__date / 10000);
}

std::size_t month_from_date(unsigned __date)
{
    return (__date / 100 % 100);
}

std::size_t day_from_date(unsigned __date)
{
    return (__date % 100);
}

bool is_leap_year(unsigned __year)
{
    return (((__year % 100) && !(__year % 4)) || !(__year % 400));
}

bool valid_date(unsigned __date)
{
    std::size_t __year = year_from_date(__date);
    std::size_t __month = month_from_date(__date);
    std::size_t __day = day_from_date(__date);

    if (__month < 1 || __day < 1) return false;

    switch (__month)
    {
        default:
            return false;
        case 1:
            return (__day <= 31);
        case 2:
            return (is_leap_year(__year) ? __day <= 29 : __day <= 28);
        case 3:
            return (__day <= 31);
        case 4:
            return (__day <= 30);
        case 5:
            return (__day <= 31);
        case 6:
            return (__day <= 30);
        case 7:
            return (__day <= 31);
        case 8:
            return (__day <= 31);
        case 9:
            return (__day <= 30);
        case 10:
            return (__day <= 31);
        case 11:
            return (__day <= 30);
        case 12:
            return (__day <= 31);
    }
}

int main()
{
    unsigned a[13]={0};

    for (unsigned i = 19000000u; i <= 20201231u; ++i)
    {
        if (!valid_date(i)) continue;

        if (pol::is_prime(i))
        {
            std::cout << i << ' ';
            ++a[month_from_date(i)];
        }
    }

    std::cout << "\n\n";

    for (unsigned i = 1u; i <= 12u; ++i)
        std::cout << i << ' ' << a[i] << '\n';

    return 0;
}
