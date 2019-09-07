#ifndef _POL_PROB_H
#define _POL_PROB_H 1

#include <random>
#include <vector>

namespace polaris
{

template<typename _Tp>
class card_pool
{
public:
    using value_type = _Tp;

private:
    std::mt19937 _M_gen;
    _Tp _M_def;
    std::vector<double> _M_prob;
    std::vector<_Tp> _M_value;

public:
    card_pool();
    card_pool(const value_type&);

    bool insert(const value_type&, double);
    bool erase(const value_type&);

    void set_default(const value_type&);

    const _Tp& take();
};

}

#endif /* _POL_PROB_H */
