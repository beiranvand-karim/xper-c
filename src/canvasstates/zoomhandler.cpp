#include "zoomhandler.h"
#include <QApplication>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QWheelEvent>
#include <qmath.h>

ZoomHandler::ZoomHandler(QGraphicsView *view, MainCanvas *canvas)
    : QObject(view), view(view), canvas(canvas), modifiers(Qt::ControlModifier),
      zoomFactorBase(1.15) {

  cursorPix = QPixmap(":/icons/scale-cursor.png");
  scaleCursor = QCursor(cursorPix);
  view->setMouseTracking(true);
  view->installEventFilter(this);
}

void ZoomHandler::setDrawState(CanvasState::State newDrawState) {
  drawState = newDrawState;
  if (drawState == CanvasState::State::SCALE) {
    view->cursor() = scaleCursor;
    view->setCursor(scaleCursor);
    view->update();
    canvas->setItemsSelectable(false);
    canvas->setItemsMovable(false);
    canvas->update();
  }
}

bool ZoomHandler::eventFilter(QObject *object, QEvent *event) {
  if (drawState == CanvasState::State::SCALE) {
    if (event->type() == QEvent::KeyPress)
      onKeyPressed(event);
    else if (event->type() == QEvent::MouseButtonPress)
      onMousePressed(event);
  }
  return QObject::eventFilter(object, event);
}

void ZoomHandler::zoom(double factor) {
  view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  view->scale(factor, factor);
}

void ZoomHandler::onKeyPressed(QEvent *event) {
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

void ZoomHandler::onMousePressed(QEvent *event) {
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

void ZoomHandler::onMouseWheel(QWheelEvent *event) {
  double degree = event->angleDelta().y() / 8.0;
  double numSteps = degree / 15;
  double factor = std::pow(1.25, numSteps);
  zoom(factor);
}
