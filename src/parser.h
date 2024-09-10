#ifndef PARSER_H
#define PARSER_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  size_t size_of_vertices;
  size_t size_of_faces;
  float* vertices;  // массив вершин с координатами
  size_t* face_vertices_count;  // количество вершин полигона
  size_t** vertex_indices;  // индексы вершин полигона
} Model;

int loadModel(Model* model, const char* filename);
int getInfo(Model* model, const char* filename);
void parseData(Model* model, const char* filename);
void deleteModel(Model* model);

#endif  // PARSER_H
