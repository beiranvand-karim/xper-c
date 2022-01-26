#ifndef VIEWZOOMHANDLER_H
#define VIEWZOOMHANDLER_H

#include "drawingstates.h"
#include <QGraphicsView>
#include <QObject>

class ViewZoomHandler : public QObject {
  Q_OBJECT
public:
  ViewZoomHandler(QGraphicsView *view);

  void setDrawState(CanvasState::State newDrawState);
  void onMouseWheel(QWheelEvent *event);

private:
  bool eventFilter(QObject *object, QEvent *event) override;
  void zoom(double factor);
  void onKeyPressed(QEvent *event);
  void onMousePressed(QEvent *event);

  QGraphicsView *view;
  Qt::KeyboardModifiers modifiers;
  double zoomFactorBase;
  CanvasState::State drawState;
};

#endif // VIEWZOOMHANDLER_H
