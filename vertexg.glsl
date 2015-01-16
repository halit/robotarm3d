#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 instance;
uniform mat4 projection;
uniform vec4 lightPosition;
uniform vec4 eyePosition;

uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;
uniform float shininess;

in vec3 vPoint;
in vec3 vColor;
in vec3 vNormal;
out vec4 out_color;

void main(){
    mat4 model_view = view * model;
    vec3 pos = (model_view * vec4(vPoint, 1.0)).xyz;
	
    vec3 L1 = normalize( (model_view*lightPosition).xyz - pos );
    vec3 E = normalize( -pos );
    vec3 H1 = normalize( L1 + E );

    // Transform vertex normal into eye coordinates
    vec3 N = normalize( model_view*vec4(vNormal, 0.0) ).xyz;

    // Compute terms in the illumination equation
    vec4 ambient_r = vec4(ambient, 1.0f);

    float Kd1 = max( dot(L1, N), 0.0 );
    vec4  diffuse_r = vec4(Kd1*diffuse, 1.0f);

    float Ks1 = pow( max(dot(N, H1), 0.0), shininess );

    vec4 specular_r = vec4(0.0, 0.0, 0.0, 1.0);
    
    if( dot(L1, N) >= 0.0 ) {
        specular_r += vec4(Ks1*specular, 1.0f);
    } 

    gl_Position = projection * view * model * instance * vec4(vPoint, 1.0f);

    out_color = (ambient_r + diffuse_r + specular_r)*vec4(vColor, 1.0f);
    out_color.a = 1.0;
}
