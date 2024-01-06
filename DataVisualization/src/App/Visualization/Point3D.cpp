#include <GL/glew.h>
#include <Visualization/Point3D.h>


void Point3D::OnStart() {
	_screen = AppObject::GetObjectOfType<Screen>();
	_camera = AppObject::GetObjectOfType<Camera>();
}

void Point3D::OnDraw() {
	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color(100, 250, 50));

	auto projection = Project() - vec2f(50);

	shape.setPosition(projection.ToSFML());
	_screen->GetRender()->draw(shape);
}

vec2f Point3D::Project() {
	_screen->EnableGL();

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble viewVector[3];
	GLdouble projection[16];
	GLdouble winX, winY, winZ; 

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	viewVector[0] = modelview[8];
	viewVector[1] = modelview[9];
	viewVector[2] = modelview[10];

	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	gluProject(x, y, z, modelview, projection, viewport, &winX, &winY, &winZ);

	_screen->DisableGL();
	return vec2f(winX, _screen->GetHeight() - winY);
}


