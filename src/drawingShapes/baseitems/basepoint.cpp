#include "basepoint.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

BasePoint::BasePoint(QPointF point, QGraphicsItem *parent,
                           QGraphicsScene *scene)
    : BaseShapeItem(scene) {
  this->pen = new QPen(Qt::NoPen);
  this->brush = new QBrush(Qt::yellow);
  this->firstPoint = point;
  this->secondPoint = this->firstPoint;
  this->setParentItem(parent);
  this->setZValue(2);
}

BasePoint::~BasePoint() {
  delete this->pen;
  delete this->brush;
}

QRectF BasePoint::boundingRect() const {
  return this->shape().boundingRect();
}

void BasePoint::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(*this->pen);
  painter->setBrush(*this->brush);
  painter->drawPath(this->shape());
  if (this->isEnterEvent) {
    painter->setPen(QColor(23, 236, 236));
    painter->drawPath(this->shape());
  }
  painter->restore();
}

QPainterPath BasePoint::shape() const {
  QPainterPath path;
  path.addEllipse(this->firstPoint, 6, 6);
  return path;
}

void BasePoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  BaseShapeItem::mouseMoveEvent(event);
  this->update();
  this->parentItem()->update();
}

QPointF BasePoint::getPos() { return this->sceneBoundingRect().center(); }
