module RubyClangFpe
  class FpeKey
    def self.generate_key(type, key, tweak, radix)
      new_key = case type
                when :ff3
                  if (tweak.size / 2) == 7
                    generate_ff3_1_key(key, tweak, radix)
                  else
                    generate_ff3_key(key, tweak, radix)
                  end
                when :ff1
                  generate_ff1_key(key, tweak, radix)
                end

      new_key
    end

    private_class_method :generate_ff3_key, :generate_ff1_key, :generate_ff3_1_key
  end
end
