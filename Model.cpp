/* Include model header file */
#include "Model.h"

/* Init static values */
GLuint Model::active_shader_id = 0;
GLuint Model::phong_shader_id = 0;
GLuint Model::gouraud_shader_id = 0;

GLint Model::model_id = 0;
GLint Model::view_id = 0;
GLint Model::instance_id = 0;
GLint Model::projection_id = 0;
GLint Model::light_position_id = 0;
GLint Model::eye_position_id = 0;
GLint Model::ambient_id = 0;
GLint Model::specular_id = 0;
GLint Model::diffuse_id = 0;
GLint Model::shininess_id = 0;
GLint Model::lightp_id = 0;

/* Add point with color to vertex array */
void Model::add_vertex(vec3 point, vec3 color){

	/* Add point to vectors */
	vertices.push_back(point);
	colors.push_back(color);
	normals.push_back(vector<vec3>());

	/* Detect and change minimum point */
    if(min_point.x > point.x) min_point.x = point.x;
    if(min_point.y > point.y) min_point.y = point.y;
    if(min_point.z > point.z) min_point.z = point.z;

    /* Detect and change maximum point */
    if(max_point.x < point.x) max_point.x = point.x;
    if(max_point.y < point.y) max_point.y = point.y;
    if(max_point.z < point.z) max_point.z = point.z;
}

/* Add three index to faces vector */
void Model::add_face(GLuint p1, GLuint p2, GLuint p3){
	faces.push_back(p1 - 1);
	faces.push_back(p2 - 1);
	faces.push_back(p3 - 1);

    vec3 n = normalize(cross(vertices[p2-1] - vertices[p1-1], vertices[p3-1] - vertices[p2-1]));

    normals[p1-1].push_back(n);
    normals[p2-1].push_back(n);
    normals[p3-1].push_back(n);	
}


void Model::apply_material(vec3 d, vec3 a, vec3 s, GLfloat sh){
	diffuse_m = d;
	ambient_m = a;
	specular_m = s;
	shininess = sh;
}

void Model::change_material(vec3 d, vec3 a, vec3 s){
	diffuse_p = d;
	ambient_p = a;
	specular_p = s;
}

void Model::change_light_position(vec4 v){
	light_position.x = v.x;
	light_position.y = v.y;
	light_position.z = v.z;
	light_position.w = v.w;
}

void Model::change_eye_position(vec3 v){
	eye_position.x = v.x;
	eye_position.y = v.y;
	eye_position.z = v.z;
}

/* Initialize the points in the buffers */
void Model::point_init(void){

	/* Generate and bind vertex array object */
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	/* Generate and bind buffer */
	glGenBuffers(1, &vbo_id);  
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

	/* Start indexes */
	vector<vec3> normal_averages(normals.size());

	vec3* vertex_s = &(vertices[0]);
	vec3* color_s = &(colors[0]);
	vec3* normal_s = &(normal_averages[0]);
	GLuint* face_s = &(faces[0]);
	//vec3* normal_s = (vec3 *)malloc(normals.size() * sizeof(vec3));

	int i = 0;

	for(vector< vector< vec3 > >::iterator itr1 = normals.begin(); itr1 != normals.end(); itr1++) {
		vec3 normal;
		for(vector<vec3>::iterator itr2 = itr1->begin(); itr2 != itr1->end(); itr2++) {
			normal += *(itr2);
		}
		normal_averages[i++] = normal / itr1->size();
	}	

	/* Feed the data, vertices and colors */
	glBufferData(GL_ARRAY_BUFFER, (vertices.size() + colors.size() + normals.size()) * sizeof(vec3), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(vec3), vertex_s);
	glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), colors.size() * sizeof(vec3), color_s);
	glBufferSubData(GL_ARRAY_BUFFER, (vertices.size()+colors.size()) * sizeof(vec3), normals.size() * sizeof(vec3), normal_s);

	//free(normal_s);

	/* Feed the data, elements */
	glGenBuffers(1, &ebo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size()  * sizeof(GLuint), face_s, GL_STATIC_DRAW);

	/* Transfer points to vertex shader */
	GLuint point = glGetAttribLocation(active_shader_id, "vPoint");
	glVertexAttribPointer(point, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(point);

	/* Transfer colors to vertex shader */
	GLuint color = glGetAttribLocation(active_shader_id, "vColor"); 
	glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(vec3)));
	glEnableVertexAttribArray(color);

	
	GLuint normal = glGetAttribLocation(active_shader_id, "vNormal"); 
	glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2*vertices.size() * sizeof(vec3)));
	glEnableVertexAttribArray(normal);	

	/* Initialized */
	is_init = true;	
}

