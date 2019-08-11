#include <polaris/probability>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

struct card
{
    std::string talent;
    std::string name;

    static size_t t_number(std::string __x)
    {
        if (__x == "SS") return 5;
        else if (__x == "S") return 4;
        else if (__x == "A") return 3;
        else if (__x == "B") return 2;
        else if (__x == "C") return 1;
        else return 0;
    }

    static bool t_greater(std::string __x, std::string __y)
    {
        return t_number(__x) > t_number(__y);
    }

    bool operator < (const card& __rhs) const
    {
        return (this->talent == __rhs.talent ? this->name < __rhs.name
            : t_greater(this->talent, __rhs.talent));
    }

    friend std::ostream&
    operator << (std::ostream& __out, const card& __x)
    {
        __out << __x.talent << ' ' << __x.name;
        return __out;
    }
};

std::map<card, size_t> result;

int main()
{
    std::ifstream fin;
    size_t lang;

    lang = 0;
/*
    std::cout << "Resource language (0:en 1:zh): ";
    std::cin >> lang;
*/

    switch (lang)
    {
        case 0: fin.open("card.en"); break;
        case 1: fin.open("card.zh"); break;
        default: std::cerr << "Error\n"; return 1;
    }

    std::string talent, name;
    double prob;

    fin >> talent >> name;

    pol::card_pool<card> p{card{talent, name}};

    while (fin >> talent >> name >> prob)
        p.insert(card{talent, name}, prob);

    fin.close();

    std::cout << "Ready to take cards...\n";

    size_t num, i;
    std::cout << "Number: ";
    std::cin >> num;

    std::cout << "\n=== Result ===\n";

    for (i=0u; i<num; ++i)
    {
        card x = p.take();
        std::cout << x << '\n';
        ++result[x];
    }

    std::cout << "\n=== Summary ===\n";

    // bool ayoufat{};
    // bool ayouqyw{};
    bool agoldhand{};
    bool aexm{};

    size_t aexm_n{};

    for (auto& e : result)
    {
        std::cout << e.first << " * " << e.second << '\n';
        if (e.first.talent == "SS") agoldhand = true;
        if (e.first.talent == "S") ++aexm_n;
    }

    if (aexm_n >= 3) aexm = true;

/*
    if (result.size() == 1 && result.begin()->first.name == "Fatfat")
        ayoufat = true;

    if (result.size() == 1 && result.begin()->first.name == "QYW")
        ayouqyw = true;
*/

    bool achieve = /*ayoufat || ayouqyw ||*/ agoldhand || aexm;

    if (achieve)
    {
        std::cout << "\n=== Achievements ===\n";
        // if (ayoufat) std::cout << "You yourself are FATFAT!\n";
        // if (ayouqyw) std::cout << "You yourself are QYW!!!\n";
        if (agoldhand) std::cout << "You have a gold hand!\n";
        if (aexm) std::cout << "Exclaimation!\n";
    }
}
