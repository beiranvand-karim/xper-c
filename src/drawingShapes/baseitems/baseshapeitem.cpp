#include "baseshapeitem.h"

#include <QGraphicsScene>

BaseShapeItem::BaseShapeItem(QGraphicsScene *parent)
    : mainCanvas(parent), isEnterEvent(false), brush(new QBrush(Qt::darkGray)),
      pen(new QPen(Qt::darkGray, 1)), boundWidth(0), boundHeight(0) {
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

qreal BaseShapeItem::getBoundHeight() const { return boundHeight; }

void BaseShapeItem::setBoundHeight(qreal newBoundHeight) {
  boundHeight = newBoundHeight;
}

qreal BaseShapeItem::getBoundWidth() const { return boundWidth; }

void BaseShapeItem::setBoundWidth(qreal newBoundWidth) {
  boundWidth = newBoundWidth;
}
QPointF BaseShapeItem::getFirstPoint() const { return firstPoint; }
QPointF BaseShapeItem::getSecondPoint() const { return secondPoint; }

void BaseShapeItem::setSecondPoint(QPointF newPoint) {
  if (this->secondPoint != newPoint) {
    prepareGeometryChange();
    this->secondPoint = newPoint;
    setBoundWidth(this->secondPoint.x() - this->firstPoint.x());
    setBoundHeight(this->secondPoint.y() - this->firstPoint.y());
    this->update();
  }
}

void BaseShapeItem::setFirstPoint(QPointF newPoint) {
  if (this->firstPoint != newPoint) {
    prepareGeometryChange();
    this->firstPoint = newPoint;
    this->update();
  }
}

void BaseShapeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
  this->isEnterEvent = true;
  QGraphicsItem::hoverEnterEvent(event);
};

void BaseShapeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
  this->isEnterEvent = false;
  QGraphicsItem::hoverEnterEvent(event);
};

bool BaseShapeItem::validateItemInsertion() {
  if (this->firstPoint == this->secondPoint)
    return false;
  return true;
}
