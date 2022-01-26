#include "ellipseitem.h"
#include "iostream"
#include <QColor>
#include <QPainter>

using namespace std;

EllipseItem::~EllipseItem() {
  delete this->pen;
  delete this->brush;
}
EllipseItem::EllipseItem(QPointF itemPos, QGraphicsItem *parent)
    : BaseShapeItem(parent) {
  this->itemPos = itemPos;
}

QRectF EllipseItem::boundingRect() const {
  return QRectF(this->itemPos.x(), this->itemPos.y(), this->boundWidth,
                this->boundHeight);
}

void EllipseItem::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(*this->pen);
  painter->setBrush(*this->brush);
  painter->drawEllipse(this->boundingRect());
  painter->restore();
  if (this->isSelected()) {
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
    return;
  } else if (this->isEnterEvent) {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::blue, 2));
    painter->drawEllipse(this->boundingRect());
    painter->restore();
    return;
  }
}
