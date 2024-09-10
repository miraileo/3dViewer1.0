#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QTime>
#include <QTimer>

#include "OpenGL.h"
#include "qgifimage.h"

extern "C" {
#include "parser.h"
#include "transformations.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_xTransSpinBox_valueChanged(double arg1);
  void on_yTransSpinBox_valueChanged(double arg1);
  void on_zTransSpinBox_valueChanged(double arg1);
  void on_xRotSpinBox_valueChanged(double arg1);
  void on_yRotSpinBox_valueChanged(double arg1);
  void on_zRotSpinBox_valueChanged(double arg1);
  void on_xTransSlider_sliderMoved(int position);
  void on_yTransSlider_sliderMoved(int position);
  void on_zTransSlider_sliderMoved(int position);
  void on_xRotSlider_sliderMoved(int position);
  void on_yRotSlider_sliderMoved(int position);
  void on_zRotSlider_sliderMoved(int position);
  void on_pushButton_clicked();
  void updateUIFromModel();
  void on_BackGroundColor_clicked();
  void on_edgeColor_clicked();
  void on_pointColor_clicked();
  void AssignTextValue(float *value, QLineEdit *line, int i);
  void on_DashedEdges_clicked();
  void on_OrthoProjection_clicked();
  void on_VertexTypeButton_clicked();
  void saveSettings();
  void loadSettings();
  void showModelInfo();
  void on_ScreenShot_clicked();
  void ChangeValue(float newValue, float *currentvalue);
  void renderFrame();
  void on_RecordGif_clicked();
  void on_vertexSizeSpinBox_valueChanged(double arg1);
  void on_edgeSizeSpinBox_valueChanged(double arg1);
  void on_scaleSpinBox_valueChanged(double arg1);

 private:
  Ui::MainWindow *ui;
  MyOpenGLWidget *m_openGL;
  QString fileName;
  QString gifFileName;
  Model model;
  QTimer *timer;
  QGifImage *gif;
  int frame_count;
  QTime start;
  QPoint mPos;
  QString qss;
  double rotX, rotY;
  void mousePressEvent(QMouseEvent *mouse) override;
  void mouseMoveEvent(QMouseEvent *mouse) override;
};
#endif  // MAINWINDOW_H
