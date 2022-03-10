#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include "zoomhandler.h"
#include <QGraphicsView>
#include <canvasstatesenums.h>
#include <maincanvas.h>
#include <selectionhandler.h>

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
  ZoomHandler *zoomHandler;
  SelectionHandler *selectionHandler;
};

#endif // CANVASVIEW_H
