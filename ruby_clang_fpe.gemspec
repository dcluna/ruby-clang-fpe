# frozen_string_literal: true

require_relative "lib/ruby_clang_fpe/version"

Gem::Specification.new do |spec|
  spec.name = "ruby_clang_fpe"
  spec.version = RubyClangFpe::VERSION
  spec.authors = ["Daniel Luna"]
  spec.email = ["dancluna@gmail.com"]

  spec.summary = "Ruby bindings for the Clang FPE library."
  spec.description = "Format-preserving encryption for Ruby, based on https://github.com/mysto/clang-fpe."
  spec.homepage = "https://github.com/dcluna/ruby_clang_fpe"
  spec.license = "MIT"
  spec.required_ruby_version = ">= 2.6.0"

  spec.metadata["allowed_push_host"] = "TODO: Set to your gem server 'https://example.com'"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/dcluna/ruby_clang_fpe"
  spec.metadata["changelog_uri"] = "https://github.com/dcluna/ruby_clang_fpe"

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  spec.files = Dir.chdir(__dir__) do
    `git ls-files -z --recurse-submodules`.split("\x0").reject do |f|
      (f == __FILE__) || f.match(%r{\A(?:(?:bin|test|spec|features)/|\.(?:git|circleci)|appveyor)})
    end
  end
  spec.bindir = "exe"
  spec.executables = spec.files.grep(%r{\Aexe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions = ["ext/ruby_clang_fpe/extconf.rb"]

  # Uncomment to register a new dependency of your gem
  # spec.add_dependency "example-gem", "~> 1.0"

  # For more information and examples about making a new gem, check out our
  # guide at: https://bundler.io/guides/creating_gem.html

  spec.add_development_dependency "pry"
  spec.add_development_dependency "pry-doc"
  spec.add_development_dependency "pry-rescue"
  spec.add_development_dependency "pry-stack_explorer"
end
