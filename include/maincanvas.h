#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include <QGraphicsScene>
#include <drawingstates.h>

class BaseItem;
class MainCanvas : public QGraphicsScene {
  Q_OBJECT
public:
  explicit MainCanvas(QObject *parent);
  ~MainCanvas();
  void setCanvasState(CanvasState::Shapes = CanvasState::Shapes::NONE,
                      CanvasState::State state = CanvasState::State::DRAW);

private:
  BaseItem *currentItem;
  CanvasState::State state;
  CanvasState::Shapes shape;

  // QGraphicsScene interface
  // protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MAINCANVAS_H
