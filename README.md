# RubyClangFpe

Format-preserving encryption for Ruby, based on https://github.com/mysto/clang-fpe.

## Installation

Add the following to the application's Gemfile:

    gem 'ruby_clang_fpe', github: 'dcluna/ruby-clang-fpe', submodules: true

## Usage

```ruby
fpe3_key = RubyClangFpe::FpeKey.generate_key(:ff3, "EF4359D8D580AA4F7F036D6F04FC6A942B7E151628AED2A6ABF7158809CF4F3C", "9A768A92F60E12D8", 26)

fpe3_key.encrypt("89012123456789000000789000000") # => "30859239999374053872365555822"
fpe3_key.decrypt("30859239999374053872365555822") # => "89012123456789000000789000000"
```

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake test` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and the created tag, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/dcluna/ruby-clang-fpe.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
