#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_openGL = new MyOpenGLWidget(nullptr, nullptr);
  ui->OpenGLWidget = m_openGL;
  ui->verticalLayout->addWidget(ui->OpenGLWidget);
  ui->OpenGLWidget->hide();
  ui->ControlWidget->setEnabled(false);
  setCentralWidget(ui->mainwidget);
  updateUIFromModel();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_xTransSpinBox_valueChanged(double arg1) {
  ChangeValue(moveX(m_openGL->m_model, arg1 - m_openGL->m_translateX,
                    m_openGL->m_translateX),
              &m_openGL->m_translateX);
}
void MainWindow::on_yTransSpinBox_valueChanged(double arg1) {
  ChangeValue(moveY(m_openGL->m_model, arg1 - m_openGL->m_translateY,
                    m_openGL->m_translateY),
              &m_openGL->m_translateY);
}
void MainWindow::on_zTransSpinBox_valueChanged(double arg1) {
  ChangeValue(moveZ(m_openGL->m_model, arg1 - m_openGL->m_translateZ,
                    m_openGL->m_translateZ),
              &m_openGL->m_translateZ);
}
void MainWindow::on_xTransSlider_sliderMoved(int position) {
  ui->xTransSpinBox->setValue(position);
}
void MainWindow::on_yTransSlider_sliderMoved(int position) {
  ui->yTransSpinBox->setValue(position);
}
void MainWindow::on_zTransSlider_sliderMoved(int position) {
  ui->zTransSpinBox->setValue(position);
}
void MainWindow::on_xRotSpinBox_valueChanged(double arg1) {
  ChangeValue(rotateX(m_openGL->m_model, arg1 - m_openGL->m_rotationX,
                      m_openGL->m_rotationX),
              &m_openGL->m_rotationX);
}
void MainWindow::on_yRotSpinBox_valueChanged(double arg1) {
  ChangeValue(rotateY(m_openGL->m_model, arg1 - m_openGL->m_rotationY,
                      m_openGL->m_rotationY),
              &m_openGL->m_rotationY);
}
void MainWindow::on_zRotSpinBox_valueChanged(double arg1) {
  ChangeValue(rotateZ(m_openGL->m_model, arg1 - m_openGL->m_rotationZ,
                      m_openGL->m_rotationZ),
              &m_openGL->m_rotationZ);
}
void MainWindow::on_xRotSlider_sliderMoved(int position) {
  ui->xRotSpinBox->setValue(position);
}
void MainWindow::on_yRotSlider_sliderMoved(int position) {
  ui->yRotSpinBox->setValue(position);
}
void MainWindow::on_zRotSlider_sliderMoved(int position) {
  ui->zRotSpinBox->setValue(position);
}
void MainWindow::on_scaleSpinBox_valueChanged(double arg1) {
  ChangeValue(scaleModel(m_openGL->m_model, arg1 - m_openGL->m_scale,
                         m_openGL->m_scale),
              &m_openGL->m_scale);
}

