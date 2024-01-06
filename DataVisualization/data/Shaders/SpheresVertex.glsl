#version 120

uniform vec4 viewport;
uniform vec2 u_resolution;
uniform vec3 u_camera_position;
uniform vec2 u_camera_rotation;
uniform vec3 u_columns_min;
uniform vec3 u_columns_max;

attribute float R;

varying float sphereRadius;
varying vec3 spherePos;


void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;

    mat4 T = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        gl_Vertex.x / R, gl_Vertex.y / R, gl_Vertex.z / R, 1.0 / R
    );

    mat4 PMTt = transpose(gl_ModelViewProjectionMatrix * T);

    vec4 r1 = PMTt[0];
    vec4 r2 = PMTt[1];
    vec4 r4 = PMTt[3];
    float r1Dr4T = dot(r1.xyz, r4.xyz) - r1.w * r4.w;
    float r1Dr1T = dot(r1.xyz, r1.xyz) - r1.w * r1.w;
    float r4Dr4T = dot(r4.xyz, r4.xyz) - r4.w * r4.w;
    float r2Dr2T = dot(r2.xyz, r2.xyz) - r2.w * r2.w;
    float r2Dr4T = dot(r2.xyz, r4.xyz) - r2.w * r4.w;

    float discriminant_x = r1Dr4T * r1Dr4T - r4Dr4T * r1Dr1T;
    float discriminant_y = r2Dr4T * r2Dr4T - r4Dr4T * r2Dr2T;
    float screen = max(float(viewport.z), float(viewport.w));

    gl_PointSize = sqrt(max(discriminant_x, discriminant_y)) * screen / (-r4Dr4T);
    
    // prepare varyings
    sphereRadius = R;
    spherePos = gl_Vertex.xyz;
}