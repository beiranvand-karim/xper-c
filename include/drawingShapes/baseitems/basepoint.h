#ifndef POINTHANDLER_H
#define POINTHANDLER_H

#include <baseshapeitem.h>

class BasePoint : public BaseShapeItem {
public:
  BasePoint(QPointF point, QGraphicsItem *parent = nullptr,
               QGraphicsScene *scene = nullptr);
  ~BasePoint();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QPainterPath shape() const override;
  QPointF getPos();

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // POINTHANDLER_H
