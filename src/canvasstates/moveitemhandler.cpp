#include "moveitemhandler.h"

MoveItemHandler::MoveItemHandler(QGraphicsView *view, MainCanvas *canvas)
    : QObject(view), view(view), canvas(canvas),
      modifiers(Qt::ControlModifier) {
  canvas->installEventFilter(this);
}

void MoveItemHandler::setDrawState(CanvasState::State newDrawState) {
  drawState = newDrawState;
  if (drawState == CanvasState::State::MOVE) {
    view->setCursor(Qt::PointingHandCursor);
    canvas->setItemsSelectable(true);
    canvas->setItemsMovable(true);
  }
}

bool MoveItemHandler::eventFilter(QObject *object, QEvent *event) {
  Q_UNUSED(object)
  Q_UNUSED(event)
  if (drawState == CanvasState::State::SCALE)
    return true;
  return false;
}
