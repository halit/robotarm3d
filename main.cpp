#include "main.h"

int main(int argc, char **argv) {

    /* Seed random */
    srand(time(NULL));

    /* Init glut and glew */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(X_SIZE, Y_SIZE);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glewExperimental = GL_TRUE;

    /* Create window */
    main_window = glutCreateWindow("Project");
    glewInit();
    glEnable(GL_DEPTH_TEST);

    /* Model init */
    Model::program_init();

    /* Data init */
    init();

    /* Glut functions */
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(NULL);

    /* Glui */
    GLUI* glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_RIGHT);
    
    glui->set_main_gfx_window(main_window);

    glui->add_statictext("Camera Rotate");
    glui->add_separator();
    glui->add_button("X+", CAMERA_XPR, button_callback);
    glui->add_button("X-", CAMERA_XNR, button_callback);  
    glui->add_button("Y+", CAMERA_YPR, button_callback);
    glui->add_button("Y-", CAMERA_YNR, button_callback);
    glui->add_button("Z+", CAMERA_ZPR, button_callback);
    glui->add_button("Z-", CAMERA_ZNR, button_callback);

    glui->add_statictext("Camera Translate");
    glui->add_separator();
    glui->add_button("X+", CAMERA_XPT, button_callback);
    glui->add_button("X-", CAMERA_XNT, button_callback);  
    glui->add_button("Y+", CAMERA_YPT, button_callback);
    glui->add_button("Y-", CAMERA_YNT, button_callback);
    glui->add_button("Z+", CAMERA_ZPT, button_callback);
    glui->add_button("Z-", CAMERA_ZNT, button_callback);    

    glui->add_statictext("Light");
    glui->add_separator();
    glui->add_button("X+", LIGHT_XPT, button_callback);
    glui->add_button("X-", LIGHT_XNT, button_callback); 
    glui->add_button("Y+", LIGHT_YPT, button_callback);
    glui->add_button("Y-", LIGHT_YNT, button_callback);    
    glui->add_button("Z+", LIGHT_ZPT, button_callback);
    glui->add_button("Z-", LIGHT_ZNT, button_callback);   
    glui->add_button("Light+", LIGHTP, button_callback);
    glui->add_button("Light-", LIGHTN, button_callback);      

    glui->add_statictext("Materials");
    glui->add_separator();
    glui->add_button("Ambient+", AMBIENTP, button_callback);
    glui->add_button("Ambient-", AMBIENTN, button_callback); 
    glui->add_button("Diffuse+", DIFFUSEP, button_callback);
    glui->add_button("Diffuse-", DIFFUSEN, button_callback);    
    glui->add_button("Specular+", SPECULARP, button_callback);
    glui->add_button("Specular-", SPECULARN, button_callback);       
        
    GLUI_Master.set_glutIdleFunc(idle);

    /* Main loop */
    glutMainLoop();

    return 0;
}

