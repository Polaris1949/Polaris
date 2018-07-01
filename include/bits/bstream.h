#ifndef _POL_BSTREAM_H
#define _POL_BSTREAM_H 1

namespace polaris
{

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
};

}

#endif
