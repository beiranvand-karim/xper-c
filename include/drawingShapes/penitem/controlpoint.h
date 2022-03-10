#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include "basepoint.h"

class ControlPoint : public BasePoint {
public:
  ControlPoint(QPointF itemPos, QGraphicsItem *parent = nullptr,
               QGraphicsScene *mainCanvas = nullptr);
  ~ControlPoint();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  BasePoint *getSymmetryPoint() const;
  void setSymmetryPoint(BasePoint *newSymmetryPoint);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
  BasePoint *symmetryPoint;
};

#endif // CONTROLPOINT_H
