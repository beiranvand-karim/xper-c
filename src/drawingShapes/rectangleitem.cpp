#include "rectangleitem.h"
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "iostream"
using namespace std;

RectangleItem::~RectangleItem() {
  delete pen;
  delete brush;
}
RectangleItem::RectangleItem(QPointF itemPos, QGraphicsItem *parent)
    : BaseShapeItem(parent), radiusX(0), radiusY(0) {
  this->itemPos = itemPos;
}

QRectF RectangleItem::boundingRect() const {
  return QRectF(this->itemPos.x(), this->itemPos.y(), this->boundWidth,
                this->boundHeight);
}

void RectangleItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget) {
  QStyleOptionGraphicsItem opt(*option);
  opt.state = QStyle::State_None;
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(*this->pen);
  painter->setBrush(*this->brush);
  painter->drawRoundedRect(this->boundingRect(), this->radiusX, this->radiusY);
  painter->restore();
  if (this->isSelected()) {
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  } else if (this->isEnterEvent) {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::blue, 2));
    painter->drawRect(this->boundingRect());
    painter->restore();
  }
}
