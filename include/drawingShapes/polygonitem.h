#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include "baseshapeitem.h"

class PolygonItem : public BaseShapeItem {

public:
  PolygonItem(QPointF itemPos = QPointF(20, 20),
              QGraphicsItem *parent = nullptr);

  ~PolygonItem();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
};

#endif // POLYGONITEM_H
