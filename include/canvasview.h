#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QGraphicsView>
#include <drawingstates.h>
#include <maincanvas.h>

class CanvasView : public QGraphicsView {
  Q_OBJECT
public:
  CanvasView(QWidget *parent = nullptr);
  ~CanvasView();
  void setCanvasState(CanvasState::Shapes = CanvasState::Shapes::NONE,
                      CanvasState::State state = CanvasState::State::DRAW);

private:
  MainCanvas *canvas;
};

#endif // CANVASVIEW_H
