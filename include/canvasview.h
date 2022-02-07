#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include "viewzoomhandler.h"
#include <QGraphicsView>
#include <canvasstatesenums.h>
#include <maincanvas.h>
#include <moveitemhandler.h>

class CanvasView : public QGraphicsView {
  Q_OBJECT
public:
  CanvasView(QWidget *parent = nullptr);
  ~CanvasView();
  void setCanvasState(CanvasState::Shapes = CanvasState::Shapes::NONE,
                      CanvasState::State state = CanvasState::State::DRAW);
  // QWidget interface
protected:
  void wheelEvent(QWheelEvent *event) override;

private:
  MainCanvas *canvas;
  ViewZoomHandler *zoomHandler;
  MoveItemHandler *moveHandler;
};

#endif // CANVASVIEW_H
