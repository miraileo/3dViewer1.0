#include "parser.h"

int loadModel(Model* model, const char* filename) {
  if (!getInfo(model, filename)) {
    model->vertex_indices =
        (size_t**)malloc(sizeof(size_t*) * (model->size_of_faces));
    model->face_vertices_count =
        (size_t*)calloc((model->size_of_faces), sizeof(size_t));
    model->vertices =
        (float*)malloc(sizeof(float) * (model->size_of_vertices) * 3);
    parseData(model, filename);
  } else {
    return 1;
  }
  return 0;
}

int getInfo(Model* model, const char* filename) {
  FILE* obj_file = fopen(filename, "r");
  if (obj_file == NULL) return 1;
  char line[1000];
  model->size_of_vertices = 1;
  model->size_of_faces = 1;

  while (!feof(obj_file)) {
    if (fgets(line, 1000, obj_file) == NULL) break;

    if (line[0] == 'v' && line[1] == ' ')
      model->size_of_vertices++;
    else if (line[0] == 'f' && line[1] == ' ')
      model->size_of_faces++;
  }
  fclose(obj_file);
  if (model->size_of_vertices == 1 || model->size_of_faces == 1) return 1;
  return 0;
}

void parseData(Model* model, const char* filename) {
  char* number;
  size_t v_row = 1;
  size_t index = 1;
  char line[1000];
  FILE* obj_file = fopen(filename, "r");

  while (!feof(obj_file)) {
    if (fgets(line, 1000, obj_file) == NULL) break;

    if (line[0] == 'v' && line[1] == ' ') {
      strtok(line, " ");
      for (size_t v_col = 0; v_col < 3; v_col++) {
        number = strtok(NULL, " ");
        model->vertices[v_row * 3 + v_col] = atof(number);
      }
      v_row++;
    } else if (line[0] == 'f' && line[1] == ' ') {
      model->face_vertices_count[index] = 0;
      for (size_t i = 0; i < strlen(line); i++)
        if (line[i] == ' ' && isdigit(line[i + 1]))
          model->face_vertices_count[index]++;
      model->vertex_indices[index] = (size_t*)malloc(
          sizeof(size_t) * (model->face_vertices_count[index] + 1));

      strtok(line, " ");
      for (size_t i = 1; i <= model->face_vertices_count[index]; i++) {
        number = strtok(NULL, " ");
        model->vertex_indices[index][i] = atoi(number);
      }
      index++;
    }
  }
  fclose(obj_file);
}

void deleteModel(Model* model) {
  free(model->vertices);
  for (size_t i = 1; i < model->size_of_faces; i++)
    free(model->vertex_indices[i]);
  free(model->vertex_indices);
  free(model->face_vertices_count);
}
