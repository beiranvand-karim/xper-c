#ifndef BASESHAPEITEM_H
#define BASESHAPEITEM_H

#include <QBrush>
#include <QColor>
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>

class BaseShapeItem : public QGraphicsItem {

public:
  virtual ~BaseShapeItem() = default;

  virtual QPointF getFirstPoint() const;
  virtual void setFirstPoint(QPointF firstPoint);

  virtual QPointF getSecondPoint() const;
  virtual void setSecondPoint(QPointF secondPoint);

  virtual bool validateItemInsertion();

  qreal getBoundWidth() const;
  void setBoundWidth(qreal newBoundWidth);

  qreal getBoundHeight() const;
  void setBoundHeight(qreal newBoundHeight);

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
  QPointF firstPoint, secondPoint;
  qreal boundWidth, boundHeight;
};

#endif // BASESHAPEITEM_H
