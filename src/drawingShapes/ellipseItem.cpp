#include "ellipseitem.h"
#include "iostream"
#include <QColor>
#include <QPainter>

using namespace std;

EllipseItem::~EllipseItem() {
  delete this->pen;
  delete this->brush;
}
EllipseItem::EllipseItem(QPointF itemPos, QGraphicsScene *parent)
    : BaseShapeItem(parent) {
  this->firstPoint = itemPos;
  this->lastPoint = itemPos;
}

QRectF EllipseItem::boundingRect() const {
  return QRectF(this->firstPoint, this->lastPoint).normalized();
}

void EllipseItem::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QPainterPath path;
  path.addEllipse(this->boundingRect());
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(*this->pen);
  painter->setBrush(*this->brush);
  painter->drawPath(path);
  painter->restore();
  if (this->isSelected())
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  else if (this->isEnterEvent)
    BaseShapeItem::drawShapeOnHover(path, painter);
}
