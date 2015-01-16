#ifndef __MAIN_H__
#define __MAIN_H__
/* Include standart list library */
#include <list>
#include <sstream>
#include <cstdlib>
#include <ctime>

/* Include helpers */
#include "Angel.h"
#include "Parser.h"
#include "Model.h"

/* Include glui */
#include <GL/glui.h>

enum {CAMERA_XPR,CAMERA_XNR, CAMERA_YPR, CAMERA_YNR, CAMERA_ZPR, CAMERA_ZNR, 
	  CAMERA_XPT,CAMERA_XNT, CAMERA_YPT, CAMERA_YNT, CAMERA_ZPT, CAMERA_ZNT, 
	  LIGHT_XPT, LIGHT_XNT, LIGHT_YPT, LIGHT_YNT, LIGHT_ZPT, LIGHT_ZNT,
	  AMBIENTP, AMBIENTN, DIFFUSEP, DIFFUSEN, SPECULARP, SPECULARN, LIGHTP, LIGHTN};

/* Update function type */
typedef void(*update_f)(Model*);

/* Shape type */
struct shape_t{
    Model* model;
    update_f update;
};

/* Shape holders */
vector<vector<shape_t> > shapes(4);
Model* hold_shape;
Model* true_shape;

/* Model list */
list<Model*> models;

/* Shape file holders */
const int SHAPE_SIZE = 4;
const char* shape_files[SHAPE_SIZE] = {"teapot.smf", "bound-cow.smf", "teddy.smf", "icos.smf"};

/* Shape sizes */
GLfloat shape_sizes[SHAPE_SIZE] = {0.4, 1.5, 0.05, 1.0};

long int score = 0;
int current_shader = 0;
string error_s;
clock_t past;
GLfloat light_p = 1.0;

const vec3 RED = vec3(255.0/255.0, 50.0/255.0, 50.0/255.0);
const vec3 BLUE = vec3(50.0/255, 50.0/255., 249.0/255.0);
const vec3 GREEN = vec3(99.0/255.0, 249.0/255.0, 69.0/255.0);
const vec3 YELLOW = vec3(249.0/255.0, 249.0/255.0, 69.0/255.0);
const vec3 BLACK = vec3(0.0, 0.0, 0.0);
const vec3 ORANGE = vec3(255.0/255.0, 161.0/255.0, 37.0/255.0); 
const vec3 WHITE  = vec3(1.0, 1.0, 1.0);
const vec3 GRAY = vec3(192.0/255.0, 192.0/255.0, 192.0/255.0); 
const vec3 PURPLE  = vec3(188.0/255.0, 76.0/255.0, 201.0/255.0);
const vec3 COLORS[] = {RED, BLUE, GREEN, YELLOW, ORANGE, WHITE, GRAY, PURPLE};

const string copyright = "2015 | gizem | bilal | halit";

int ROTATE_X = 10;
int ROTATE_Y = 15;
int ROTATE_Z = 1;

int TRANSLATE_X = 0;
int TRANSLATE_Y = 0;
int TRANSLATE_Z = 0;

const GLfloat ROBOT_X_ORIGIN = -10.0;  
const GLfloat ROBOT_Y_ORIGIN = 0.0; 
const GLfloat ROBOT_Z_ORIGIN = 0.0; 
const GLfloat R_SCALE = 1.50;
const GLfloat BASE_HEIGHT = R_SCALE * 2.0;
const GLfloat BASE_WIDTH = R_SCALE * 5.0;
const GLfloat LOWER_ARM_HEIGHT = R_SCALE * 6.0;
const GLfloat LOWER_ARM_WIDTH = R_SCALE * 0.5;
const GLfloat UPPER_ARM_HEIGHT = R_SCALE * 8.0;
const GLfloat UPPER_ARM_WIDTH = R_SCALE * 0.5;

vec4 light_position1 = vec4(0.0f, 30.0f, 0.0f, 1.0f);
GLfloat light_radius = -2.0f;
GLfloat light_height = 0.0f;
GLfloat light_rotation = 0.0f;
GLfloat light_speed = 0.1f;

vec3 light_diffuse1 = vec3(0.5f, 0.5f, 0.5f);
vec3 light_ambient1 = vec3(0.2f, 0.2f, 0.2f);
vec3 light_specular1 = vec3(0.5f, 0.5f, 0.5f);

vec3 diffuse = vec3(1.0f, 1.0f, 1.0f);
vec3 ambient = vec3(1.0f, 1.0f, 1.0f);
vec3 specular = vec3(1.0f, 1.0f, 1.0f);
GLfloat shininess = 5.0f;

GLfloat lower_arm_theta = 0;
GLfloat upper_arm_theta = 0;
GLfloat upper_arm_beta = 0;
GLfloat upper_arm_delta = 0.0;

/* Main window holder */

int main_window;
const GLfloat PI = 3.14159265538979323846;
const int X_SIZE = 1000;
const int Y_SIZE = 800;

mat4 view;
mat4 projection;

vec3 eye_point = vec3(0.0, 30.0, 60.0);
vec3 look_at_point = vec3(1.0,10.0,0);

GLfloat fovy = 30;
GLfloat aspect = 1.0 * X_SIZE/Y_SIZE;
GLfloat z_near = 0.1;
GLfloat z_far = 1000;


/* Function prototypes */
void display(void);
void init(void);
void keyboard(unsigned char, int, int);
void special(int, int, int);
void move_camera(float, float, float);
void idle(void);
void button_callback(int);

Model* new_cube(GLfloat, GLfloat, GLfloat, update_f);
Model* new_shape(int);
vec2 random_ints(void);

void update_upper_arm(Model*);
void update_lower_arm(Model*);
void update_base(Model*);
void update_shape(Model*);
void update_holded(Model*);

void update_colors(void);
void update_shapes(void);

void change_shader(int);

#endif