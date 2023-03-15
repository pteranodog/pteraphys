all: compile link

compile:
	g++ -c drivers/main.cpp -o objects/main.o -I"D:\cpplibs\SFML-2.5.1\include" -I"headers" -DSFML_STATIC -g
	g++ -c src/Vector.cpp -o objects/Vector.o -I"headers" -g
	g++ -c src/PointMass.cpp -o objects/PointMass.o -I"D:\cpplibs\SFML-2.5.1\include" -I"headers" -DSFML_STATIC -g
	g++ -c src/CircleAreaConstraint.cpp -o objects/CircleAreaConstraint.o -I"D:\cpplibs\SFML-2.5.1\include" -I"headers" -DSFML_STATIC -g
	g++ -c src/LinkConstraint.cpp -o objects/LinkConstraint.o -I"D:\cpplibs\SFML-2.5.1\include" -I"headers" -DSFML_STATIC -g
	g++ -c src/Simulation.cpp -o objects/Simulation.o -I"D:\cpplibs\SFML-2.5.1\include" -I"headers" -DSFML_STATIC -g

link:
	g++ -static objects/* -o builds/pteraphys -L"D:\cpplibs\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -g -mwindows

clean:
	del /f /s /q objects builds