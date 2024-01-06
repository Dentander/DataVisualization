#version 330

out vec4 fragColor;

uniform vec2 u_resolution;
uniform vec3 u_camera_position;
uniform vec2 u_camera_rotation;
uniform vec3 u_background_color = vec3(0.5, 0.8, 0.9);

const float FOV = 1;
const float EPSILON = 0.01;


mat2 rot(const float a) {
    float s = sin(a);
    float c = cos(a);
    return mat2(c, -s, s, c);
}

vec3 render(const vec2 uv) {
    vec3 ro = u_camera_position;
    vec3 rd = normalize(vec3(uv, FOV));

    rd.zy *= rot(u_camera_rotation.y);
    rd.xz *= rot(-u_camera_rotation.x);

    return u_background_color - max(0.6 * rd.y, 0.0);
}

vec2 getUV(const vec2 offset) {
    vec2 uv = (2.0 * (gl_FragCoord.xy + offset) - u_resolution.xy) / u_resolution.y;
    return uv;
}

void main() {
    vec3 color = render(getUV(vec2(0)));
    color = pow(color, vec3(0.4545));
    fragColor = vec4(color, 1.0);
}
