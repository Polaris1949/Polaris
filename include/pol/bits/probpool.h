#ifndef _POL_PROBPOOL_H
#define _POL_PROBPOOL_H 1

#include <random>
#include <vector>

namespace pol
{

template<typename _Tp>
class prn_pool
{
public:
    using value_type = _Tp;

public:
    prn_pool();

    void insert(const value_type&);

    value_type take();

private:
    std::mt19937 _M_gen;
    std::vector<_Tp> _M_data;
};

template<typename _Tp, typename _Up = uint64_t>
class prq_pool
{
public:
    using value_type = _Tp;
    using prob_type = _Up;

private:
    struct prq_data
    {
        _Tp value;
        _Up prob;

        prq_data(const _Tp& v, _Up p) : value(v), prob(p) {}
        operator _Up() const { return prob; }
    };

public:
    prq_pool();

    void insert(const value_type&, prob_type);

    value_type take();

private:
    std::mt19937 _M_gen;
    std::vector<prq_data> _M_data;
    _Up _M_sum;
};

template<typename _Tp, typename _Up = double>
class prf_pool
{
public:
    using value_type = _Tp;
    using prob_type = _Up;

private:
    struct prf_data
    {
        _Tp value;
        _Up prob;

        prf_data(const _Tp& v, _Up p) : value(v), prob(p) {}
        operator _Up() const { return prob; }
    };

public:
    prf_pool();

    void insert(const value_type&, prob_type);

    void check() const;

    value_type take();

private:
    std::mt19937 _M_gen;
    std::vector<prf_data> _M_data;
    _Up _M_sum;
};

}

#endif /* _POL_PROBPOOL_H */
