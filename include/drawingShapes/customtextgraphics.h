#ifndef CUSTOMTEXTGRAPHICS_H
#define CUSTOMTEXTGRAPHICS_H

#include <QGraphicsTextItem>

class CustomTextGraphics : public QGraphicsTextItem {

public:
  CustomTextGraphics(QPointF itemPos, QGraphicsItem *parent = nullptr,
                     QGraphicsScene *mainCanvas = nullptr);
  ~CustomTextGraphics();
  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  void focusOutEvent(QFocusEvent *event) override;

protected:
  void keyPressEvent(QKeyEvent *event) override;

private:
  QPointF itemPos;
  QGraphicsItem *textItemWrapper;
  QGraphicsScene *mainCanvas;
};

#endif // CUSTOMTEXTGRAPHICS_H
