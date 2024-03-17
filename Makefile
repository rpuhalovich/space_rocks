build:
	cmake -B build -S .
	cmake --build build
	cp build/compile_commands.json compile_commands.json

xcode:
	cmake -B build -S . -GXcode

clean:
	rm -rf build compile_commands.json
