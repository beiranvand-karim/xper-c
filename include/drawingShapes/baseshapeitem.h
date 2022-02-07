#ifndef BASEITEM_H
#define BASEITEM_H

#include <QBrush>
#include <QColor>
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>

class BaseShapeItem : public QGraphicsItem {

public:
  virtual ~BaseShapeItem() = default;

  QPointF getFirstPoint() const;
  void setFirstPoint(QPointF newItemPos);
  QPointF getLastPoint() const;
  virtual void setLastPoint(QPointF newLastPoint);
  virtual bool validateItemInsertion();

protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

protected:
  BaseShapeItem(QGraphicsScene *mainCanvas);
  void drawBorders(QRectF boundingRect, QPainter *painter);
  void drawShapeOnHover(QPainterPath &path, QPainter *painter);

  QGraphicsScene *mainCanvas;
  int id;
  bool isEnterEvent;
  QBrush *brush;
  QPen *pen;
  QPointF firstPoint, lastPoint;
};

#endif // BASEITEM_H
