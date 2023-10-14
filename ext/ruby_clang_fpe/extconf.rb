# frozen_string_literal: TRUE

require "mkmf"

openssl_include_dir, openssl_lib_dir = dir_config("openssl", "include", "lib")

openssl_dir = File.dirname openssl_include_dir

find_header "string.h"
find_header "openssl/bn.h"
find_header "openssl/aes.h"

clang_fpe_include_dir, clang_fpe_lib_dir = dir_config("clang-fpe", "src", "./")

clang_fpe_dir = File.dirname clang_fpe_include_dir

if clang_fpe_dir == "."
  clang_fpe_dir = (File.expand_path File.dirname(__FILE__) + "/../../vendor/clang-fpe" )
  clang_fpe_lib_dir = clang_fpe_dir
  clang_fpe_include_dir = clang_fpe_dir + "/src"
end

Dir.chdir clang_fpe_dir do
  system "CFLAGS='-I#{openssl_include_dir}' LDFLAGS='-L#{openssl_lib_dir}' make" if Dir["**/libfpe.a"].empty?
end

libfpe = Dir[clang_fpe_dir + "/**/libfpe.a"].first

$LOCAL_LIBS << "'#{libfpe}'"

find_header "fpe.h", clang_fpe_include_dir
find_header "fpe_locl.h", clang_fpe_include_dir

create_makefile("ruby_clang_fpe/ruby_clang_fpe")
