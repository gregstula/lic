#!/bin/sh 
exec ruby -x "$0" "$@"
#!ruby -W0
#
# Copyright © 2016 Gregory D. Stula 
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

module Lic

  DIR = "choosealicense.com/_licenses/"
  REGEX = /(\.html)$/

  def self.lucky_word
    words = "/usr/share/dict/words"
    word = ""
    if not File.exists?(words)
      word = "youre_not_using_a_real_unix_lmao"
    else
      dict = File.foreach(words).map { |line| line.split("\n") }
      count = dict.count
      num = rand(count)
      word = dict[num][0]
    end 
    word
  end

  def self.constexpr_power f
    raw_name = File.basename(f,File.extname(f))
    header = "#{raw_name}.hpp"
    delim = lucky_word 

    File.open("#{header}", 'w') do |ofstream|
      # prepend include guard and constexpr raw string utf8 literal syntax
      ofstream.puts "#ifndef #{raw_name}_hpp"
      ofstream.puts "#define #{raw_name}_hpp"
      ofstream.puts "constexpr auto = u8R\"#{delim}("
      File.foreach("#{DIR}#{f}") { |contents| ofstream.puts contents }
    end
    # append closing delimeter for raw string literal
    File.write("#{header}", ")#{delim}\"\n#endif", File.size("#{header}"), mode: 'a')
  end # def self.constexpr_is_power

end # module Lic

Dir.foreach(Lic::DIR) do |lic|
  unless lic == '.' || lic == '..'
    Lic::constexpr_power(lic)
    puts "#{File.basename(lic,File.extname(lic))}"
  end
end

