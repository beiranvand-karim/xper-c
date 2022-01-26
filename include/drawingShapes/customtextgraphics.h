#ifndef CUSTOMTEXTGRAPHICS_H
#define CUSTOMTEXTGRAPHICS_H

#include <QGraphicsTextItem>

class CustomTextGraphics : public QGraphicsTextItem {

public:
  CustomTextGraphics(QPointF itemPos, QGraphicsItem *parent = nullptr);
  ~CustomTextGraphics();
  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  void focusInEvent(QFocusEvent *event) override;
  void focusOutEvent(QFocusEvent *event) override;

  void setHeight(int newHeight);
  void setWidth(int newWidth);

private:
  QPointF itemPos;
  int width, height;
};

#endif // CUSTOMTEXTGRAPHICS_H
