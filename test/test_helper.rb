# frozen_string_literal: true

$LOAD_PATH.unshift File.expand_path("../lib", __dir__)
require "ruby_clang_fpe"

require "minitest/autorun"
require "minitest/unit"
require "pry"
require "pry-doc"
require "pry-rescue/minitest"
