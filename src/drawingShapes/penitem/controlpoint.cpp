#include "controlpoint.h"

ControlPoint::ControlPoint(QPointF itemPos, QGraphicsItem *parent,
                           QGraphicsScene *mainCanvas)
    : BasePoint(itemPos, parent, mainCanvas), symmetryPoint(nullptr) {
  this->setParentItem(parent);
}

ControlPoint::~ControlPoint() {}

QRectF ControlPoint::boundingRect() const { return BasePoint::boundingRect(); }

QPainterPath ControlPoint::shape() const { return BasePoint::shape(); }

void ControlPoint::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  return BasePoint::paint(painter, option, widget);
}

void ControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  BasePoint::mouseMoveEvent(event);
  if (symmetryPoint) {
    symmetryPoint->setPos(-this->pos());
  }
}

BasePoint *ControlPoint::getSymmetryPoint() const { return symmetryPoint; }

void ControlPoint::setSymmetryPoint(BasePoint *newSymmetryPoint) {
  if (this->symmetryPoint) {
    this->symmetryPoint = nullptr;
  }
  symmetryPoint = newSymmetryPoint;
  this->update();
}
