#ifndef _POL_UFSET_TCC
#define _POL_UFSET_TCC 1

namespace polaris
{

template<typename _Tp>
ufset<_Tp>::
ufset()
	: _M_parent{}, _M_rank{}
{}

ufset<std::size_t>::
ufset()
	: _M_parent{}, _M_rank{}
{}

ufset<std::size_t>::
ufset(size_type __n)
	: _M_parent{}, _M_rank{}
{ this->init(__n); }

void
ufset<std::size_t>::
init(size_type __n)
{
	this->_M_parent.resize(__n);
	this->_M_rank.resize(__n);

	for (size_type __i{}; __i < __n; ++__i)
		this->_M_parent[__i] = __i;
}

std::size_t&
ufset<std::size_t>::
parent(const value_type& __x)
{ return this->_M_parent[__x]; }

const std::size_t&
ufset<std::size_t>::
parent(const value_type& __x) const
{ return this->_M_parent[__x]; }

std::size_t&
ufset<std::size_t>::
rank(const value_type& __x)
{ return this->_M_rank[__x]; }

const std::size_t&
ufset<std::size_t>::
rank(const value_type& __x) const
{ return this->_M_rank[__x]; }

std::size_t&
ufset<std::size_t>::
find(const value_type& __x)
{
	return this->_M_parent[__x] == __x ? this->_M_parent[__x]
		: this->_M_parent[__x] = this->find(this->_M_parent[__x]);
}

bool
ufset<std::size_t>::
merge(const value_type& __x, const value_type& __y)
{
	value_type __rx{this->find(__x)};
	value_type __ry{this->find(__y)};

	if (__rx == __ry) return false;

	if (this->_M_rank[__rx] < this->_M_rank[__ry])
		this->_M_parent[__rx] = __ry;
	else
	{
		this->_M_parent[__ry] = __rx;

		if (this->_M_rank[__rx] == this->_M_rank[__ry])
			++this->_M_rank[__rx];
	}

	return true;
}

bool
ufset<std::size_t>::
is_brother(const value_type& __x, const value_type& __y)
{ return this->find(__x) == this->find(__y); }

std::size_t&
ufset<std::size_t>::
operator[] (const value_type& __x)
{ return this->find(__x); }

}

#endif
