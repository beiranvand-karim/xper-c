#include "canvasview.h"
#include "iostream"
#include <QAction>
#include <QApplication>
#include <QCursor>
#include <QScrollBar>
#include <QWheelEvent>

using namespace std;

CanvasView::CanvasView(QWidget *parent) : QGraphicsView(parent) {
  zoomHandler = new ViewZoomHandler(this);
  canvas = new MainCanvas(this);
  this->setScene(canvas);
  setMouseTracking(canvas);
  this->show();
}

CanvasView::~CanvasView() {
  delete canvas;
  delete zoomHandler;
}

void CanvasView::setCanvasState(CanvasState::Shapes shape,
                                CanvasState::State state) {
  if (state == CanvasState::State::SCALE) {
    this->setCursor(Qt::OpenHandCursor);
  } else {
    this->setCursor(Qt::CrossCursor);
  }
  zoomHandler->setDrawState(state);
  canvas->setCanvasState(shape, state);
}

void CanvasView::wheelEvent(QWheelEvent *event) {
  this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  if (QApplication::keyboardModifiers() == Qt::ControlModifier)
    zoomHandler->onMouseWheel(event);
  else {
    QGraphicsView::wheelEvent(event);
  }
}
