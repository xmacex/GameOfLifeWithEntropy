// Conway's game of life, with a twist of entropy

const int entropyPin = A0;

const int WORLDWIDTH = 5;
const int WORLDHEIGHT = 50;
boolean world[WORLDWIDTH][WORLDHEIGHT];
int generation = 0;
int entropy;

void setup() {
  Serial.begin(9600);
  
  // a blinker
  world[1][10] = true;
  world[2][10] = true;
  world[3][10] = true;
  
  drawWorld();
  Serial.println("===== life ====");
  delay(5000);
}

void loop() {
  int x, y;
  for (x = 0; x < WORLDWIDTH; x++) {
    for (y = 0; y < WORLDHEIGHT; y++) {
      int noNeighbours = countNeighbours(x, y);
      boolean selfAlive = world[x][y];
      entropy = analogRead(entropyPin);
      if (selfAlive && noNeighbours < 2) {
        world[x][y] = false;
      } else if (selfAlive && (noNeighbours == 2 || noNeighbours == 3)) {
        world[x][y] = true;
      } else if (selfAlive && (noNeighbours > 3)) {
        world[x][y] = false;
      } else if (!selfAlive && noNeighbours == 3) {
        world[x][y] = true;
      }
      
      // enter chaos
      if (20 / generation == 0) {
        delay(5); // give entropy a chance
        if (entropy % 100 == 0) {
          world[x][y] = true;
        }
      }
    }
  }
  drawWorld();
  delay(500);
//  Serial.print(" with entropy ");
//  Serial.print(entropy);
  Serial.print("+++++++++++++++++ gen no ");
  Serial.print(generation);
  Serial.print(" ++++++++++++++++++++++");
  Serial.println();
  generation++;
}

int countNeighbours(int x, int y) {
  int xx, yy;
  int count = 0;
  for (xx = x - 1; xx <= x + 1; xx++) {
    for (yy = y - 1; yy <= y + 1; yy++) {
      // Serial.println(x y);
      if(world[xx][yy] == true && (xx != 0 && yy != 0)) {
        count++;
      }
    }
  }
  return count;
}

void drawWorld() {
  int dx, dy;
  for (dx = 0; dx < WORLDWIDTH; dx++) {
      for (dy = 0; dy < WORLDHEIGHT; dy++) {
        if(world[dx][dy] == true) {
          Serial.print("o");
        } else {
          Serial.print(".");
        }
      }
      Serial.println();
    }
}
