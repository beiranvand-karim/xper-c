#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include <QGraphicsScene>
#include <baseshapeitem.h>
#include <canvasstatesenums.h>
#include <penitem.h>

class MainCanvas : public QGraphicsScene {
  Q_OBJECT
public:
  explicit MainCanvas(QGraphicsView *view);
  ~MainCanvas();
  void setCanvasState(CanvasState::Shapes = CanvasState::Shapes::NONE,
                      CanvasState::State state = CanvasState::State::DRAW);
  void setItemsMovable(bool isMovable);
  void setItemsSelectable(bool isSelectable);
  void deleteCurrentItem();
  // QGraphicsScene interface
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  BaseShapeItem *onDrawShape(QPointF itemPos);

private:
  QGraphicsView *view;
  BaseShapeItem *currentItem;
  PenItem *currentPenItem;
  CanvasState::State state;
  CanvasState::Shapes currentShapeType, lastShapeType;
  bool mousePressed;
};

#endif // MAINCANVAS_H
