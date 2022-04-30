/*
 * Color By Number/Neighbor
 * 
 * An example showing how to count the number of neighbors.
 * 
 * Each uutside Blink displays a color
 *  
 */

enum gameMode {INIT, MOVE};

gameMode gameState = INIT;

void setup() {
  setValueSentOnAllFaces(0);
}

void loop() {
  if (gameState == INIT) {
    boundaryLoop();
  }
}

void boundaryLoop() {
  Color colors[] = {OFF, RED, BLUE};
  Color color = OFF;

  bool faces[6];
  FOREACH_FACE(f) {
    faces[f] = isValueReceivedOnFaceExpired(f);
  }

  int nbrs = 0;
  FOREACH_FACE(f) {
    if (faces[f]) {
      nbrs++;
    }
  }

  if (nbrs == 6) {
    setColor(OFF);
    gameState = MOVE;
    return;
  }
  if (nbrs == 2 || nbrs == 3) {
    color = MAGENTA;
    gameState = MOVE;
  }
  if (nbrs == 2) {
    byte left;
    if (faces[0] && faces[5]) {
      left = 5;
    } else {
      FOREACH_FACE(f) {
        if (faces[f]) {
          left = f;
        }
      }
    }
    setValueSentOnFace(1, left);
    setValueSentOnFace(2, (left - 1) % 6);
    // debugging
    setColorOnFace(RED, left);
    setColorOnFace(BLUE, (left - 1) % 6);
    gameState = MOVE;
    color = MAGENTA;
  }

  int v = 0;
  if (nbrs == 4) {
    FOREACH_FACE(f) {
      if (faces[f]) {
        v = getLastValueReceivedOnFace(f);
        if (v) {
          //setColorOnFace(GREEN, f);
          setValueSentOnFace(v, (f + 3) % 6);
          //setColorOnFace(ORANGE, (f + 3) % 6);
          color = colors[v];
          gameState = MOVE;
        }
      }
    }
  }
  // display boundary color on all faces with no neighbor
  if (gameState != INIT) {
    FOREACH_FACE(f) {
      if (!faces[f]) {
        setColorOnFace(color, f);
      }
    }
  }
  //setColor(color);
}
