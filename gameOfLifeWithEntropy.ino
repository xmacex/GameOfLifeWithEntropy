// Conway's game of life, with a twist of entropy

const int entropyPin = A0;

const int WORLDWIDTH = 10;
const int WORLDHEIGHT = 20;
boolean world[WORLDWIDTH][WORLDHEIGHT];
int worldProspects[WORLDWIDTH][WORLDHEIGHT];
int generation = 0;
int entropy;

void setup() {
  Serial.begin(9600);
  
  // a glider
  // .*.
  // ..*
  // ***
  world[2][5] = true;
  world[3][6] = true;
  world[4][4] = true;
  world[4][5] = true;
  world[4][6] = true;

  // a blinker
  // ***
  world[2][10] = true;
  world[2][11] = true;
  world[2][12] = true;
  
  inspectProspects();
  drawWorld();
  Serial.println("===== life ====");
  delay(5000);
}

void loop() {
  inspectProspects();
  applyLife();
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

void inspectProspects() {
  int x, y;
  for (x = 0; x < WORLDWIDTH; x++) {
    for (y = 0; y < WORLDHEIGHT; y++) {
      worldProspects[x][y] = countNeighbours(x, y);
    }
  }
}

void applyLife() {
  int x, y;
  for (x = 0; x < WORLDWIDTH; x++) {
    for(y = 0; y < WORLDHEIGHT; y++) {
      boolean selfAlive = world[x][y];
      int noNeighbours = worldProspects[x][y];
      entropy = analogRead(entropyPin);
      if (selfAlive && noNeighbours < 2) {
        world[x][y] = false;
      } else if (selfAlive && (noNeighbours == 2 || noNeighbours == 3)) {
        world[x][y] = true;
      } else if (selfAlive && noNeighbours > 3) {
        world[x][y] = false;
      } else if (!selfAlive && noNeighbours == 3) {
        world[x][y] = true;
      } else {                     // pointless clause?
        world[x][y] = false;
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
}

int countNeighbours(int x, int y) {
  int xx, yy;
  int count = 0;
  for (xx = x - 1; xx <= x + 1; xx++) {
    for (yy = y - 1; yy <= y + 1; yy++) {
       if (!(xx == x && yy == y)) {
         if(world[xx][yy] == true) {
           count++;
         }
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
          //int c = worldProspects[dx][dy];
          //Serial.print(c);
          Serial.print('*');
        } else {
          //int c = worldProspects[dx][dy];
          //Serial.print(c);
          Serial.print(".");
        }
      }
      Serial.println();
    }
}
