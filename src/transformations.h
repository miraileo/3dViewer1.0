#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#define M_PI 3.14159265358979323846

#include <math.h>

#include "parser.h"

float moveX(Model *model, float value, float translateX);
float moveY(Model *model, float value, float translateY);
float moveZ(Model *model, float value, float translateZ);
float rotateX(Model *model, float angle, float rotationX);
float rotateY(Model *model, float angle, float rotationY);
float rotateZ(Model *model, float angle, float rotationZ);
float scaleModel(Model *model, float increment, float currentScale);

#endif  // TRANSFORMATIONS_H