void MainWindow::on_pushButton_clicked() {
  fileName =
      QFileDialog::getOpenFileName(this, "Open model", "", "model (*.obj)");
  if (!fileName.isEmpty()) {
    if (!loadModel(&model, fileName.toStdString().c_str())) {
      m_openGL->m_model = &model;
      ui->OpenGLWidget->show();
      ui->ControlWidget->setEnabled(true);
      loadSettings();
      m_openGL->update();
      showModelInfo();
    } else {
      QMessageBox::critical(this, "Ошибка",
                            "При открытии файла произошла ошибка!");
    }
  }
}
void MainWindow::updateUIFromModel() {
  ui->xTransSpinBox->setValue(m_openGL->m_translateX);
  ui->yTransSpinBox->setValue(m_openGL->m_translateY);
  ui->zTransSpinBox->setValue(m_openGL->m_translateZ);
  ui->xTransSlider->setValue(m_openGL->m_translateX);
  ui->yTransSlider->setValue(m_openGL->m_translateY);
  ui->zTransSlider->setValue(m_openGL->m_translateZ);
  ui->xRotSpinBox->setValue(m_openGL->m_rotationX);
  ui->yRotSpinBox->setValue(m_openGL->m_rotationY);
  ui->zRotSpinBox->setValue(m_openGL->m_rotationZ);
  ui->xRotSlider->setValue(m_openGL->m_rotationX);
  ui->yRotSlider->setValue(m_openGL->m_rotationY);
  ui->zRotSlider->setValue(m_openGL->m_rotationZ);
  ui->scaleSpinBox->setValue(m_openGL->m_scale);
  ui->vertexSizeSpinBox->setValue(m_openGL->m_pointSize);
  ui->edgeSizeSpinBox->setValue(m_openGL->m_lineSize);
}
void MainWindow::ChangeValue(float newValue, float *currentvalue) {
  *currentvalue = newValue;
  updateUIFromModel();
  m_openGL->update();
}
void MainWindow::on_BackGroundColor_clicked() {
  QColor color =
      QColorDialog::getColor(Qt::white, this, "Choose Background Color");
  m_openGL->m_backgroundColor = color;
  qss = QString("height: 19px; border: 3px solid %1").arg(color.name());
  ui->BackGroundColor->setStyleSheet(qss);
  m_openGL->update();
}
void MainWindow::on_vertexSizeSpinBox_valueChanged(double arg1) {
  m_openGL->m_pointSize = arg1;
  m_openGL->update();
}
void MainWindow::on_edgeColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Edge Color");
  m_openGL->m_edgeColor = color;
  qss = QString("height: 19px; border: 3px solid %1").arg(color.name());
  ui->edgeColor->setStyleSheet(qss);
  m_openGL->update();
}
void MainWindow::on_pointColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Vertex Color");
  m_openGL->m_pointColor = color;
  qss = QString("height: 19px; border: 3px solid %1").arg(color.name());
  ui->pointColor->setStyleSheet(qss);
  m_openGL->update();
}
void MainWindow::on_edgeSizeSpinBox_valueChanged(double arg1) {
  m_openGL->m_lineSize = arg1;
  m_openGL->update();
}
void MainWindow::AssignTextValue(float *value, QLineEdit *line, int i) {
  *value = i * line->text().toFloat();
  m_openGL->update();
}
void MainWindow::on_DashedEdges_clicked() {
  if (!m_openGL->stripLine) {
    m_openGL->stripLine = true;
    ui->DashedEdges->setText("Dashed");
  } else {
    m_openGL->stripLine = false;
    ui->DashedEdges->setText("Solid");
  }
  m_openGL->update();
}
void MainWindow::on_OrthoProjection_clicked() {
  if (!m_openGL->orthoProjection) {
    m_openGL->orthoProjection = true;
    ui->OrthoProjection->setText("Ortho");
  } else {
    m_openGL->orthoProjection = false;
    ui->OrthoProjection->setText("Perspective");
  }
  m_openGL->update();
}
void MainWindow::on_VertexTypeButton_clicked() {
  if (!m_openGL->circleVertex && !m_openGL->squareVertex) {
    ui->VertexTypeButton->setText("Square");
    m_openGL->squareVertex = true;
    m_openGL->circleVertex = false;
  } else if (m_openGL->squareVertex && !m_openGL->circleVertex) {
    ui->VertexTypeButton->setText("Circle");
    m_openGL->squareVertex = false;
    m_openGL->circleVertex = true;
  } else if (!m_openGL->squareVertex && m_openGL->circleVertex) {
    ui->VertexTypeButton->setText("None");
    m_openGL->squareVertex = false;
    m_openGL->circleVertex = false;
  }
  m_openGL->update();
}
void MainWindow::saveSettings() {
  QFile file("Settings.txt");
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    out << "BackgroundColor: " << m_openGL->m_backgroundColor.name() << "\n";
    out << "PointColor: " << m_openGL->m_pointColor.name() << "\n";
    out << "EdgeColor: " << m_openGL->m_edgeColor.name() << "\n";
    out << "Zoom: " << m_openGL->m_zoom << "\n";
    out << "RotationX: " << m_openGL->m_rotationX << "\n";
    out << "RotationY: " << m_openGL->m_rotationY << "\n";
    out << "RotationZ: " << m_openGL->m_rotationZ << "\n";
    out << "Scale: " << m_openGL->m_scale << "\n";
    out << "TranslateX: " << m_openGL->m_translateX << "\n";
    out << "TranslateY: " << m_openGL->m_translateY << "\n";
    out << "TranslateZ: " << m_openGL->m_translateZ << "\n";
    out << "PointSize: " << m_openGL->m_pointSize << "\n";
    out << "LineSize: " << m_openGL->m_lineSize << "\n";
    out << "StripLine: " << (m_openGL->stripLine ? "True" : "False") << "\n";
    out << "OrthoProjection: " << (m_openGL->orthoProjection ? "True" : "False")
        << "\n";
    out << "CircleVertex: " << (m_openGL->circleVertex ? "True" : "False")
        << "\n";
    out << "SquareVertex: " << (m_openGL->squareVertex ? "True" : "False")
        << "\n";
    file.close();
  }
}
void MainWindow::loadSettings() {
  QFile file("Settings.txt");
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    QString vertexType = "None";

    while (!in.atEnd()) {
      QString line = in.readLine();
      QStringList parts = line.split(": ");
      if (parts.size() == 2) {
        QString key = parts[0];
        QString value = parts[1];
        if (key == "BackgroundColor") {
          m_openGL->m_backgroundColor = QColor(value);
          qss = QString("height: 19px; border: 3px solid %1")
                    .arg(QColor(value).name());
          ui->BackGroundColor->setStyleSheet(qss);
        } else if (key == "PointColor") {
          m_openGL->m_pointColor = QColor(value);
          qss = QString("height: 19px; border: 3px solid %1")
                    .arg(QColor(value).name());
          ui->pointColor->setStyleSheet(qss);
        } else if (key == "EdgeColor") {
          m_openGL->m_edgeColor = QColor(value);
          qss = QString("height: 19px; border: 3px solid %1")
                    .arg(QColor(value).name());
          ui->edgeColor->setStyleSheet(qss);
        } else if (key == "Zoom")
          m_openGL->m_zoom = value.toFloat();
        else if (key == "RotationX") {
          m_openGL->m_rotationX = value.toFloat();
          rotateX(m_openGL->m_model, m_openGL->m_rotationX,
                  m_openGL->m_rotationX);
        } else if (key == "RotationY") {
          m_openGL->m_rotationY = value.toFloat();
          rotateY(m_openGL->m_model, m_openGL->m_rotationY,
                  m_openGL->m_rotationY);
        } else if (key == "RotationZ") {
          m_openGL->m_rotationZ = value.toFloat();
          rotateZ(m_openGL->m_model, m_openGL->m_rotationZ,
                  m_openGL->m_rotationZ);
        } else if (key == "Scale") {
          m_openGL->m_scale = value.toFloat();
          scaleModel(m_openGL->m_model, 0, m_openGL->m_scale);
        } else if (key == "TranslateX") {
          m_openGL->m_translateX = value.toFloat();
          moveX(m_openGL->m_model, m_openGL->m_translateX,
                m_openGL->m_translateX);
        } else if (key == "TranslateY") {
          m_openGL->m_translateY = value.toFloat();
          moveY(m_openGL->m_model, m_openGL->m_translateY,
                m_openGL->m_translateY);
        } else if (key == "TranslateZ") {
          m_openGL->m_translateZ = value.toFloat();
          moveZ(m_openGL->m_model, m_openGL->m_translateZ,
                m_openGL->m_translateZ);
        } else if (key == "PointSize")
          m_openGL->m_pointSize = value.toFloat();
        else if (key == "LineSize")
          m_openGL->m_lineSize = value.toFloat();
        else if (key == "StripLine")
          m_openGL->stripLine = (value == "True");
        else if (key == "OrthoProjection") {
          m_openGL->orthoProjection = (value == "True");
          ui->OrthoProjection->setText("Ortho");
        } else if (key == "CircleVertex") {
          m_openGL->circleVertex = (value == "True");
          if (value == "True") vertexType = "Circle";
        } else if (key == "SquareVertex") {
          m_openGL->squareVertex = (value == "True");
          if (value == "True") vertexType = "Square";
        }
      }
      ui->VertexTypeButton->setText(vertexType);
    }
    updateUIFromModel();
    file.close();
  }
}

