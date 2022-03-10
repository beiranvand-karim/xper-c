#include "pencilitem.h"

#include "iostream"
#include <QPen>

using namespace std;

PencilItem::~PencilItem() {
  delete this->pen;
  delete this->brush;
}
PencilItem::PencilItem(QPointF itemFirstPos, QGraphicsScene *parent)
    : BaseShapeItem(parent), isClicked(false) {
  this->firstPoint = this->secondPoint;
  this->secondPoint = this->firstPoint;
  poly << itemFirstPos;
}

QRectF PencilItem::boundingRect() const { return QRectF(poly.boundingRect()); }

void PencilItem::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->save();
  painter->setPen(*this->pen);
  painter->setBrush(*this->brush);
  painter->setRenderHint(QPainter::Antialiasing);
  if (!this->secondPoint.isNull())
    painter->drawPolyline(poly);
  painter->restore();
  if (this->isSelected() && isClicked) {
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  } else if (this->isEnterEvent) {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::darkBlue, 2));
    painter->drawPolyline(poly);
    painter->restore();
  }
}

bool PencilItem::validateItemInsertion() {
  if (BaseShapeItem::validateItemInsertion() && poly.length() > 1)
    return true;
  return false;
}

void PencilItem::setSecondPoint(QPointF newPoint) {
  BaseShapeItem::setSecondPoint(newPoint);
  if (!this->secondPoint.isNull()) {
    poly << this->secondPoint;
  }
  this->update();
}

void PencilItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  this->isClicked = true;
  this->update();
  BaseShapeItem::mousePressEvent(event);
}
