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
RectangleItem::RectangleItem(QPointF itemPos, QGraphicsScene *parent)
    : BaseShapeItem(parent), radiusX(0), radiusY(0) {
  this->firstPoint = itemPos;
  this->lastPoint = itemPos;
}

QRectF RectangleItem::boundingRect() const {
  return QRectF(this->firstPoint, this->lastPoint).normalized();
}

void RectangleItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QPainterPath path;
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(*this->pen);
  painter->setBrush(*this->brush);
  path.addRoundedRect(this->boundingRect(), this->radiusX, this->radiusY);
  painter->drawPath(path);
  painter->restore();
  if (this->isSelected()) {
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
  } else if (this->isEnterEvent) {
    BaseShapeItem::drawShapeOnHover(path, painter);
  }
}
