#ifndef __PARSER_H__
#define __PARSER_H__

/* Include file stream library */
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>

/* Use the standart namespace */
using namespace std;

/* Include OpenGL requirements */
#include "Angel.h"
#include "Model.h"

/* Token types */
enum{INTEGER, FLOAT, VERTEX, FACE, END};

/* Parser class */
class Parser{
public:
	/* Default constructor */
	Parser(const char*);

	/* Parse text file to Model */
	Model* parse_to_model(vec3, GLfloat, GLfloat, GLfloat, void (*update)(Model*));
private:
	/* Parse helper functions */
	void read_number(void);
	void next_token(void);
	void parse_vertex(Model*, vec3);
	void parse_face(Model*);

	/* Input file stream for object */
	std::ifstream* file_stream;

	/* Requirements for tokenizer */
	char current_char;
	char token;
	float f_value;
	int i_value;
};

#endif