#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 instance;
uniform mat4 projection;
uniform vec4 lightPosition;
uniform vec4 eyePosition;

out vec3 fN;
out vec3 fE;
out vec3 fL1;

in vec3 vPoint;
in vec3 vColor;
in vec3 vNormal;
out vec3 out_color;

void main(){
    fN = vNormal;
    fE = (eyePosition - vec4(vPoint, 1.0f)).xyz;

    if(lightPosition.w != 0.0) {
        fL1 = lightPosition.xyz - vPoint;
    }
    else {
        fL1 = lightPosition.xyz;
    }
    
    gl_Position = projection * view * model * instance * vec4(vPoint, 1.0f);
    out_color = vColor;
}
