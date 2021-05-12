#pragma once

#include "trace.h"
#include "libcommon/macroargument.h"
#include <sstream>

#if TRACING_ENABLED == 1

#define XTRACE(...) VFUNC(XTRACE, __VA_ARGS__)

#define XTRACE1(a)\
{\
std::wstringstream xtrace_ss;\
xtrace_ss << a;\
common::trace::Trace::DoTrace(__FUNCTIONW__, xtrace_ss.str().c_str());\
}

#define XTRACE2(a, b)\
{\
std::wstringstream xtrace_ss;\
xtrace_ss << a << b;\
common::trace::Trace::DoTrace(__FUNCTIONW__, xtrace_ss.str().c_str());\
}

#define XTRACE3(a, b, c)\
{\
std::wstringstream xtrace_ss;\
xtrace_ss << a << b << c;\
common::trace::Trace::DoTrace(__FUNCTIONW__, xtrace_ss.str().c_str());\
}

#define XTRACE4(a, b, c, d)\
{\
std::wstringstream xtrace_ss;\
xtrace_ss << a << b << c << d;\
common::trace::Trace::DoTrace(__FUNCTIONW__, xtrace_ss.str().c_str());\
}

#define XTRACE5(a, b, c, d, e)\
{\
std::wstringstream xtrace_ss;\
xtrace_ss << a << b << c << d << e;\
common::trace::Trace::DoTrace(__FUNCTIONW__, xtrace_ss.str().c_str());\
}

#define XTRACE6(a, b, c, d, e, f)\
{\
std::wstringstream xtrace_ss;\
xtrace_ss << a << b << c << d << e << f;\
common::trace::Trace::DoTrace(__FUNCTIONW__, xtrace_ss.str().c_str());\
}

#define XTRACE7(a, b, c, d, e, f, g)\
{\
std::wstringstream xtrace_ss;\
xtrace_ss << a << b << c << d << e << f << g;\
common::trace::Trace::DoTrace(__FUNCTIONW__, xtrace_ss.str().c_str());\
}

#define XTRACE8(a, b, c, d, e, f, g, h)\
{\
std::wstringstream xtrace_ss;\
xtrace_ss << a << b << c << d << e << f << g << h;\
common::trace::Trace::DoTrace(__FUNCTIONW__, xtrace_ss.str().c_str());\
}

#define XTRACE9(a, b, c, d, e, f, g, h, i)\
{\
std::wstringstream xtrace_ss;\
xtrace_ss << a << b << c << d << e << f << g << h << i;\
common::trace::Trace::DoTrace(__FUNCTIONW__, xtrace_ss.str().c_str());\
}

#define XTRACE10(a, b, c, d, e, f, g, h, i, j)\
{\
std::wstringstream xtrace_ss;\
xtrace_ss << a << b << c << d << e << f << g << h << i << j;\
common::trace::Trace::DoTrace(__FUNCTIONW__, xtrace_ss.str().c_str());\
}

#else
#define XTRACE(...)
#endif
