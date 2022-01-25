#ifndef TEXTITEM_H
#define TEXTITEM_H

#include "baseshapeitem.h"

#include <QObject>
#include <customtextgraphics.h>

class TextItem : public BaseShapeItem, public QObject {

public:
  TextItem(QPointF itemPos, QGraphicsItem *parent = nullptr);
  ~TextItem();

  // QGraphicsItem interface
public:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;

private:
  QString text;
  CustomTextGraphics *customTextGraphics;
};

#endif // TEXTITEM_H