void button_callback(int button_id){
    switch(button_id){
        case CAMERA_XPR:
            ROTATE_X += 1;
            break;
        case CAMERA_XNR:
            ROTATE_X += -1;
            break;   
        case CAMERA_YPR:
            ROTATE_Y += 1;
            break;
        case CAMERA_YNR:
            ROTATE_Y += -1;
            break; 
        case CAMERA_ZPR:
            ROTATE_Z += 1;
            break;
        case CAMERA_ZNR:
            ROTATE_Z += -1;
            break;  

        case CAMERA_XPT:
            TRANSLATE_X += 1;
            break;   
        case CAMERA_XNT:
            TRANSLATE_X -= 1;
            break;   
        case CAMERA_YPT:
            TRANSLATE_Y += 1;
            break;   
        case CAMERA_YNT:
            TRANSLATE_Y -= 1;
            break; 
        case CAMERA_ZPT:
            TRANSLATE_Z += 1;
            break;   
        case CAMERA_ZNT:
            TRANSLATE_Z -= 1;
            break;     


        case LIGHT_XPT:
            light_position1.x += 2;
            break;   
        case LIGHT_XNT:
            light_position1.x += -2;
            break;   
        case LIGHT_YPT:
            light_position1.x += 2;
            break;   
        case LIGHT_YNT:
            light_position1.x += -2;
            break; 
        case LIGHT_ZPT:
            light_position1.x += 2;
            break;   
        case LIGHT_ZNT:
            light_position1.x += -2;
            break;  

        case AMBIENTP:
            light_ambient1.x += 0.1;                     
            light_ambient1.y += 0.1;
            light_ambient1.z += 0.1;
            break;
        case AMBIENTN:
            light_ambient1.x += -0.1;                     
            light_ambient1.y += -0.1;
            light_ambient1.z += -0.1;
            break;   
        case DIFFUSEP:
            light_diffuse1.x += 0.1;                     
            light_diffuse1.y += 0.1;
            light_diffuse1.z += 0.1;
            break;
        case DIFFUSEN:
            light_diffuse1.x += -0.1;                     
            light_diffuse1.y += -0.1;
            light_diffuse1.z += -0.1;
            break;  
        case SPECULARP:
            light_specular1.x += 0.1;                     
            light_specular1.y += 0.1;
            light_specular1.z += 0.1;
            break;
        case SPECULARN:
            light_specular1.x += -0.1;                     
            light_specular1.y += -0.1;
            light_specular1.z += -0.1;
            break;    
        case LIGHTP:
            light_p += 0.1;
            break;
        case LIGHTN:
            light_p -= 0.1;
            break;                               

    }
}

void display(void){

    /* Clear screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Calculate view matrix */
    view = LookAt(eye_point, look_at_point, vec3(0.0,1.0,0.0));

    view *= RotateX(ROTATE_X);
    view *= RotateY(ROTATE_Y);
    view *= RotateZ(ROTATE_Z);
    view *= Translate(TRANSLATE_X, TRANSLATE_Y, TRANSLATE_Z);

    /* Draw all models */
    for(list<Model*>::iterator i = models.begin();i != models.end();i++){
        (*i)->update(*i);
        (*i)->change_light_position(light_position1);
        (*i)->change_eye_position(eye_point);
        (*i)->change_material(light_diffuse1, light_ambient1, light_specular1);
        (*i)->lightp = light_p;
        (*i)->draw(view, projection);
    }

    /* Draw the score */
    
    ostringstream ss;
    ss << "Score: ";
    ss << score;
    string s = ss.str();
    
    glRasterPos2f(0.45, 0.9);    
    for(int i=0;i<s.size();i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);    
    }

    ostringstream shader_s;
    shader_s << "Shader: ";
    if(current_shader){
        shader_s << "gouraud";
    }else{
        shader_s << "phong";
    }

    glRasterPos2f(0.45, 0.85); 
    string shader_st = shader_s.str();
    for(int i=0;i<shader_st.size();i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, shader_st[i]);    
    }    

    /* Draw the error rate */
    glRasterPos2f(0.45, 0.80); 
    for(int i=0;i<error_s.size();i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, error_s[i]);    
    }

    /* Draw the copyright */
    glRasterPos2f(0.45, -0.95); 
    for(int i=0;i<copyright.size();i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, copyright[i]);    
    }    

    /* Swap the buffers */
    glutSwapBuffers();
}

Model* new_cube(GLfloat x_origin, GLfloat y_origin, GLfloat z_origin, update_f update){
    Model* cube = new Model(x_origin, y_origin, z_origin, update);
    cube->add_vertex(vec3( -0.5, -0.5,  0.5), PURPLE);
    cube->add_vertex(vec3( -0.5,  0.5,  0.5), PURPLE);
    cube->add_vertex(vec3(  0.5,  0.5,  0.5), YELLOW);
    cube->add_vertex(vec3(  0.5, -0.5,  0.5), YELLOW);
    cube->add_vertex(vec3( -0.5, -0.5, -0.5), BLACK);
    cube->add_vertex(vec3( -0.5,  0.5, -0.5), BLACK);
    cube->add_vertex(vec3(  0.5,  0.5, -0.5), ORANGE);
    cube->add_vertex(vec3(  0.5, -0.5, -0.5), ORANGE);    

    cube->add_face(2, 1, 4);
    cube->add_face(2, 4, 3);

    cube->add_face(3, 4, 8);
    cube->add_face(3, 8, 7);

    cube->add_face(4, 1, 5);
    cube->add_face(4, 5, 8);

    cube->add_face(7, 6, 2);
    cube->add_face(7, 2, 3);

    cube->add_face(5, 6, 7);
    cube->add_face(5, 7, 8);

    cube->add_face(6, 5, 1);
    cube->add_face(6, 1, 2);

    return cube;     
}

