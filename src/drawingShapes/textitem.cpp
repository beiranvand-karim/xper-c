#include "textitem.h"
#include <QBrush>
#include <QCursor>
#include <QPainter>
#include <QPen>
#include <iostream>

using namespace std;

TextItem::~TextItem() {
  delete this->pen;
  delete this->brush;
  delete this->customTextGraphics;
}

TextItem::TextItem(QPointF itemPos, QGraphicsItem *parent)
    : BaseShapeItem(parent), customTextGraphics(nullptr) {
  this->itemPos = itemPos;
  customTextGraphics = new CustomTextGraphics(itemPos, this);
  this->setCursor(QCursor(Qt::IBeamCursor));
  this->update();
}

QRectF TextItem::boundingRect() const {
  if (customTextGraphics) {
    int maxWitdth =
        max(customTextGraphics->boundingRect().width(), double(boundWidth));
    int maxHeight =
        max(customTextGraphics->boundingRect().height(), double(boundHeight));
    return QRectF(itemPos.x(), itemPos.y(), maxWitdth, maxHeight);
  }
  return QRectF(itemPos.x(), itemPos.y(), boundWidth, boundHeight);
}

void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  if (this->isSelected()) {
    BaseShapeItem::drawBorders(this->boundingRect(), painter);
    if (customTextGraphics) {
      customTextGraphics->setFocus();
    }
  } else if (this->isEnterEvent) {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::blue, 2));
    painter->drawRect(this->boundingRect());
    painter->restore();
  }
}
