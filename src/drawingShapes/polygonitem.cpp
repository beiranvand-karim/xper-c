#include "polygonitem.h"
#include <QColor>
#include <QPainter>

PolygonItem::~PolygonItem() {
  delete this->pen;
  delete this->brush;
}
PolygonItem::PolygonItem(QPointF itemPos, QGraphicsItem *parent)
    : BaseShapeItem(parent) {
  this->itemPos = itemPos;
}

QRectF PolygonItem::boundingRect() const {
  return QRectF(this->itemPos.x(), this->itemPos.y(), this->boundWidth,
                this->boundHeight);
}

void PolygonItem::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(*this->pen);
  painter->setBrush(*this->brush);
  QPolygonF polyPoints;
  QRectF bound = this->boundingRect();
  polyPoints << QPointF(bound.bottomLeft())
             << QPointF(this->boundingRect().center().x(),
                        this->boundingRect().topRight().y())
             << QPointF(bound.bottomRight());

  painter->drawPolygon(polyPoints);
  painter->restore();
  if (this->isSelected()) {
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  } else if (this->isEnterEvent) {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::blue, 2));
    painter->drawPolygon(polyPoints);
    painter->restore();
  }
}
