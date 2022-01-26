#include "mainwindow.h"
#include "QScreen"
#include "drawingstates.h"
#include "iostream"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("XPER QT");

  QSize screenSize = qApp->screens()[0]->size();
  int appWidth = screenSize.width() / 100 * 80;
  int appHeight = screenSize.height() / 100 * 80;
  auto xCoordinate = (screenSize.width() - appWidth) / 2;
  auto yCoordinate = (screenSize.height() - appHeight) / 2;
  move(xCoordinate, yCoordinate);
  this->resize(appWidth, appHeight);

  canvasView = ui->canvasView;
  ui->scrolledMenu->resize(appWidth / 5 * 1, 0);
  ui->scrolledCanvas->resize(appWidth / 5 * 4, 0);
}

MainWindow::~MainWindow() {
  delete ui;
  delete canvasView;
}

void MainWindow::on_moveAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::NONE,
                                   CanvasState::State::MOVE);
}

void MainWindow::on_scaleAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::NONE,
                                   CanvasState::State::SCALE);
}

void MainWindow::on_frameAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::NONE,
                                   CanvasState::State::FRAME);
}

void MainWindow::on_rectAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::RECTANGLE);
}

void MainWindow::on_ellipseAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::ELLIPSE);
}

void MainWindow::on_penAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::PEN);
}

void MainWindow::on_pencilAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::PENCIL);
}

void MainWindow::on_lineAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::LINE);
}

void MainWindow::on_polygonAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::POLYGON);
}

void MainWindow::on_imageAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::IMAGE);
}

void MainWindow::on_textAction_triggered() {
  this->canvasView->setCanvasState(CanvasState::Shapes::TEXT);
}
