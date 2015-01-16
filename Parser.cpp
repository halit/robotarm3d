/* Include parser header file */
#include "Parser.h"

/* Default constructor */
Parser::Parser(const char* file_name){
	file_stream = new ifstream(file_name, ifstream::in);
	current_char = '\0';
}

/* Get the next token */
void Parser::next_token(){
	while(file_stream->good()){
		/* Get one character */
		int ch = file_stream->get();
		current_char = (char)ch;

		/* Categorize the input */
		if((ch <= '9') && (ch >= '0') || (ch == '-')){
			read_number();
			return;
		}else if(ch == 'v'){
			token = VERTEX;
			return;
		}else if(ch == 'f'){
			token = FACE;
			return;
		}
	}
	token = END;
}

void Parser::read_number(){
	int real_value = 0;
	int sign = 1;

	/* If the value is negative, check the sign */
	if(current_char == '-'){
		sign = -1;
	}else{
		real_value += (current_char - '0');
	}

	/* Read the integer part */
	while(file_stream->good()){
		int i = file_stream->get();
		current_char = (char)i;
		if(i == '.'){
			break;
		}else if((i > '9') || (i < '0')){
			token = INTEGER;
			i_value = sign * real_value;
			return;
		}
		real_value = (10 * real_value) + (i - '0');
	}

	/* Read the fractional part */
	float decimal_value = 0.0f;
	int place = 1;
	while(file_stream->good()){
		int i = file_stream->get();
		current_char = (char)i;
		if((i > '9') || (i < '0')){
			token = FLOAT;
			f_value = (float)sign * ((float)real_value + decimal_value);
			return;
		}
		decimal_value += ((float)(i - '0') / pow(10.0, (float)place));
		place++;
	}
	/* Token type is float */
	token = FLOAT;

	/* Get the real float value */
	f_value = (float)sign * ((float)real_value + decimal_value);
}

/* Parse the vertex coordinate and add to model with color */
void Parser::parse_vertex(Model* model, vec3 color){
	float values[3];
	for(int i=0;i<3;i++){
		next_token();
		switch(token){
			case INTEGER:
				values[i] = i_value;
				break;
			case FLOAT:
				values[i] = f_value;
				break;
		}
	}

	/* Add to model */
	model->add_vertex(vec3(values[0], values[1], values[2]), color);
}

/* Parse the face index and add to model */
void Parser::parse_face(Model* model){
	int values[3];
	for(int i=0;i<3;i++){
		next_token();
		switch(token){
			case INTEGER:
				values[i] = i_value;
				break;
		}
	}

	/* Add to model */
	model->add_face(values[0], values[1], values[2]);
}

/* Parse all file to model */
Model* Parser::parse_to_model(vec3 color, GLfloat x, GLfloat y, GLfloat z, void (*update)(Model*)){
	Model* model = new Model(x, y, z, update);
	while(token != END){
		next_token();
		switch(token){
			case VERTEX:
				parse_vertex(model, color);
				break;
			case FACE:
				parse_face(model);
				break;
		}
	}
	return model;
}