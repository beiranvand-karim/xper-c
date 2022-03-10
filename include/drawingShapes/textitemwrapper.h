#ifndef TEXTITEM_H
#define TEXTITEM_H

#include "baseshapeitem.h"
#include <QGraphicsScene>
#include <customtextgraphics.h>

class TextItemWrapper : public BaseShapeItem {

public:
  TextItemWrapper(QPointF itemPos, QGraphicsScene *parent = nullptr);
  ~TextItemWrapper();

  // QGraphicsItem interface
public:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;
  // BaseShapeItem interface
public:
  bool validateItemInsertion() override;

private:
  QString text;
  QGraphicsScene *parentScene;
  CustomTextGraphics *customTextGraphics;
};

#endif // TEXTITEM_H
