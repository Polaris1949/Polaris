#ifndef _POL_VERSION_H
#define _POL_VERSION_H

namespace polaris
{

#define CPP_USING_VERSION __cplusplus
#define CPP_1998_VERSION 199711L
#define CPP_2003_VERSION 200300L
#define CPP_2011_VERSION 201103L
#define CPP_2014_VERSION 201402L
#define CPP_2017_VERSION 201500L

#if CPP_USING_VERSION >= CPP_2017_VERSION
#define CPP_USING 2017
#elif CPP_USING_VERSION >= CPP_2014_VERSION
#define CPP_USING 2014
#elif CPP_USING_VERSION >= CPP_2011_VERSION
#define CPP_USING 2011
#elif CPP_USING_VERSION >= CPP_2003_VERSION
#define CPP_USING 2003
#elif CPP_USING_VERSION >= CPP_1998_VERSION
#define CPP_USING 1998
#else
#error bad c++ version
#endif

}

#endif
