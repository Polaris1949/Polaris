#ifndef _POL_UFSET_TCC
#define _POL_UFSET_TCC 1

namespace polaris
{

template<typename _Tp>
basic_ufset<_Tp>::
basic_ufset()
	: _M_parent{}, _M_rank{}
{}

template<typename _Tp>
_Tp&
basic_ufset<_Tp>::
parent(const value_type& __x)
{
	value_type& __res = this->_M_parent[__x];
	if (__res == value_type{}) __res = __x;
	return __res;
}

template<typename _Tp>
std::size_t&
basic_ufset<_Tp>::
rank(const value_type& __x)
{ return this->_M_rank[__x]; }

template<typename _Tp>
_Tp&
basic_ufset<_Tp>::
find(const value_type& __x)
{
	return this->parent(__x) == __x ? this->parent(__x)
		: this->parent(__x) = this->find(this->parent(__x));
}

template<typename _Tp>
bool
basic_ufset<_Tp>::
merge(const value_type& __x, const value_type& __y)
{
	value_type __rx{this->find(__x)};
	value_type __ry{this->find(__y)};

	if (__rx == __ry) return false;

	if (this->rank(__rx) < this->rank(__ry))
		this->parent(__rx) = __ry;
	else
	{
		this->parent(__ry) = __rx;

		if (this->rank(__rx) == this->rank(__ry))
			++this->rank(__rx);
	}

	return true;
}

template<typename _Tp>
bool
basic_ufset<_Tp>::
is_brother(const value_type& __x, const value_type& __y)
{ return this->find(__x) == this->find(__y); }

template<typename _Tp>
_Tp&
basic_ufset<_Tp>::
operator[] (const value_type& __x)
{ return this->find(__x); }

seq_ufset::
seq_ufset()
	: _M_parent{}, _M_rank{}
{}

seq_ufset::
seq_ufset(size_type __n)
	: _M_parent{}, _M_rank{}
{ this->init(__n); }

void
seq_ufset::
init(size_type __n)
{
	this->_M_parent.resize(__n);
	this->_M_rank.resize(__n);

	for (size_type __i{}; __i < __n; ++__i)
		this->_M_parent[__i] = __i;
}

std::size_t&
seq_ufset::
parent(const value_type& __x)
{ return this->_M_parent[__x]; }

const std::size_t&
seq_ufset::
parent(const value_type& __x) const
{ return this->_M_parent[__x]; }

std::size_t&
seq_ufset::
rank(const value_type& __x)
{ return this->_M_rank[__x]; }

const std::size_t&
seq_ufset::
rank(const value_type& __x) const
{ return this->_M_rank[__x]; }

std::size_t&
seq_ufset::
find(const value_type& __x)
{
	return this->_M_parent[__x] == __x ? this->_M_parent[__x]
		: this->_M_parent[__x] = this->find(this->_M_parent[__x]);
}

bool
seq_ufset::
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
seq_ufset::
is_brother(const value_type& __x, const value_type& __y)
{ return this->find(__x) == this->find(__y); }

std::size_t&
seq_ufset::
operator[] (const value_type& __x)
{ return this->find(__x); }

}

#endif
