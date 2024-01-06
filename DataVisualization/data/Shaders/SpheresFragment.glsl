#version 120

const float FOV = 1;
const float MAX_DIST = 5000;

uniform vec2 u_resolution;
uniform vec3 u_camera_position;
uniform vec2 u_camera_rotation;

varying float sphereRadius;
varying vec3 spherePos;


mat2 rot(const float a) {
    float s = sin(a);
    float c = cos(a);
    return mat2(c, -s, s, c);
}

float raySphereIntersect(vec3 r0, vec3 rd, vec3 s0, float sr) {
    float a = dot(rd, rd);
    vec3 s0_r0 = r0 - s0;
    float b = 2.0 * dot(rd, s0_r0);
    float c = dot(s0_r0, s0_r0) - (sr * sr);
    float d = b * b - 4.0 * a * c;
    if (d < 0.0) {
        return -1.0;
    }
    return (-b - sqrt(d)) / (2.0 * a);
}

vec3 getLight(vec3 p, vec3 rd, vec3 color, vec3 N) {
    vec3 lightPos = vec3(2, 4, -3) * 1000;
    vec3 L = normalize(lightPos - p);
    vec3 diffuse = color * clamp(dot(L, N), 0.07, 1.0);
    return diffuse;
}

vec3 render(const vec2 uv) {
    vec3 ro = u_camera_position;
    vec3 rd = normalize(vec3(uv, FOV));

    rd.zy *= rot(u_camera_rotation.y);
    rd.xz *= rot(-u_camera_rotation.x);

    float sphereDist = raySphereIntersect(ro, rd, spherePos.zyx, sphereRadius);

    if (sphereDist < 0.0f) { discard; } 

    vec3 sphereNormal = (ro + rd * sphereDist) - spherePos.zyx;
    gl_FragDepth = sphereDist / MAX_DIST;

    return getLight(ro + rd * sphereDist, rd, gl_Color.xyz, sphereNormal);
}

vec2 getUV() {
    vec2 uv = (2.0 * gl_FragCoord.xy - u_resolution.xy) / u_resolution.y;
    return uv;
}

void main() {
    vec3 color = render(getUV());
    color = pow(color, vec3(0.4545));
    gl_FragColor = vec4(color, 1);
}
