build:
	cmake -B build -S .
	cmake --build build
	cp build/compile_commands.json compile_commands.json

format:
	find src -iname "*.h" -o -iname "*.c" | xargs clang-format -i --style=file --verbose

xcode:
	cmake -S . -B xcode -GXcode -D CMAKE_C_COMPILER="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc"

clean:
	rm -rf build compile_commands.json

.PHONY: build xcode format clean
.SILENT:
