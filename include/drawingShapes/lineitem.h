#ifndef LINEITEM_H
#define LINEITEM_H

#include "baseshapeitem.h"

class LineItem : public BaseShapeItem {

public:
  LineItem(QPointF firstPoint = QPointF(0, 0), QGraphicsItem *parent = nullptr);
  ~LineItem();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void setSecondPoint(QPointF newSecondPoint);

  // BaseShapeItem interface
public:
  void setBoundWidth(int boundWidth) override;
  void setBoundHeight(int boundHeight) override;

private:
  QPointF secondPoint;
};

#endif // LINEITEM_H
