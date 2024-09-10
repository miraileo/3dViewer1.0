#include "transformations.h"

float moveX(Model *model, float value, float translateX) {
  for (size_t i = 1; i < model->size_of_vertices; i++) {
    model->vertices[i * 3] += value;
  }
  translateX += value;
  return translateX;
}

float moveY(Model *model, float value, float translateY) {
  for (size_t i = 1; i < model->size_of_vertices; i++) {
    model->vertices[i * 3 + 1] += value;
  }
  translateY += value;
  return translateY;
}

float moveZ(Model *model, float value, float translateZ) {
  for (size_t i = 1; i < model->size_of_vertices; i++) {
    model->vertices[i * 3 + 2] += value;
  }
  translateZ += value;
  return translateZ;
}

float rotateX(Model *model, float angle, float rotationX) {
  float radians = angle * (M_PI / 180.0f);
  for (size_t i = 1; i < model->size_of_vertices; i++) {
    float y = model->vertices[i * 3 + 1];
    float z = model->vertices[i * 3 + 2];
    model->vertices[i * 3 + 1] = y * cos(-radians) - z * sin(-radians);
    model->vertices[i * 3 + 2] = y * sin(-radians) + z * cos(-radians);
  }
  rotationX += angle;
  return rotationX;
}

float rotateY(Model *model, float angle, float rotationY) {
  float radians = angle * (M_PI / 180.0f);
  for (size_t i = 1; i < model->size_of_vertices; i++) {
    float x = model->vertices[i * 3];
    float z = model->vertices[i * 3 + 2];

    model->vertices[i * 3] = x * cos(-radians) - z * sin(-radians);
    model->vertices[i * 3 + 2] = x * sin(-radians) + z * cos(-radians);
  }
  rotationY += angle;
  return rotationY;
}

float rotateZ(Model *model, float angle, float rotationZ) {
  float radians = angle * (M_PI / 180.0f);
  for (size_t i = 1; i < model->size_of_vertices; i++) {
    float x = model->vertices[i * 3];
    float y = model->vertices[i * 3 + 1];

    model->vertices[i * 3] = x * cos(-radians) - y * sin(-radians);
    model->vertices[i * 3 + 1] = x * sin(-radians) + y * cos(-radians);
  }
  rotationZ += angle;
  return rotationZ;
}

float scaleModel(Model *model, float increment, float currentScale) {
  if (currentScale + increment == 0) return currentScale;
  float newScale = currentScale + increment;
  float scaleFactor = newScale / currentScale;
  for (size_t i = 1; i < model->size_of_vertices; i++) {
    model->vertices[i * 3] *= scaleFactor;
    model->vertices[i * 3 + 1] *= scaleFactor;
    model->vertices[i * 3 + 2] *= scaleFactor;
  }
  return newScale;
}
