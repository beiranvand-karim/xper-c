#ifndef VIEWZOOMHANDLER_H
#define VIEWZOOMHANDLER_H

#include "canvasstatesenums.h"
#include <QGraphicsView>
#include <QObject>
#include <maincanvas.h>

class ViewZoomHandler : public QObject {
  Q_OBJECT
public:
  ViewZoomHandler(QGraphicsView *view, MainCanvas *canvas);

  void setDrawState(CanvasState::State newDrawState);
  void onMouseWheel(QWheelEvent *event);

private:
  bool eventFilter(QObject *object, QEvent *event) override;
  void zoom(double factor);
  void onKeyPressed(QEvent *event);
  void onMousePressed(QEvent *event);

  QGraphicsView *view;
  MainCanvas *canvas;
  Qt::KeyboardModifiers modifiers;
  double zoomFactorBase;
  CanvasState::State drawState;
  QPixmap cursorPix;
  QCursor scaleCursor;
};

#endif // VIEWZOOMHANDLER_H
