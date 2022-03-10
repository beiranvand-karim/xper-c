#include "selectionhandler.h"

SelectionHandler::SelectionHandler(QGraphicsView *view, MainCanvas *canvas)
    : QObject(view), view(view), canvas(canvas),
      modifiers(Qt::ControlModifier) {
  canvas->installEventFilter(this);
}

void SelectionHandler::setDrawState(CanvasState::State newDrawState) {
  drawState = newDrawState;
  if (drawState == CanvasState::State::MOVE) {
    view->setCursor(Qt::PointingHandCursor);
    view->update();
    canvas->setItemsSelectable(true);
    canvas->setItemsMovable(true);
    canvas->update();
  }
}

bool SelectionHandler::eventFilter(QObject *object, QEvent *event) {
  if (drawState == CanvasState::State::SCALE)
    return true;
  return QObject::eventFilter(object, event);
}
