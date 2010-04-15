# Turns an enum into an array.
if ARGV.size() == 1
    File.open(ARGV[0], "r") do |infile|
	puts "String #{ARGV[0]}_Strings[]"
	puts "{"
	while (line = infile.gets)
	    if( ! ((line.include? "{") || (line.include? "}") || (line.include? "enum")))
		puts("\t\"#{line.split(',')[0].strip}\",")
	    end
	end
	puts "}"
    end
else
    puts "Usage : #{$0} filename"
end
	
