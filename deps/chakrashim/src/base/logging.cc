// Copyright 2006-2008 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/base/logging.h"

#include <cstdio>
#include <cstdlib>

#include "src/base/platform/platform.h"

namespace v8 {
namespace base {

// Explicit instantiations for commonly used comparisons.
#define DEFINE_MAKE_CHECK_OP_STRING(type)              \
  template std::string* MakeCheckOpString<type, type>( \
      type const&, type const&, char const*);
DEFINE_MAKE_CHECK_OP_STRING(unsigned long long)  // NOLINT(runtime/int)
#undef DEFINE_MAKE_CHECK_OP_STRING


// Explicit instantiations for floating point checks.
#define DEFINE_CHECK_OP_IMPL(NAME)                          \
  template std::string* Check##NAME##Impl<float, float>(    \
      float const& lhs, float const& rhs, char const* msg); \
  template std::string* Check##NAME##Impl<double, double>(  \
      double const& lhs, double const& rhs, char const* msg);
DEFINE_CHECK_OP_IMPL(LT)
#undef DEFINE_CHECK_OP_IMPL

}  // namespace base
}  // namespace v8


// Contains protection against recursive calls (faults while handling faults).
extern "C" void V8_Fatal(const char* file, int line, const char* format, ...) {
  fflush(stdout);
  fflush(stderr);
  v8::base::OS::PrintError("\n\n#\n# Fatal error in %s, line %d\n# ", file,
                           line);
  va_list arguments;
  va_start(arguments, format);
  v8::base::OS::VPrintError(format, arguments);
  va_end(arguments);
  v8::base::OS::PrintError("\n#\n");

  fflush(stderr);
  v8::base::OS::Abort();
}
