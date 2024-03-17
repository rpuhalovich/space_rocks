build:
	cmake -B build -S .
	cmake --build build

xcode:
	cmake -B build -S . -GXcode

