#ifndef __MODEL_H__
#define __MODEL_H__

/* Include vector library */
#include <vector>

/* Include OpenGL requirements */
#include "Angel.h"

/* Use the standart namespace */
using namespace std;

/* Model class */
class Model{
public:

	/* Default constructor with default max and min point values */
	Model(GLfloat x, GLfloat y, GLfloat z, void (*update)(Model*)): 
		min_point(vec3(1000.0f, 1000.0f, 1000.0f)), 
		max_point(vec3(-1000.0f, -1000.0f, -1000.0f)),
		x_origin(x), 
		y_origin(y), 
		z_origin(z),
		update(update){}

	/* Static holders for OpenGL ids */
	static GLuint active_shader_id;
	static GLuint phong_shader_id;
	static GLuint gouraud_shader_id;
	
	static GLint model_id;
	static GLint view_id;
	static GLint instance_id;
	static GLint projection_id;

	static GLint light_position_id;
	static GLint eye_position_id;
	
	static GLint diffuse_id;
	static GLint ambient_id;
	static GLint specular_id;
	static GLint shininess_id;
	static GLint lightp_id;

	mat4 model_mat;
	mat4 instance_mat;


	/* Holders for buffers */
	GLuint vbo_id;
	GLuint vao_id;
	GLuint ebo_id;

	/* Min and max point */
	vec3 min_point;
	vec3 max_point;

	GLfloat x_origin;
	GLfloat y_origin;
	GLfloat z_origin;

	GLfloat size_c;	
    GLfloat lightp;

	/* Vertex and face add to Model */
	void add_vertex(vec3, vec3);
	void add_face(GLuint, GLuint, GLuint);
	void apply_material(vec3, vec3, vec3, GLfloat);
	void change_material(vec3, vec3, vec3);
	void change_light_position(vec4);
	void change_eye_position(vec3);
	void change_shader(int);

	/* Init and draw functions */
	void point_init(void);
	void draw(mat4, mat4);
	static void program_init(void);

	void change_color(vec3);
	void (*update)(Model*);
	
private:
	/* Is initialized flag */
	bool is_init;

	/* Vertex, color and face vectors */
	vector<vec3> vertices;
	vector<vec3> colors;
	vector<GLuint> faces;

	vector< vector<vec3> > normals;

    vec3 diffuse_m;
    vec3 ambient_m;
    vec3 specular_m;

    vec3 diffuse_p;
    vec3 ambient_p;
    vec3 specular_p;

	vec4 eye_position;
	vec4 light_position;    

    GLfloat shininess;
};

#endif