void MainWindow::showModelInfo() {
  int numOfEdges = 0;
  int lastSlash = fileName.lastIndexOf('/');
  QString _fileName = fileName.mid(lastSlash + 1);
  int lastDot = _fileName.lastIndexOf('.');
  if (lastDot != -1) {
    _fileName = _fileName.left(lastDot);
  }
  for (size_t i = 1; i < m_openGL->m_model->size_of_faces; i++)
    numOfEdges += m_openGL->m_model->face_vertices_count[i];
  ui->statusbar->showMessage(
      "Model: " + _fileName +
      "    V: " + QString::number(m_openGL->m_model->size_of_vertices - 1) +
      ",  E: " + QString::number(numOfEdges / 2));
}

void MainWindow::on_ScreenShot_clicked() {
  QImage screenshot = m_openGL->grabFramebuffer();
  QFileDialog dialog(this, "Сохранить изображение", "",
                     "BMP Files (*.bmp);;JPEG Files (*.jpg *.jpeg)");
  dialog.setAcceptMode(QFileDialog::AcceptSave);

  if (dialog.exec() == QDialog::Accepted) {
    QString imageFileName = dialog.selectedFiles().first();
    QString selectedFilter = dialog.selectedNameFilter();
    if (selectedFilter.contains("BMP")) {
      if (!imageFileName.endsWith(".bmp", Qt::CaseInsensitive)) {
        imageFileName += ".bmp";
      }
    } else if (selectedFilter.contains("JPEG") ||
               selectedFilter.contains("JPG")) {
      if (!imageFileName.endsWith(".jpg", Qt::CaseInsensitive) &&
          !imageFileName.endsWith(".jpeg", Qt::CaseInsensitive)) {
        imageFileName += ".jpg";
      }
    }
    screenshot.save(imageFileName);
    QMessageBox::information(
        this, "Скриншот",
        "Скриншот успешно сохранен! <br>Путь к файлу: <br><br>" +
            imageFileName);
  }
}

