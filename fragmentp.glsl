#version 130

in vec3 fN;
in vec3 fL1;
in vec3 fE;

in vec3 out_color;
out vec4 outColor;

uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;

uniform float shininess;
uniform float lightp;

void main(){
	vec3 N = normalize(fN);
	vec3 E = normalize(fE);
	
	vec3 L1 = normalize(fL1);
	vec3 H1 = normalize( L1 + E );

	vec3 ambient_r = ambient;
	
	float Kd1 = max(dot(L1, N), 0.0);
	vec3 diffuse_r = Kd1*diffuse;
    
    float Ks1 = pow(max(dot(N, H1), 0.0), shininess);
    vec3 specular_r = vec3(0.0, 0.0, 0.0);	
    
    if( dot(L1, N) >= 0.0 ) {
        float Ks1 = pow(max(dot(N, H1), 0.0), shininess);
		specular_r += Ks1*specular;
    }    

   //outColor = vec4(out_color, 1.0);
   outColor = vec4(ambient_r + diffuse_r + specular_r, 1.0f) * vec4(out_color, 1.0) * lightp;
}
