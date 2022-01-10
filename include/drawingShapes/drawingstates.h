#ifndef DRAWINGSTATES_H
#define DRAWINGSTATES_H

namespace CanvasState {
enum State { DRAW, MOVE, SCALE, FRAME };

enum Shapes {
  NONE,
  RECTANGLE,
  ARROW,
  POLYGON,
  ELLIPSE,
  IMAGE,
  TEXT,
  PEN,
  PENCIL,
};
}; // namespace DrawingStates

#endif // DRAWINGSTATES_H
