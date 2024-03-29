#pragma once

#define PRINTF(VALUE, ...) Protostar::Core::Printf(VALUE, __VA_ARGS__)


#define WIDE1(x) L##x
#define WIDE2(x) WIDE1(x)
#define __WFUNCTION__ WIDE2(__FUNCTION__)

#if defined(_WIN32) || defined(_WIN64)
#define _WIN
#endif
