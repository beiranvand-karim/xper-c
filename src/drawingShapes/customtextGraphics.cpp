#include "customtextgraphics.h"
#include "iostream"
#include <QStyleOptionGraphicsItem>

using namespace std;

CustomTextGraphics::~CustomTextGraphics() {}

CustomTextGraphics::CustomTextGraphics(QPointF itemPos, QGraphicsItem *parent)
    : QGraphicsTextItem(parent), itemPos(itemPos), width(0), height(0) {
  this->setFlags(ItemIsFocusable | ItemIsSelectable);
  this->setTextInteractionFlags(Qt::TextEditorInteraction);
  this->setPos(itemPos);
}

QRectF CustomTextGraphics::boundingRect() const {
  return QGraphicsTextItem::boundingRect();
}

void CustomTextGraphics::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget) {
  QStyleOptionGraphicsItem opt(*option);
  opt.state = QStyle::State_Editing;
  parentItem()->update();
  QGraphicsTextItem::paint(painter, &opt, widget);
}

void CustomTextGraphics::focusInEvent(QFocusEvent *event) {
  this->parentItem()->setSelected(true);
  this->parentItem()->update();
  this->update();
  QGraphicsTextItem::focusInEvent(event);
}

void CustomTextGraphics::focusOutEvent(QFocusEvent *event) {
  QGraphicsTextItem::focusOutEvent(event);
}
void CustomTextGraphics::setHeight(int newHeight) {
  height = newHeight;
  this->update();
  this->parentItem()->update();
}

void CustomTextGraphics::setWidth(int newWidth) {
  width = newWidth;
  this->update();
  this->parentItem()->update();
}
