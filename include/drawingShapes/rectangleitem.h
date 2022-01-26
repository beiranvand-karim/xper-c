#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include "baseshapeitem.h"

class RectangleItem : public BaseShapeItem {
public:
  RectangleItem(QPointF itemPos = QPointF(20, 20),
                QGraphicsItem *parent = nullptr);
  ~RectangleItem();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

private:
  int radiusX, radiusY;
};

#endif // RECTANGLEITEM_H
