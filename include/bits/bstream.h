#ifndef _POL_BSTREAM_H
#define _POL_BSTREAM_H 1

namespace polaris
{

/**
 *  @brief Forward declaration.
 *  @{
 */
template<typename>
class byte_stream;

template<size_t>
struct ignore_byte;
/**
 *  @}
 */

template<size_t _Num>
struct ignore_byte
{
	typedef ignore_byte<_Num> type;
	static constexpr size_t value = _Num;
};

template<typename _Tp>
class byte_stream
{
public:
	typedef _Tp stream_type;

private:
	_Tp _M_stream;

public:
	byte_stream() = default;
	byte_stream(_Tp&& __stream);

	void open(const std::string& __s, std::ios_base::openmode __mode);
	void close();
	bool is_open() const;

	template<typename _Up>
	byte_stream& operator >> (_Up& __x);

	template<typename _Up>
	byte_stream& operator << (const _Up& __x);

	template<size_t _BNum>
	byte_stream& operator >> (ignore_byte<_BNum>& __x);

	template<size_t _BNum>
	byte_stream& operator << (const ignore_byte<_BNum>& __x);
};

}

#endif