void update_upper_arm(Model* m){
    mat4 rotation = Translate(0.0,-LOWER_ARM_HEIGHT - 0.5*UPPER_ARM_HEIGHT,0.0) *
                    RotateZ(upper_arm_theta) *
                    RotateY(upper_arm_delta) *
                    Translate(0.0,LOWER_ARM_HEIGHT + 0.5*UPPER_ARM_HEIGHT,0.0);
    mat4 rotation2 = Translate(0.0,-UPPER_ARM_HEIGHT/2.0,0.0) * 
                     RotateZ(upper_arm_beta) *
                     Translate(0.0,UPPER_ARM_HEIGHT/2.0,0.0);
    mat4 instance = Translate( 0.0, 0.5 * UPPER_ARM_HEIGHT + LOWER_ARM_HEIGHT + BASE_HEIGHT, 0.0 ) *
                    rotation *
                    rotation2 *
                    Scale(UPPER_ARM_WIDTH,
                          UPPER_ARM_HEIGHT,
                          UPPER_ARM_WIDTH);  

    m->instance_mat = instance;
}

void update_lower_arm(Model* m){
    mat4 rotate = RotateZ(lower_arm_theta);
    mat4 instance = Translate(0.0, BASE_HEIGHT,0.0) * 
                    rotate *
                    Translate(0.0, 0.5 * LOWER_ARM_HEIGHT, 0.0 ) *
                    Scale(LOWER_ARM_WIDTH,
                          LOWER_ARM_HEIGHT,
                          LOWER_ARM_WIDTH);    

    m->instance_mat = instance;
}

void update_base(Model* m){
    mat4 instance = Translate( 0.0, 0.5 * BASE_HEIGHT, 0.0 ) *
                    Scale(BASE_WIDTH,
                          BASE_HEIGHT,
                          BASE_WIDTH);
    m->instance_mat = instance;       
}

void update_shape(Model* m){
    mat4 instance = Translate( 0.0, 0.5 * BASE_HEIGHT, 0.0 ) *
                    Scale(m->size_c,
                          m->size_c,
                          m->size_c);
    m->instance_mat = instance; 
}

vec2 random_ints(void){
    GLfloat x_r = fmod(random(), 14) + 5;
    GLfloat y_r = fmod(random(), 15);
    bool is_unique = true;
    bool is_running = true;

    while(is_running){
        for(list<Model*>::iterator i = models.begin();i != models.end();i++){
            GLfloat xd = fabs((*i)->x_origin - ROBOT_X_ORIGIN - x_r);
            if((xd <= 0.5)){
                x_r += 1.5;
                y_r += 1.0;
                is_unique = false;
                break;
            }
            GLfloat yd = fabs((*i)->y_origin - ROBOT_Y_ORIGIN - y_r);
            if((yd <= 0.5)){
                y_r += 1.5;
                x_r += 1.0;
                is_unique = false;
                break;
            }            
        }        
        if(is_unique){
            is_running = false;
        }else{
            x_r = fmod(random(), 14) + 5;
            y_r = fmod(random(), 15);
            is_unique = true;
        }
    }

    return vec2(x_r, y_r);

}

void update_colors(void){
    for(list<Model*>::iterator i = models.begin();i != models.end();i++){
        (*i)->change_color(COLORS[rand()%7]);
    }
}