void MainWindow::on_RecordGif_clicked() {
  gif = new QGifImage(QSize(640, 480));
  timer = new QTimer(this);
  frame_count = 0;

  QFileDialog dialog(this, "Сохранить анимацию", "", "GIF Files (*.gif)");
  dialog.setAcceptMode(QFileDialog::AcceptSave);

  if (dialog.exec() == QDialog::Accepted) {
    gifFileName = dialog.selectedFiles().first();
    QString selectedFilter = dialog.selectedNameFilter();
    if (!gifFileName.endsWith(".gif", Qt::CaseInsensitive)) {
      gifFileName += ".gif";
    }
    connect(timer, &QTimer::timeout, this, &MainWindow::renderFrame);
    ui->RecordGif->setEnabled(false);
    timer->start(100);
    start = QTime::currentTime();
  }
}

void MainWindow::renderFrame() {
  QImage frame(QSize(640, 480), QImage::Format_RGB888);
  if (frame_count < 50) {
    frame = m_openGL->grabFramebuffer().scaled(640, 480, Qt::IgnoreAspectRatio);
    gif->addFrame(frame, 0);
    if (frame_count % 5 == 0)
      ui->RecordGif->setText("Recording... " +
                             QString::number((50 - frame_count) / 10));
    frame_count++;
  } else {
    QTime end = QTime::currentTime();
    timer->stop();
    gif->save(gifFileName);
    frame_count = 0;
    ui->RecordGif->setText("GIF");
    ui->RecordGif->setEnabled(true);

    int duration = start.QTime::msecsTo(end) / 1000;
    int FPS = gif->frameCount() / duration;

    QMessageBox::information(
        this, "Запись завершена",
        "GIF-анимация успешно сохранена! <br>Количество кадров: " +
            QString::number(gif->frameCount()) +
            "<br>Продолжительность: " + QString::number(duration) +
            " сек.<br>FPS: " + QString::number(FPS) +
            "<br><br>Путь к файлу:<br>" + gifFileName);
  }
}

void MainWindow::mousePressEvent(QMouseEvent *mouse) { mPos = mouse->pos(); }

void MainWindow::mouseMoveEvent(QMouseEvent *mouse) {
  if (ui->OpenGLWidget->isVisible() && ui->OpenGLWidget->underMouse()) {
    rotX += 0.5 / M_PI * (mPos.y() - mouse->pos().y());
    rotY += 0.5 / M_PI * (mouse->pos().x() - mPos.x());
    mPos = mouse->pos();
    m_openGL->m_rotationX = rotateX(
        m_openGL->m_model, rotX - m_openGL->m_rotationX, m_openGL->m_rotationX);
    m_openGL->m_rotationY = rotateY(
        m_openGL->m_model, rotY - m_openGL->m_rotationY, m_openGL->m_rotationY);
    updateUIFromModel();
    m_openGL->update();
  }
}
