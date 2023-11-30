#include <fstream>
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

    UpdateResolution();
    SetData();
    glUseProgram(0);

    _screen->DisableGL();
}

void Spheres::Init() {
    glDepthMask(GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glAlphaFunc(GL_GREATER, 0.5);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthRange(0, 1);

    glewInit();
    SetShaders();

    location_attribute_0 = glGetAttribLocation(prog_hdlr, "R");
    location_viewport = glGetUniformLocation(prog_hdlr, "viewport");

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

bool Spheres::ReadAndCompileShader(const std::string filename, GLuint& hdlr, GLenum shaderType) {
    std::ifstream is(filename, std::ios::in | std::ios::binary | std::ios::ate);
    if (!is.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return false;
    }
    long size = is.tellg();
    char* buffer = new char[size + 1];
    is.seekg(0, std::ios::beg);
    is.read(buffer, size);
    is.close();
    buffer[size] = 0;

    hdlr = glCreateShader(shaderType);
    glShaderSource(hdlr, 1, (const GLchar**)&buffer, NULL);
    glCompileShader(hdlr);
    delete[] buffer;
    return true;
}

void Spheres::SetShaders() {
    GLuint vert_hdlr, frag_hdlr;
    ReadAndCompileShader(_vertexShaderPath, vert_hdlr, GL_VERTEX_SHADER);
    ReadAndCompileShader(_fragmentShaderPath, frag_hdlr, GL_FRAGMENT_SHADER);

    prog_hdlr = glCreateProgram();
    glAttachShader(prog_hdlr, frag_hdlr);
    glAttachShader(prog_hdlr, vert_hdlr);

    glLinkProgram(prog_hdlr);
}

void Spheres::UpdateResolution() {
    vec2f size = _screen->GetSize();
    float ratio = (1.0 * size.x) / size.y;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, ratio, 0.01, 5000);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, size.x, size.y);
}

void Spheres::SetData() {
    glLoadIdentity();

    // ========== CAMERA ==========
    vec3f position = _camera->GetPosition().zyx();
    vec2f rotation = _camera->GetRotation();

    vec3f cameraPos = position;
    vec3f lookAt = cameraPos;
    lookAt.x += sin(rotation.x) * 10.0 * cos(rotation.y);
    lookAt.y += sin(rotation.y) * 10.0;
    lookAt.z += cos(rotation.x) * 10.0 * cos(rotation.y);
    gluLookAt(
        cameraPos.z, cameraPos.y, cameraPos.x,
        lookAt.z, lookAt.y, lookAt.x,
        0, 1, 0
    );

    glUseProgram(prog_hdlr);
    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);
    glUniform4fv(location_viewport, 1, viewport);

    SetUniform("u_camera_position", position);
    SetUniform("u_camera_rotation", rotation);
    SetUniform("u_resolution", _screen->GetSize());

    // ========== SPHERES ==========
    glBegin(GL_POINTS);
   
    auto& columnX = _data->GetColumnX();
    auto& columnY = _data->GetColumnY();
    auto& columnZ = _data->GetColumnZ();

    for (size_t i = 0; i < _data->GetSize(); ++i) {
        if (columnX[i].IsNum() and columnZ[i].IsNum() and columnZ[i].IsNum()) {
            glColor3f(0.5, 0.25, 1);
            glVertexAttrib1f(location_attribute_0, _data->radius);
            glVertex3f(
                columnX[i].vFloat,
                columnY[i].vFloat,
                columnZ[i].vFloat
            );
        }
    }

    glEnd();
}

void Spheres::SetUniform(std::string name, int item) {
    GLint location = glGetUniformLocation(prog_hdlr, name.c_str());
    glUniform1i(location, item);
}

void Spheres::SetUniform(std::string name, float item) {
    GLint location = glGetUniformLocation(prog_hdlr, name.c_str());
    glUniform1f(location, item);
}

void Spheres::SetUniform(std::string name, vec2f item) {
    GLint location = glGetUniformLocation(prog_hdlr, name.c_str());
    glUniform2f(location, item.x, item.y);
}

void Spheres::SetUniform(std::string name, vec3f item) {
    GLint location = glGetUniformLocation(prog_hdlr, name.c_str());
    glUniform3f(location, item.x, item.y, item.z);
}
