#include "ruby_clang_fpe.h"

VALUE rb_mRubyClangFpe;

void
Init_ruby_clang_fpe(void)
{
  rb_mRubyClangFpe = rb_define_module("RubyClangFpe");
}
