#ifndef _POL_UFSET_H
#define _POL_UFSET_H 1

namespace polaris
{

#if _POL_NEWLIB
template<typename _Tp>
class bhash
{
public:
	typedef _Tp value_type;
	typedef size_t size_type;
	
	size_type operator() (const value_type& __x) const;
	value_type operator[] (const size_type& __x) const;
};

template<>
class bhash<size_t>
{
public:
	typedef size_t value_type;
	typedef size_t size_type;
	
	size_type operator() (const value_type& __x) const;
	value_type operator[] (const size_type& __x) const;
};

// TODO:......\
template<typename _Tp>

template<typename _Tp = size_t, typename _Seq = std::deque<_Tp>, \
	typename _Hash = bhash<_Tp>>
class ufset
{
public:
	typedef _Tp value_type;
	typedef _Hash hash_function;
	
	using rebind = _Seq::rebind<size_t>;
	
private:
	sequence<size_t> _M_storage;
};

#else

template<typename _Tp = size_t>
class ufset
{
	typedef size_t(*_Hash)(const _Tp&);
	typedef _Tp(*_Unhash)(const size_t&);
	
public:
	typedef _Tp value_type;
	typedef size_t size_type;
	
private:
	sequence<size_t> _M_storage;
	_Hash _M_hash_fun;
	_Unhash _M_unhash_fun;
	
public:
	ufset();
	explicit ufset(size_type __n);
	
	_Hash& hash_func();
	_Unhash& unhash_func();
};

template<>
class ufset<size_t>
{
public:
	typedef size_t value_type;
	typedef size_t size_type;
	
private:
	sequence<size_t> _M_storage;
	
public:
	ufset();
	explicit ufset(size_type __n);
	
	void resize(size_type __new_size);
	
	value_type& operator[] (const value_type& __x);
	const value_type& operator[] (const value_type& __x) const;
};

#endif

}

#endif
