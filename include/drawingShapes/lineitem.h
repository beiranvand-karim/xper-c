#ifndef LINEITEM_H
#define LINEITEM_H

#include "baseshapeitem.h"

class LineItem : public BaseShapeItem {

public:
  LineItem(QPointF firstPoint = QPointF(0, 0),
           QGraphicsScene *parent = nullptr);
  ~LineItem();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QPainterPath shape() const override;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  bool isClicked;
};

#endif // LINEITEM_H
