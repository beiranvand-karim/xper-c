#ifndef ELLIPSEITEM_H
#define ELLIPSEITEM_H

#include "baseshapeitem.h"

class EllipseItem : public BaseShapeItem {

public:
  EllipseItem(QPointF itemPos = QPointF(20, 20),
              QGraphicsScene *parent = nullptr);

  ~EllipseItem();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
};

#endif // ELLIPSEITEM_H
