#include "customtextgraphics.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>

CustomTextGraphics::~CustomTextGraphics() {}

CustomTextGraphics::CustomTextGraphics(QPointF itemPos, QGraphicsItem *parent,
                                       QGraphicsScene *mainCanvas)
    : QGraphicsTextItem(parent), itemPos(itemPos), textItemWrapper(parent),
      mainCanvas(mainCanvas) {
  this->setParentItem(parent);
  this->setFlags(ItemIsFocusable | ItemIsSelectable);
  this->setTextInteractionFlags(Qt::TextEditorInteraction);
  this->setCursor(QCursor(Qt::IBeamCursor));
  this->setPos(itemPos);
  this->setFocus();
}

QRectF CustomTextGraphics::boundingRect() const {
  return QGraphicsTextItem::boundingRect();
}

void CustomTextGraphics::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget) {
  QStyleOptionGraphicsItem opt(*option);
  opt.state = QStyle::State_Editing;
  QGraphicsTextItem::paint(painter, &opt, widget);
}

void CustomTextGraphics::focusOutEvent(QFocusEvent *event) {
  QGraphicsTextItem::focusOutEvent(event);
}

void CustomTextGraphics::keyPressEvent(QKeyEvent *event) {
  QGraphicsTextItem::keyPressEvent(event);
  this->textItemWrapper->update();
  this->mainCanvas->update();
}
