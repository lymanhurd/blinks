Color colors[6] = {RED, GREEN, BLUE, WHITE, YELLOW, ORANGE};

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  FOREACH_FACE(f) {
    setColorOnFace(colors[f], f);
  }
}
