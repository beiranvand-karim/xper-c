#include "canvasview.h"
#include "iostream"
#include <QAction>

using namespace std;

CanvasView::CanvasView(QWidget *parent) : QGraphicsView(parent) {
  canvas = new MainCanvas(this);
  this->setScene(canvas);
  setMouseTracking(canvas);
  this->show();
}

CanvasView::~CanvasView() { delete canvas; }

void CanvasView::setCanvasState(CanvasState::Shapes shape,
                                CanvasState::State state) {
  canvas->setCanvasState(shape, state);
}
