#ifndef _POL_BSTREAM_TCC
#define _POL_BSTREAM_TCC 1

namespace polaris
{

template<typename _Tp>
byte_stream<_Tp>::
byte_stream(_Tp&& __stream)
	: _M_stream(std::move(__stream))
{
}

template<typename _Tp>
void
byte_stream<_Tp>::
open(const std::string& __s, std::ios_base::openmode __mode)
{
	_M_stream.open(__s, std::ios_base::binary | __mode);
}

template<typename _Tp>
void
byte_stream<_Tp>::
close()
{
	_M_stream.close();
}

template<typename _Tp>
bool
byte_stream<_Tp>::
is_open() const
{
	return _M_stream.is_open();
}

template<typename _Tp>
template<typename _Up>
byte_stream<_Tp>&
byte_stream<_Tp>::
operator >> (_Up& __x)
{
	std::string __buf;
	__buf.resize(sizeof(__x));
	_M_stream.read(const_cast<char*>(__buf.c_str()), __buf.size());
	memcpy(reinterpret_cast<char*>(&__x), __buf.c_str(), __buf.size());
	return *this;
}

template<typename _Tp>
template<typename _Up>
byte_stream<_Tp>&
byte_stream<_Tp>::
operator << (const _Up& __x)
{
	_M_stream.write(reinterpret_cast<const char*>(&__x), sizeof(__x));
	return *this;
}

template<typename _Tp>
template<size_t _BNum>
byte_stream<_Tp>&
byte_stream<_Tp>::
operator >> (ignore_byte<_BNum>& __x)
{
	std::string __buf;
	__buf.resize(_BNum);
	_M_stream.read(const_cast<char*>(__buf.c_str()), __buf.size());
	return *this;
}

template<typename _Tp>
template<size_t _BNum>
byte_stream<_Tp>&
byte_stream<_Tp>::
operator << (const ignore_byte<_BNum>& __x)
{
	std::string __buf;
	__buf.resize(_BNum);
	_M_stream.write(__buf.c_str(), __buf.size());
	return *this;
}

}

#endif
