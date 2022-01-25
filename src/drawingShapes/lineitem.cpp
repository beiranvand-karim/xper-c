#include "lineitem.h"

LineItem::~LineItem() {
  delete this->pen;
  delete this->brush;
}

LineItem::LineItem(QPointF firstPoint, QGraphicsItem *parent)
    : BaseShapeItem(parent) {
  this->itemPos = firstPoint;
}

QRectF LineItem::boundingRect() const {
  return QRectF(itemPos.x(), itemPos.y(), boundWidth, boundHeight);
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  painter->save();
  this->pen->setWidth(2);
  painter->setPen(*this->pen);
  painter->setBrush(*this->brush);
  painter->setRenderHint(QPainter::Antialiasing);
  if (!secondPoint.isNull())
    painter->drawLine(itemPos, secondPoint);
  painter->restore();
  if (isSelected())
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  else if (this->isEnterEvent) {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::darkBlue, 2));
    painter->drawLine(itemPos, secondPoint);
    painter->restore();
  }
}

void LineItem::setSecondPoint(QPointF newSecondPoint) {
  if (this->secondPoint != newSecondPoint) {
    this->prepareGeometryChange();
    secondPoint = newSecondPoint;
    this->update();
  }
}

void LineItem::setBoundWidth(int boundWidth) {
  BaseShapeItem::setBoundWidth(boundWidth);
  this->setSecondPoint(QPointF(this->boundWidth + this->itemPos.x(),
                               this->boundHeight + this->itemPos.y()));
  this->update();
}

void LineItem::setBoundHeight(int boundHeight) {
  BaseShapeItem::setBoundHeight(boundHeight);
  this->setSecondPoint(QPointF(this->boundWidth + this->itemPos.x(),
                               this->boundHeight + this->itemPos.y()));
}
