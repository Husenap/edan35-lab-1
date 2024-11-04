BUILD_DIRECTORY=build
CMAKE_GEN_FLAGS=-B${BUILD_DIRECTORY} -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

.PHONY: gen build run

gen:
	cmake . ${CMAKE_GEN_FLAGS}

build:
	cmake --build ${BUILD_DIRECTORY}

run: build
	./build/raytracer

clean:
	rm -rf ${BUILD_DIRECTORY}
