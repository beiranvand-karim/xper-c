#include "polygonitem.h"
#include <QColor>
#include <QPainter>

PolygonItem::~PolygonItem() {
  delete this->pen;
  delete this->brush;
}
PolygonItem::PolygonItem(QPointF itemPos, QGraphicsScene *parent)
    : BaseShapeItem(parent) {
  this->firstPoint = itemPos;
  this->lastPoint = itemPos;
}

QRectF PolygonItem::boundingRect() const {
  return QRectF(this->firstPoint, this->lastPoint).normalized();
}

void PolygonItem::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QPainterPath path;
  QPolygonF polygon;
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(*this->pen);
  painter->setBrush(*this->brush);
  QRectF bound = this->boundingRect();
  polygon << QPointF(bound.bottomLeft())
          << QPointF(this->boundingRect().center().x(),
                     this->boundingRect().topRight().y())
          << QPointF(bound.bottomRight());

  polygon.push_back(polygon.first());
  path.addPolygon(polygon);
  painter->drawPath(path);
  painter->restore();
  if (this->isSelected()) {
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  } else if (this->isEnterEvent) {
    BaseShapeItem::drawShapeOnHover(path, painter);
  }
}
