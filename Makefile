all: compile link

compile:
	g++ -c drivers/main.cpp -o objects/main.o -I"D:\cpplibs\SFML-2.5.1\include" -I"headers" -DSFML_STATIC
	g++ -c src/Vector.cpp -o objects/Vector.o -I"headers"
	g++ -c src/PointMass.cpp -o objects/PointMass.o -I"headers"

link:
	g++ -static objects/* -o builds/pteraphys -L"D:\cpplibs\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -mwindows
clean:
	rm -f objects/*.o builds/pteraphys