#include "baseshapeitem.h"

BaseShapeItem::BaseShapeItem(QGraphicsItem *parent)
    : QGraphicsItem(parent), isEnterEvent(false), borderWidth(1), boundWidth(0),
      boundHeight(0), brush(new QBrush(Qt::gray)), pen(new QPen(Qt::gray)) {
  this->setFlag(ItemIsSelectable);
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

int BaseShapeItem::getBoundWidth() const { return boundWidth; }

int BaseShapeItem::getBoundHeight() const { return boundHeight; }

QPointF BaseShapeItem::getItemPos() const { return itemPos; }

void BaseShapeItem::setItemPos(QPointF newItemPos) {
  if (this->itemPos != newItemPos) {
    prepareGeometryChange();
    this->itemPos = newItemPos;
    this->update();
  }
}

void BaseShapeItem::setBoundWidth(int boundWidth) {
  if (this->boundWidth != boundWidth) {
    prepareGeometryChange();
    this->boundWidth = boundWidth;
    this->update();
  }
}

void BaseShapeItem::setBoundHeight(int boundHeight) {
  if (this->boundHeight != boundHeight) {
    prepareGeometryChange();
    this->boundHeight = boundHeight;
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
