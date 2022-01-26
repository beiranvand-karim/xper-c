#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include <QGraphicsScene>
#include <drawingstates.h>
#include <rectangleitem.h>

class MainCanvas : public QGraphicsScene {
  Q_OBJECT
public:
  explicit MainCanvas(QObject *parent);
  ~MainCanvas();
  void setCanvasState(CanvasState::Shapes = CanvasState::Shapes::NONE,
                      CanvasState::State state = CanvasState::State::DRAW);
  void setItemsMovable(bool isMovable);
  void setItemsSelectable(bool isSelectable);
  // QGraphicsScene interface
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  BaseShapeItem *onDrawShape(QPointF itemPos);

private:
  BaseShapeItem *currentItem;
  CanvasState::State state;
  CanvasState::Shapes shape;
  bool mousePressed;
};

#endif // MAINCANVAS_H
