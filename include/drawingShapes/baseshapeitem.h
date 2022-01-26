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
  virtual void setBoundWidth(int boundWidth);
  virtual void setBoundHeight(int boundHeight);

  // QGraphicsItem interface
  QPointF getItemPos() const;
  void setItemPos(QPointF newItemPos);
  int getBoundWidth() const;
  int getBoundHeight() const;

protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

protected:
  BaseShapeItem(QGraphicsItem *parent = nullptr);
  void drawBorders(QRectF boundingRect, QPainter *painter);

  int id;
  bool isEnterEvent;
  int borderWidth, boundWidth, boundHeight;
  QBrush *brush;
  QPen *pen;
  QPointF itemPos;
};

#endif // BASEITEM_H