void update_shapes(void){
    /* Select the random shape */
    int r = rand()%4;

    /* Get random values */
    vec2 randoms = random_ints();
    GLfloat x_r = randoms.x;
    GLfloat y_r = randoms.y;

    /* Update coordinates holded shape */
    hold_shape->x_origin = ROBOT_X_ORIGIN + x_r;
    hold_shape->y_origin = ROBOT_Y_ORIGIN + y_r;
    hold_shape->update = update_shape;

    /* Get new random values */
    randoms = random_ints();
    x_r = randoms.x;
    y_r = randoms.y;

    /* Update hold shape */
    hold_shape = shapes[r][0].model;
    hold_shape->update = update_holded;

    /* Update true shape */
    true_shape = shapes[r][1].model;
    true_shape->x_origin = ROBOT_X_ORIGIN + x_r;
    true_shape->y_origin = ROBOT_Y_ORIGIN + y_r;

    /* Update colors */
    update_colors();
}

void update_holded(Model* m){

    /* Calculate x_r, y_r coefficents */
    GLfloat x_r = m->x_origin - ROBOT_X_ORIGIN;
    GLfloat y_r = m->y_origin - ROBOT_Y_ORIGIN;

    /* Calculate rotation matrices */
    mat4 rotation = Translate(0.0,-LOWER_ARM_HEIGHT - UPPER_ARM_HEIGHT,0.0) *
                    RotateZ(upper_arm_theta) *
                    RotateY(upper_arm_delta) *
                    Translate(0.0,LOWER_ARM_HEIGHT + UPPER_ARM_HEIGHT,0.0);
    mat4 rotation2 = Translate(0.0,-UPPER_ARM_HEIGHT,0.0) * 
                     RotateZ(upper_arm_beta) *
                     Translate(0.0,UPPER_ARM_HEIGHT,0.0);

    /* Calculate instance matrix */
    mat4 instance = Translate( -x_r, UPPER_ARM_HEIGHT + LOWER_ARM_HEIGHT + BASE_HEIGHT-y_r, 0.0 ) *
                rotation *
                rotation2 *
              Scale(m->size_c,
                 m->size_c,
                 m->size_c);  
    m->instance_mat = instance;

    /* Calculate how tipped */
    GLfloat lower_arm_tipx = -sin(lower_arm_theta*(PI/180))*LOWER_ARM_HEIGHT;
    GLfloat lower_arm_tipy =  cos(-lower_arm_theta*(PI/180))*LOWER_ARM_HEIGHT;
    GLfloat upper_arm_tipx = -cos((90 - (lower_arm_theta + upper_arm_beta))*(PI/180))*UPPER_ARM_HEIGHT;
    GLfloat upper_arm_tipy =  sin((90 - (lower_arm_theta + upper_arm_beta))*(PI/180))*UPPER_ARM_HEIGHT;
    
    // @FIX
    GLfloat upper_arm_tip_z = tan(upper_arm_delta*(PI/180))*LOWER_ARM_HEIGHT;

    /* Calculate real tip and offset */
    vec2 lower_arm_tip = vec2(lower_arm_tipx, lower_arm_tipy);
    vec2 upper_arm_tip = vec2(upper_arm_tipx, upper_arm_tipy);
    vec2 offset = vec2(ROBOT_X_ORIGIN, 0.0 + BASE_HEIGHT);    
    
    /* Current and true shape */
    vec3 cs = vec3(offset + lower_arm_tip + upper_arm_tip, upper_arm_tip_z);
    vec3 ts = vec3(true_shape->x_origin, true_shape->y_origin, true_shape->z_origin);

    /* Calculate distances */
    GLfloat xd = sqrt((cs.x - ts.x)*(cs.x - ts.x));
    GLfloat yd = sqrt((cs.y - ts.y)*(cs.y - ts.y));
    GLfloat zd = sqrt((cs.z - ts.z)*(cs.z - ts.z));

    /* Magic numbers */
    GLfloat xdd = xd - 1.5;
    GLfloat ydd = yd - 1.5;
    GLfloat zdd = zd - 0.5;

    if((xdd <= 0.01) && (ydd <= 0.01)){
        /* Calculate time and add score */
        clock_t last = clock() - past;
        GLfloat score_r = float(last)/CLOCKS_PER_SEC;
        score += int(10/score_r);
        past = clock();

        /* Update shapes */
        update_shapes();
    }else{
        ostringstream s;
        s << "X: ";
        s << xdd;
        s << "\n";
        s << "Y: ";
        s << ydd;
        error_s = s.str();
    }
}

