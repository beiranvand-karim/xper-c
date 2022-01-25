#include "viewzoomhandler.h"
#include "iostream"
#include <QApplication>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QTransform>
#include <QWheelEvent>
#include <qmath.h>

using namespace std;

ViewZoomHandler::ViewZoomHandler(QGraphicsView *view)
    : QObject(view), view(view) {
  view->setMouseTracking(true);
  view->installEventFilter(this);

  modifiers = Qt::ControlModifier;
  zoomFactorBase = 1.15;
}

void ViewZoomHandler::setDrawState(CanvasState::State newDrawState) {
  drawState = newDrawState;
}

bool ViewZoomHandler::eventFilter(QObject *object, QEvent *event) {
  if (drawState == CanvasState::State::SCALE) {
    if (event->type() == QEvent::KeyPress)
      onKeyPressed(event);
    else if (event->type() == QEvent::MouseButtonPress)
      onMousePressed(event);
  }
  return QObject::eventFilter(object, event);
}

void ViewZoomHandler::zoom(double factor) {
  view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  view->scale(factor, factor);
}

void ViewZoomHandler::onKeyPressed(QEvent *event) {
  auto keyEvent = static_cast<QKeyEvent *>(event);
  switch (keyEvent->key()) {
  case Qt::Key_Plus: {
    this->zoom(zoomFactorBase + 0.05);
    break;
  }
  case Qt::Key_Minus: {
    this->zoom(1 / zoomFactorBase);
    break;
  }
  default:
    break;
  }
}

void ViewZoomHandler::onMousePressed(QEvent *event) {
  auto mouseEvent = static_cast<QMouseEvent *>(event);
  switch (mouseEvent->button()) {
  case Qt::LeftButton: {
    this->zoom(zoomFactorBase + 0.05);
    break;
  }
  case Qt::RightButton: {
    this->zoom(1 / zoomFactorBase);
    break;
  }
  default:
    break;
  }
}

void ViewZoomHandler::onMouseWheel(QWheelEvent *event) {
  double degree = event->angleDelta().y() / 8.0;
  double numSteps = degree / 15;
  double factor = std::pow(1.25, numSteps);
  zoom(factor);
}
