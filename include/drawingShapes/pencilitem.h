#ifndef PENCILITEM_H
#define PENCILITEM_H

#include <baseshapeitem.h>

class PencilItem : public BaseShapeItem {
public:
  PencilItem(QPointF itemFirstPos, QGraphicsScene *parent = nullptr);
  ~PencilItem();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

  // BaseShapeItem interface
public:
  bool validateItemInsertion() override;
  void setLastPoint(QPointF newLastPoint) override;

private:
  QPolygonF poly;
  bool isClicked;
};

#endif // PENCILITEM_H
