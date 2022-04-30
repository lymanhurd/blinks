bool nbrs[6];
int nbrCount = 0;

enum Stage {START, INIT, REDTURN, BLUETURN, REDWIN, BLUEWIN};
Stage stage = START;

Color colors[] = {OFF, RED, BLUE, GREEN, MAGENTA, CYAN, ORANGE, WHITE};
byte color = 0;

const byte LEFT = 0x1;
const byte RIGHT = 0x2;
const byte TOP = 0x4;
const byte BOTTOM = 0x8;

boolean clicked = false;

bool redsTurn = true;
byte edgeState = 0;

void setup() {
}

void loop() {
  FOREACH_FACE(f) {
    if (didValueOnFaceChange(f)) {
      stage = getStage(getLastValueReceivedOnFace(f));
    }
  }
  if (buttonLongPressed()) {
    stage = INIT;
  }
  switch (stage) {
    case(INIT):
      initLoop();
      break;
    case(REDTURN):
      playLoop(BLUETURN);
      break;
    case(BLUETURN):
      playLoop(REDTURN);
      break;
    case(REDWIN):
    case(BLUEWIN):
      displayWin(stage);
      break;
  }
  setValueSentOnAllFaces(stage);
}

byte getStage(byte value) {
  return value;
}

void initLoop() {
  queryNeighbors();
  setupBoundary();
  clicked = false;
  if (buttonSingleClicked()) {
    displayInternal(GREEN);
    clicked = true;
    stage = REDTURN;
  }
}

void setupBoundary() {
  displayInternal(OFF);
  displayExternal(BLUE);
}

void playLoop(byte nextStage) {
  if (buttonSingleClicked()) {
    displayInternal(GREEN);
    clicked = true;
    stage = nextStage;
  }
  if (buttonDoubleClicked()) {
    if (nextStage == BLUETURN) {
      stage = REDWIN;
    } else {
      stage = BLUEWIN;
    }
  }
}

void displayWin(byte stage) {
  Color color = CYAN;
  if (stage == REDWIN) {
    stage = MAGENTA;
  }
  if (clicked) {
    displayInternal(color);
    clicked = false;
  }
}
/*
void updateDisplay() {
  Color color = OFF;
  if (stage == PLAY) {
    color = WHITE;
  } else if (stage == FINISHED) {
    color = redsTuren ? RED : BLUE;
  }
  switch (nbrCount) {
    case(6):
      setColor(color):
      break;
    case(2):
    case(3):
    case(4):
      FOREACH_FACE(f) {
        if (isValueReceivedOnFaceExpired(f)) {
          setColorOnFace(color, f);
        }
      }
  }
}

void startLoop(){
  queryNeighbors();
  FOREACH_FACE(f) {
    if (didValueOnFaceChange(f)) {
      byte received = getLastValueReceivedOnFace(f);
      if (nbrCount == 4) {
        setValueSentOnFace(received, (f + 3) % 6);
        state = received;
      } else if (nbrCount == 3) {
        setValueSentOnFace(received * 4, (f + 4) % 6);
        setValueSentOnFace(received * 4, (f + 2) % 6);
        state = received * 5;          
      } else if (nbrCount == 2) {
        state = 12;
      }
    }
  }
  stage = REDTURN;
  propagateStage();
}

void startLoop(){
  if (buttonDown()) {
    if (nbrCount == 2) {
      state = 3;
      propagateState();
    }
  }
  setColor(stateColor(state));
}

Color stateColor(byte state) {
  switch(state) {
    case(1):
      return RED;
    case(2):
      return BLUE; 
    case(4):
      return GREEN;
    case(8):
      return CYAN;
    case(3):
      return MAGENTA;
    case(5):
      return ORANGE;
    case(10):
      return WHITE;
    case(12):
      return RED;
    default:
      return OFF;    
  }
}

void propagateStage() {
  FOREACH_FACE(f) {
    setValueSentOnAllFaces(stage);
  }
}
*/

void queryNeighbors() {
  nbrCount = 0;
  FOREACH_FACE(f) {
    nbrs[f] = !isValueReceivedOnFaceExpired(f);
    if (nbrs[f]) {
      nbrCount++;
    }
  }
}

void displayExternal(Color c) {
  FOREACH_FACE(f) {
    if (!nbrs[f]) {
      setColorOnFace(c, f);  
    }
  }
}

void displayInternal(Color c) {
  FOREACH_FACE(f) {
    if (nbrs[f]) {
      setColorOnFace(c, f);  
    }
  }
}
