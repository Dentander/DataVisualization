#pragma once
#include <AdditionalStd/vec3.h>
#include <BaseClasses/AppObject.h>


class Point3D : public AppObject, public vec3<float> {
public:
	~Point3D() {}
};