/* Draw the model */
void Model::draw(mat4 view, mat4 projection) {
	if(is_init) {
		// if any error occured, you init first id matrix then multiply
		model_mat = Translate(x_origin, y_origin, z_origin);

		/* Bind the buffer */
		glBindVertexArray(vao_id);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);

		/* Use the shader program */
		glUseProgram(active_shader_id);

		/* Send the data to shader */
		glUniformMatrix4fv(model_id, 1, GL_TRUE, model_mat);
		glUniformMatrix4fv(instance_id, 1, GL_TRUE, instance_mat);

		glUniformMatrix4fv(view_id, 1, GL_TRUE, view);
		glUniformMatrix4fv(projection_id, 1, GL_TRUE, projection);

		glUniform4fv(light_position_id, 1, light_position);
		
		glUniform3fv(diffuse_id, 1, diffuse_p * diffuse_m );
		glUniform3fv(ambient_id, 1, ambient_p * ambient_m );
		glUniform3fv(specular_id, 1, specular_p * specular_m );	

		glUniform4fv(eye_position_id, 1, eye_position);
		glUniform1f(shininess_id, shininess);			
		glUniform1f(lightp_id, lightp);	

		/* Draw all faces */
		glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, 0);
	}
}

/* Init the shader program */
void Model::program_init(void) {
	/* Create shader program with shader files */
	phong_shader_id = InitShader("vertexp.glsl", "fragmentp.glsl");
	glBindFragDataLocation(phong_shader_id, 0, "outColor");
	LinkProgram(phong_shader_id);

	gouraud_shader_id = InitShader("vertexg.glsl", "fragmentg.glsl");
	glBindFragDataLocation(gouraud_shader_id, 0, "outColor");
	LinkProgram(gouraud_shader_id);	

	active_shader_id = phong_shader_id;

	/* Link the shaders with matrices */
	model_id = glGetUniformLocation(active_shader_id, "model");
	view_id = glGetUniformLocation(active_shader_id, "view");
	instance_id = glGetUniformLocation(active_shader_id, "instance");
	projection_id = glGetUniformLocation(active_shader_id, "projection");
	
	light_position_id = glGetUniformLocation(active_shader_id, "lightPosition");
	eye_position_id = glGetUniformLocation(active_shader_id, "eyePosition");

	diffuse_id = glGetUniformLocation(active_shader_id, "diffuse");
	ambient_id = glGetUniformLocation(active_shader_id, "ambient");
	specular_id = glGetUniformLocation(active_shader_id, "specular");
	shininess_id = glGetUniformLocation(active_shader_id, "shininess");
	lightp_id = glGetUniformLocation(active_shader_id, "lightp");
}

void Model::change_color(vec3 color){
	for(vector<vec3>::iterator i=colors.begin();i != colors.end();i++){
		(*i).x = color.x;
		(*i).y = color.y;
		(*i).z = color.z;
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	vec3* color_s = &(colors[0]);	
	glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), colors.size() * sizeof(vec3), color_s);
}

void Model::change_shader(int shader) {
    if(shader == 0) {
    	active_shader_id = phong_shader_id;
    }else{
    	active_shader_id = gouraud_shader_id;
    }

    glUseProgram(active_shader_id);
    glBindVertexArray(vao_id);

	/* Link the shaders with matrices */
	model_id = glGetUniformLocation(active_shader_id, "model");
	view_id = glGetUniformLocation(active_shader_id, "view");
	instance_id = glGetUniformLocation(active_shader_id, "instance");
	projection_id = glGetUniformLocation(active_shader_id, "projection");
	
	light_position_id = glGetUniformLocation(active_shader_id, "lightPosition");
	eye_position_id = glGetUniformLocation(active_shader_id, "eyePosition");

	diffuse_id = glGetUniformLocation(active_shader_id, "diffuse");
	ambient_id = glGetUniformLocation(active_shader_id, "ambient");
	specular_id = glGetUniformLocation(active_shader_id, "specular");
	shininess_id = glGetUniformLocation(active_shader_id, "shininess");
	lightp_id = glGetUniformLocation(active_shader_id, "lightp");
}