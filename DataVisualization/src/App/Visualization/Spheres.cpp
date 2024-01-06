#include <fstream>
#include <sstream>
#include <Visualization/Spheres.h>


const std::string Spheres::_vertexShaderPath = "data/Shaders/SpheresVertex.glsl";
const std::string Spheres::_fragmentShaderPath = "data/Shaders/SpheresFragment.glsl";

void Spheres::OnStart() {
    _data = AppObject::GetObjectOfType<Data>();
    _camera = AppObject::GetObjectOfType<Camera>();
    _screen = AppObject::GetObjectOfType<Screen>();

    _screen->EnableGL();

    Init();
    
    _screen->DisableGL();
}

void Spheres::OnDraw() {
    if (_data->isReady == false) { return; }

    _screen->EnableGL();

    glLoadIdentity();
    glUseProgram(_hProgram);

    UpdateResolution();
    PassCameraToShader();
    PassDataToShader();

    _screen->DisableGL();
}

void Spheres::Init() {
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);

    glewInit();
    SetShaders();

    location_attribute_0 = glGetAttribLocation(_hProgram, "R");

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

bool Spheres::ReadAndCompileShader(const std::string filename, GLuint& hdlr, GLenum shaderType) {
    std::ifstream file(filename, std::ios::in);
    if (file.is_open() == false) {
        std::cerr << "Unable to open file " << filename << "\n";
        return false;
    }

    std::stringstream buffer;
    std::string line;
    while (std::getline(file, line)) {
        buffer << line << "\n";
    }
    file.close();

    auto srcTmp = buffer.str();
    const char* src = srcTmp.c_str();

    hdlr = glCreateShader(shaderType);
    glShaderSource(hdlr, 1, &src, nullptr);
    glCompileShader(hdlr);
    return true;
}

void Spheres::SetShaders() {
    GLuint hVert, hFrag;
    ReadAndCompileShader(_vertexShaderPath, hVert, GL_VERTEX_SHADER);
    ReadAndCompileShader(_fragmentShaderPath, hFrag, GL_FRAGMENT_SHADER);

    _hProgram = glCreateProgram();
    glAttachShader(_hProgram, hVert);
    glAttachShader(_hProgram, hFrag);
    glLinkProgram(_hProgram);
}

void Spheres::UpdateResolution() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, _screen->GetRatio(), 0.01, 5000);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, _screen->GetWidth(), _screen->GetHeight());

    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);
    SetUniform("viewport", viewport);
}

void Spheres::PassCameraToShader() {
    vec3f position = _camera->GetPosition();
    vec2f rotation = _camera->GetRotation();
    vec3f lookAt = position + _camera->GetViewDirection();

    gluLookAt(
        position.x, position.y, position.z,
        lookAt.x  , lookAt.y  , lookAt.z  ,
        0         , 1         , 0
    );

    SetUniform("u_camera_position", position.zyx());
    SetUniform("u_camera_rotation", rotation);
    SetUniform("u_resolution", _screen->GetSize());
}

void Spheres::PassDataToShader() {
    glBegin(GL_POINTS);
   
    auto& columnX = _data->GetColumnX();
    auto& columnY = _data->GetColumnY();
    auto& columnZ = _data->GetColumnZ();

    for (size_t i = 0; i < _data->GetSize(); ++i) {
        glColor3f(0.5, 0.25, 1);
        glVertexAttrib1f(location_attribute_0, 0.4);
        glVertex3f(
            columnX[i].vFloat * _data->userScale.x,
            columnY[i].vFloat * _data->userScale.y,
            columnZ[i].vFloat * _data->userScale.z
        );
    }

    glEnd();
}

void Spheres::SetUniform(const char* name, int value) {
    GLint location = glGetUniformLocation(_hProgram, name);
    glUniform1i(location, value);
}

void Spheres::SetUniform(const char* name, float value) {
    GLint location = glGetUniformLocation(_hProgram, name);
    glUniform1f(location, value);
}

void Spheres::SetUniform(const char* name, vec2f value) {
    GLint location = glGetUniformLocation(_hProgram, name);
    glUniform2f(location, value.x, value.y);
}

void Spheres::SetUniform(const char* name, vec3f value) {
    GLint location = glGetUniformLocation(_hProgram, name);
    glUniform3f(location, value.x, value.y, value.z);
}

void Spheres::SetUniform(const char* name, GLfloat value[4]) {
    GLint location = glGetUniformLocation(_hProgram, name);
    glUniform4fv(location, 1, value);
}