Model* new_shape(int i){

    /* Create random ints */
    vec2 randoms = random_ints();
    int x_r = randoms.x;
    int y_r = randoms.y;

    /* Parse the shape files to models */
    Parser parser(shape_files[i]);
    Model* m1 = parser.parse_to_model(RED, ROBOT_X_ORIGIN+x_r, ROBOT_Y_ORIGIN+y_r, ROBOT_Z_ORIGIN, update_shape);    
    m1->size_c = shape_sizes[i];

    return m1;
}

/* Init the models */
void init(void){

    /* Create the robot base */
    Model* base = new_cube(ROBOT_X_ORIGIN, ROBOT_Y_ORIGIN, ROBOT_Z_ORIGIN, update_base);
    models.push_back(base);

    /* Create the lower arm */
    Model* lower_arm = new_cube(ROBOT_X_ORIGIN, ROBOT_Y_ORIGIN, ROBOT_Z_ORIGIN, update_lower_arm);
    models.push_back(lower_arm);  

    /* Create the upper arm */
    Model* upper_arm = new_cube(ROBOT_X_ORIGIN, ROBOT_Y_ORIGIN, ROBOT_Z_ORIGIN, update_upper_arm);
    models.push_back(upper_arm);    

    /* Create the first shapes */
    for(int i=0;i<SHAPE_SIZE;i++){
        Model* m = new_shape(i);
        models.push_back(m); 

        shape_t s;
        s.model = m;        
        shapes[i].push_back(s);
    } 

    /* Create the second shapes */
    for(int i=0;i<SHAPE_SIZE;i++){
        Model* m = new_shape(i);
        models.push_back(m); 

        shape_t s;
        s.model = m;        
        shapes[i].push_back(s);
    }     

    /* Update colors as random */
    update_colors();

    /* Select the hold and true shape */
    hold_shape = shapes[0][0].model;
    hold_shape->update = update_holded;
    true_shape = shapes[0][1].model;

    /* Init the all models */
    for(list<Model*>::iterator i = models.begin();i != models.end();i++){
        (*i)->point_init();
        (*i)->apply_material(diffuse, ambient, specular, shininess);
        (*i)->lightp = light_p;
    }

    /* Init the view matrix */
    view = LookAt(eye_point, look_at_point, vec3(0.0,1.0,0.0));
    view *= RotateX(ROTATE_X);
    view *= RotateY(ROTATE_Y);
    projection = Perspective(fovy, aspect, z_near, z_far);
    
    /* Enable some features */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);   

    /* Init the clock */
    past = clock();
}

void change_shader(int shader){
    for(list<Model*>::iterator i = models.begin();i != models.end();i++){
        (*i)->change_shader(shader);
    }
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 033:
            exit(EXIT_SUCCESS);
            break;
        case 'a':
            lower_arm_theta += 4;
            upper_arm_theta += 4;
            break;
        case 'd' :
            lower_arm_theta += -4;
            upper_arm_theta += -4;
            break;
        case 'w':
            upper_arm_beta += 4;
            break;
        case 's' :
            upper_arm_beta += -4;
            break;
        case 'e' :
            upper_arm_delta += -4;
            break;
        case 'q' :
            upper_arm_delta += 4;
            break;                        
        case 'p':
            change_shader(0);
            current_shader = 0;
            break;
        case 'g':
            change_shader(1);  
            current_shader = 1; 
            break;
    }
    glutPostRedisplay();
}

void idle(void){
    glutSetWindow(main_window);
    glutPostRedisplay();
}

void special(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            ROTATE_X += 5;
            break;
        case GLUT_KEY_DOWN:
            ROTATE_X -= 5;
            break;
        case GLUT_KEY_LEFT:
            ROTATE_Y += 5;
            break;
        case GLUT_KEY_RIGHT:
            ROTATE_Y -= 5;
            break;
    }
}
