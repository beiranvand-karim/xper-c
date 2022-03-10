#include "lineitem.h"
#include "iostream"
using namespace std;

LineItem::~LineItem() {
  delete this->pen;
  delete this->brush;
}

LineItem::LineItem(QPointF firstPoint, QGraphicsScene *parent)
    : BaseShapeItem(parent), isClicked(false) {
  this->firstPoint = firstPoint;
  this->secondPoint = this->firstPoint;
}

QRectF LineItem::boundingRect() const { return this->shape().boundingRect(); }

QPainterPath LineItem::shape() const {
  QPainterPath lineShape;
  QPolygonF poly;
  lineShape.moveTo(this->firstPoint);
  lineShape.lineTo(this->secondPoint);
  poly << this->firstPoint - QPointF(15, 15)
       << this->firstPoint + QPointF(-15, 15)
       << this->secondPoint + QPointF(15, 15)
       << this->secondPoint + QPointF(15, -15)
       << this->firstPoint - QPointF(15, 15);
  lineShape.addPolygon(poly);
  return lineShape;
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QPainterPath path;
  path.moveTo(this->firstPoint);
  path.lineTo(this->secondPoint);
  painter->save();
  painter->setPen(*this->pen);
  painter->setBrush(*this->brush);
  painter->setRenderHint(QPainter::Antialiasing);
  if (!this->secondPoint.isNull())
    painter->drawPath(path);
  painter->restore();
  if (isSelected() && isClicked) {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::darkBlue, 2));
    painter->drawLine(this->firstPoint, this->secondPoint);
    painter->restore();
  } else if (this->isEnterEvent) {
    BaseShapeItem::drawShapeOnHover(path, painter);
  }
}

void LineItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  this->isClicked = true;
  this->update();
  BaseShapeItem::mousePressEvent(event);
}
