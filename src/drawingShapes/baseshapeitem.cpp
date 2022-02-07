#include "baseshapeitem.h"

#include <QGraphicsScene>

BaseShapeItem::BaseShapeItem(QGraphicsScene *parent)
    : mainCanvas(parent), isEnterEvent(false), brush(new QBrush(Qt::darkGray)),
      pen(new QPen(Qt::gray, 2)) {
  this->setFlags(ItemIsSelectable);
  this->setAcceptHoverEvents(true);
}

void BaseShapeItem::drawBorders(QRectF boundingRect, QPainter *painter) {
  painter->save();
  QPen pen(Qt::darkBlue);
  pen.setWidth(1);
  painter->setPen(pen);
  painter->drawRect(boundingRect);
  painter->restore();
}

void BaseShapeItem::drawShapeOnHover(QPainterPath &path, QPainter *painter) {
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(QPen(Qt::darkBlue, 2));
  painter->drawPath(path);
  painter->restore();
}
QPointF BaseShapeItem::getFirstPoint() const { return firstPoint; }
QPointF BaseShapeItem::getLastPoint() const { return lastPoint; }

void BaseShapeItem::setLastPoint(QPointF newLastPoint) {
  if (this->lastPoint != newLastPoint) {
    prepareGeometryChange();
    this->lastPoint = newLastPoint;
    this->update();
  }
}

void BaseShapeItem::setFirstPoint(QPointF newItemPos) {
  if (this->firstPoint != newItemPos) {
    prepareGeometryChange();
    this->firstPoint = newItemPos;
    this->update();
  }
}

void BaseShapeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
  this->isEnterEvent = true;
  QGraphicsItem::hoverEnterEvent(event);
};
;

void BaseShapeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
  this->isEnterEvent = false;
  QGraphicsItem::hoverEnterEvent(event);
};

bool BaseShapeItem::validateItemInsertion() {
  if (qAbs(this->lastPoint.x() - this->firstPoint.x()) > 0 &&
      qAbs(this->lastPoint.y() - this->firstPoint.y()) > 0)
    return true;
  return false;
}
