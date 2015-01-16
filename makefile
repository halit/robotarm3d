all : main


main: main.cpp InitShader.cpp Model.cpp Parser.cpp
	g++ main.cpp Model.cpp InitShader.cpp Parser.cpp -o main -lglut -lGLEW -lGL -lglui -lGLU -I include/

clean:
	rm main
