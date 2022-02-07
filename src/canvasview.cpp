#include "canvasview.h"
#include "iostream"
#include <QAction>
#include <QApplication>
#include <QCursor>
#include <QScrollBar>
#include <QWheelEvent>

using namespace std;

CanvasView::CanvasView(QWidget *parent) : QGraphicsView(parent) {
  canvas = new MainCanvas(this);
  zoomHandler = new ViewZoomHandler(this, canvas);
  moveHandler = new MoveItemHandler(this, canvas);
  this->setScene(canvas);
  this->setMouseTracking(canvas);
  this->show();
}

CanvasView::~CanvasView() {
  delete canvas;
  delete zoomHandler;
}

void CanvasView::setCanvasState(CanvasState::Shapes shape,
                                CanvasState::State state) {
  moveHandler->setDrawState(state);
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
