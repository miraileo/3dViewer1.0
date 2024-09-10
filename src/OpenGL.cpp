#include "OpenGL.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent, Model *model)
    : QOpenGLWidget(parent),
      m_model(model),
      m_backgroundColor(1),
      m_pointColor(1),
      m_edgeColor(1),
      m_zoom(1.0f),
      m_rotationX(0.0f),
      m_rotationY(0.0f),
      m_rotationZ(0.0f),
      m_scale(1.0f),
      m_translateX(0.0f),
      m_translateY(0.0f),
      m_translateZ(0.0f),
      m_pointSize(2),
      m_lineSize(2),
      stripLine(false),
      orthoProjection(false),
      circleVertex(false),
      squareVertex(false) {}

MyOpenGLWidget::~MyOpenGLWidget() {
  if (m_model) deleteModel(m_model);
}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, w / (float)h, 0.1, 1000.0);
  glMatrixMode(GL_MODELVIEW);
}

void MyOpenGLWidget::paintGL() {
  UpdateProjection();
  glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(),
               m_backgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0, 0, 0 + (5.0f * m_zoom), 0, 0, 0, 0.0, 1.0, 0.0);
  DrawVertexes();
  DrawEdges();
  glFlush();
}

void MyOpenGLWidget::UpdateProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect = static_cast<float>(width()) / static_cast<float>(height());
  if (orthoProjection)
    glOrtho(-aspect, aspect, -1.0, 1.0, 0.1, 1000.0);
  else
    gluPerspective(45.0, aspect, 0.1, 1000.0);
  glMatrixMode(GL_MODELVIEW);
}

void MyOpenGLWidget::DrawEdges() {
  glColor3f(m_edgeColor.redF(), m_edgeColor.greenF(), m_edgeColor.blueF());
  glLineWidth(m_lineSize);
  if (stripLine) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(7, 7);
  } else
    glDisable(GL_LINE_STIPPLE);
  glBegin(GL_LINES);
  for (size_t i = 1; i < m_model->size_of_faces; i++) {
    for (size_t j = 1; j <= m_model->face_vertices_count[i]; j++) {
      int current_index = m_model->vertex_indices[i][j];
      int next_index =
          m_model->vertex_indices[i][(j % m_model->face_vertices_count[i]) + 1];

      glVertex3f(m_model->vertices[current_index * 3],
                 m_model->vertices[current_index * 3 + 1],
                 m_model->vertices[current_index * 3 + 2]);
      glVertex3f(m_model->vertices[next_index * 3],
                 m_model->vertices[next_index * 3 + 1],
                 m_model->vertices[next_index * 3 + 2]);
    }
  }
  glEnd();
}

void MyOpenGLWidget::DrawVertexes() {
  glColor3f(m_pointColor.redF(), m_pointColor.greenF(), m_pointColor.blueF());
  if (squareVertex || circleVertex) {
    glPointSize(m_pointSize);
    if (circleVertex)
      glEnable(GL_POINT_SMOOTH);
    else if (squareVertex)
      glDisable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for (size_t i = 1; i < m_model->size_of_vertices; i++) {
      glVertex3f(m_model->vertices[i * 3], m_model->vertices[i * 3 + 1],
                 m_model->vertices[i * 3 + 2]);
    }
    glEnd();
  }
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    m_zoom *= 0.9f;
  } else {
    m_zoom *= 1.1f;
  }
  update();
}
