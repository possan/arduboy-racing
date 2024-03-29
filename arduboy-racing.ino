#include "global.h"
#include "game.h"
#include "titleimages.h"

Arduboy2 arduboy;
Arduboy2 *_arduboy = &arduboy;

GAME game;

void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();

  game_init(&game);

  int blink = 0;
  int exiting = false;
  while (!exiting) {
    arduboy.clear();
    arduboy.drawBitmap(0, 0, __title, 128, 64, WHITE);
    // arduboy.setCursor(0,0);
    if (blink) {
      // arduboy.print("Press A or B...");
      arduboy.drawBitmap(0, 40, __startblack, 128, 16, BLACK);
      arduboy.drawBitmap(0, 40, __startwhite, 128, 16, WHITE);
    }
    arduboy.display();
    delay(500);

    blink = !blink;

    if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
      exiting = true;
    }
  }
}

void loop()
{
  // pause render until it's time for the next frame
  if (!arduboy.nextFrame()) {
    return;
  }

  arduboy.clear();
  game_render(&game);
  arduboy.display();
  game_move(&game);

  /*
  //Title screen loop switches from title screen
  //and high scores until FIRE is pressed
  while (!start)
  {
    start = titleScreen();
    if (!start)
    {
      start = displayHighScores(EE_FILE);
    }
  }

  //Initial level draw
  if (!initialDraw)
  {
    //Clears the screen
    arduboy.clear();
    //Selects Font
    //Draws the new level
    level = 1;
    newLevel();
    score = 0;
    initialDraw=true;
  }

  if (lives>0)
  {
    drawPaddle();

    //Pause game if FIRE pressed
    pad = arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON);

    if(pad == true && oldpad == false && released)
    {
      oldpad2 = false; //Forces pad loop 2 to run once
      pause();
    }

    oldpad = pad;
    drawBall();

    if(brickCount == ROWS * COLUMNS)
    {
      level++;
      newLevel();
    }
  }
  else
  {
    drawGameOver();
    if (score > 0)
    {
      enterHighScore(EE_FILE);
    }

    arduboy.clear();
    initialDraw=false;
    start=false;
    lives=3;
    newLevel();
  }

  */
}

// void movePaddle()
// {
//   //Move right
//   if(xPaddle < WIDTH - 12)
//   {
//     if (arduboy.pressed(RIGHT_BUTTON))
//     {
//       xPaddle+=2;
//     }
//   }

//   //Move left
//   if(xPaddle > 0)
//   {
//     if (arduboy.pressed(LEFT_BUTTON))
//     {
//       xPaddle-=2;
//     }
//   }
// }

// void moveBall()
// {
//   tick++;
//   if(released)
//   {
//     //Move ball
//     if (abs(dx)==2) {
//       xb += dx/2;
//       // 2x speed is really 1.5 speed
//       if (tick%2==0)
//         xb += dx/2;
//     } else {
//       xb += dx;
//     }
//     yb=yb + dy;

//     //Set bounds
//     leftBall = xb;
//     rightBall = xb + 2;
//     topBall = yb;
//     bottomBall = yb + 2;

//     //Bounce off top edge
//     if (yb <= 0)
//     {
//       yb = 2;
//       dy = -dy;
//       playTone(523, 250);
//     }

//     //Lose a life if bottom edge hit
//     if (yb >= 64)
//     {
//       arduboy.drawRect(xPaddle, 63, 11, 1, 0);
//       xPaddle = 54;
//       yb=60;
//       released = false;
//       lives--;
//       playTone(175, 250);
//       if (random(0, 2) == 0)
//       {
//         dx = 1;
//       }
//       else
//       {
//         dx = -1;
//       }
//     }

//     //Bounce off left side
//     if (xb <= 0)
//     {
//       xb = 2;
//       dx = -dx;
//       playTone(523, 250);
//     }

//     //Bounce off right side
//     if (xb >= WIDTH - 2)
//     {
//       xb = WIDTH - 4;
//       dx = -dx;
//       playTone(523, 250);
//     }

//     //Bounce off paddle
//     if (xb+1>=xPaddle && xb<=xPaddle+12 && yb+2>=63 && yb<=64)
//     {
//       dy = -dy;
//       dx = ((xb-(xPaddle+6))/3); //Applies spin on the ball
//       // prevent straight bounce
//       if (dx == 0) {
//         dx = (random(0,2) == 1) ? 1 : -1;
//       }
//       playTone(200, 250);
//     }

//     //Bounce off Bricks
//     for (byte row = 0; row < ROWS; row++)
//     {
//       for (byte column = 0; column < COLUMNS; column++)
//       {
//         if (!isHit[row][column])
//         {
//           //Sets Brick bounds
//           leftBrick = 10 * column;
//           rightBrick = 10 * column + 10;
//           topBrick = 6 * row + 1;
//           bottomBrick = 6 * row + 7;

//           //If A collison has occured
//           if (topBall <= bottomBrick && bottomBall >= topBrick &&
//               leftBall <= rightBrick && rightBall >= leftBrick)
//           {
//             Score();
//             brickCount++;
//             isHit[row][column] = true;
//             arduboy.drawRect(10*column, 2+6*row, 8, 4, 0);

//             //Vertical collision
//             if (bottomBall > bottomBrick || topBall < topBrick)
//             {
//               //Only bounce once each ball move
//               if(!bounced)
//               {
//                 dy =- dy;
//                 yb += dy;
//                 bounced = true;
//                 playTone(261, 250);
//               }
//             }

//             //Hoizontal collision
//             if (leftBall < leftBrick || rightBall > rightBrick)
//             {
//               //Only bounce once brick each ball move
//               if(!bounced)
//               {
//                 dx =- dx;
//                 xb += dx;
//                 bounced = true;
//                 playTone(261, 250);
//               }
//             }
//           }
//         }
//       }
//     }
//     //Reset Bounce
//     bounced = false;
//   }
//   else
//   {
//     //Ball follows paddle
//     xb=xPaddle + 5;

//     //Release ball if FIRE pressed
//     pad3 = arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON);
//     if (pad3 == true && oldpad3 == false)
//     {
//       released = true;

//       //Apply random direction to ball on release
//       if (random(0, 2) == 0)
//       {
//         dx = 1;
//       }
//       else
//       {
//         dx = -1;
//       }
//       //Makes sure the ball heads upwards
//       dy = -1;
//     }
//     oldpad3 = pad3;
//   }
// }

// void drawBall()
// {
//   // arduboy.setCursor(0,0);
//   // arduboy.print(arduboy.cpuLoad());
//   // arduboy.print("  ");
//   arduboy.drawPixel(xb,   yb,   0);
//   arduboy.drawPixel(xb+1, yb,   0);
//   arduboy.drawPixel(xb,   yb+1, 0);
//   arduboy.drawPixel(xb+1, yb+1, 0);

//   moveBall();

//   arduboy.drawPixel(xb,   yb,   1);
//   arduboy.drawPixel(xb+1, yb,   1);
//   arduboy.drawPixel(xb,   yb+1, 1);
//   arduboy.drawPixel(xb+1, yb+1, 1);
// }

// void drawPaddle()
// {
//   arduboy.drawRect(xPaddle, 63, 11, 1, 0);
//   movePaddle();
//   arduboy.drawRect(xPaddle, 63, 11, 1, 1);
// }

// void drawGameOver()
// {
//   arduboy.drawPixel(xb,   yb,   0);
//   arduboy.drawPixel(xb+1, yb,   0);
//   arduboy.drawPixel(xb,   yb+1, 0);
//   arduboy.drawPixel(xb+1, yb+1, 0);
//   arduboy.setCursor(37, 42);
//   arduboy.print("Game Over");
//   arduboy.setCursor(31, 56);
//   arduboy.print("Score: ");
//   arduboy.print(score);
//   arduboy.display();
//   delay(4000);
// }

// void pause()
// {
//   paused = true;
//   //Draw pause to the screen
//   arduboy.setCursor(52, 45);
//   arduboy.print("PAUSE");
//   arduboy.display();
//   while (paused)
//   {
//     delay(150);
//     //Unpause if FIRE is pressed
//     pad2 = arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON);
//     if (pad2 == true && oldpad2 == false && released)
//     {
//         arduboy.fillRect(52, 45, 30, 11, 0);

//         paused=false;
//     }
//     oldpad2 = pad2;
//   }
// }

// void Score()
// {
//   score += (level*10);
// }

// void newLevel(){
//   //Undraw paddle
//   arduboy.drawRect(xPaddle, 63, 11, 1, 0);

//   //Undraw ball
//   arduboy.drawPixel(xb,   yb,   0);
//   arduboy.drawPixel(xb+1, yb,   0);
//   arduboy.drawPixel(xb,   yb+1, 0);
//   arduboy.drawPixel(xb+1, yb+1, 0);

//   //Alter various variables to reset the game
//   xPaddle = 54;
//   yb = 60;
//   brickCount = 0;
//   released = false;

//   //Draws new bricks and resets their values
//   for (byte row = 0; row < 4; row++) {
//     for (byte column = 0; column < 13; column++)
//     {
//       isHit[row][column] = false;
//       arduboy.drawRect(10*column, 2+6*row, 8, 4, 1);
//     }
//   }

//   arduboy.display();
// }

// //Used to delay images while reading button input
// boolean pollFireButton(int n)
// {
//   for(int i = 0; i < n; i++)
//   {
//     delay(15);
//     pad = arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON);
//     if(pad == true && oldpad == false)
//     {
//       oldpad3 = true; //Forces pad loop 3 to run once
//       return true;
//     }
//     oldpad = pad;
//   }
//   return false;
// }

// //Function by nootropic design to display highscores
// boolean displayHighScores(byte file)
// {
//   byte y = 8;
//   byte x = 24;
//   // Each block of EEPROM has 7 high scores, and each high score entry
//   // is 5 bytes long:  3 bytes for initials and two bytes for score.
//   int address = file * 7 * 5 + EEPROM_STORAGE_SPACE_START;
//   byte hi, lo;
//   arduboy.clear();
//   arduboy.setCursor(32, 0);
//   arduboy.print("HIGH SCORES");
//   arduboy.display();

//   for(int i = 0; i < 7; i++)
//   {
//     sprintf(text_buffer, "%2d", i+1);
//     arduboy.setCursor(x,y+(i*8));
//     arduboy.print(text_buffer);
//     arduboy.display();
//     hi = EEPROM.read(address + (5*i));
//     lo = EEPROM.read(address + (5*i) + 1);

//     if ((hi == 0xFF) && (lo == 0xFF))
//     {
//       score = 0;
//     }
//     else
//     {
//       score = (hi << 8) | lo;
//     }

//     initials[0] = (char)EEPROM.read(address + (5*i) + 2);
//     initials[1] = (char)EEPROM.read(address + (5*i) + 3);
//     initials[2] = (char)EEPROM.read(address + (5*i) + 4);

//     if (score > 0)
//     {
//       sprintf(text_buffer, "%c%c%c %u", initials[0], initials[1], initials[2], score);
//       arduboy.setCursor(x + 24, y + (i*8));
//       arduboy.print(text_buffer);
//       arduboy.display();
//     }
//   }
//   if (pollFireButton(300))
//   {
//     return true;
//   }
//   return false;
//   arduboy.display();
// }

// boolean titleScreen()
// {
//   //Clears the screen
//   arduboy.clear();
//   arduboy.setCursor(16,22);
//   arduboy.setTextSize(2);
//   arduboy.print("BREAKOUT");
//   arduboy.setTextSize(1);
//   arduboy.display();
//   if (pollFireButton(25))
//   {
//     return true;
//   }

//   //Flash "Press FIRE" 5 times
//   for(byte i = 0; i < 5; i++)
//   {
//     //Draws "Press FIRE"
//     arduboy.setCursor(31, 53);
//     arduboy.print("PRESS FIRE!");
//     arduboy.display();

//     if (pollFireButton(50))
//     {
//       return true;
//     }

//     //Removes "Press FIRE"
//     arduboy.setCursor(31, 53);
//     arduboy.print("           ");
//     arduboy.display();

//     if (pollFireButton(25))
//     {
//       return true;
//     }
//   }

//   return false;
// }

// //Function by nootropic design to add high scores
// void enterInitials()
// {
//   byte index = 0;

//   arduboy.clear();

//   initials[0] = ' ';
//   initials[1] = ' ';
//   initials[2] = ' ';

//   while (true)
//   {
//     arduboy.display();
//     arduboy.clear();

//     arduboy.setCursor(16,0);
//     arduboy.print("HIGH SCORE");
//     sprintf(text_buffer, "%u", score);
//     arduboy.setCursor(88, 0);
//     arduboy.print(text_buffer);
//     arduboy.setCursor(56, 20);
//     arduboy.print(initials[0]);
//     arduboy.setCursor(64, 20);
//     arduboy.print(initials[1]);
//     arduboy.setCursor(72, 20);
//     arduboy.print(initials[2]);
//     for(byte i = 0; i < 3; i++)
//     {
//       arduboy.drawLine(56 + (i*8), 27, 56 + (i*8) + 6, 27, 1);
//     }
//     arduboy.drawLine(56, 28, 88, 28, 0);
//     arduboy.drawLine(56 + (index*8), 28, 56 + (index*8) + 6, 28, 1);
//     delay(150);

//     if (arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(B_BUTTON))
//     {
//       if (index > 0)
//       {
//         index--;
//         playTone(1046, 250);
//       }
//     }

//     if (arduboy.pressed(RIGHT_BUTTON))
//     {
//       if (index < 2)
//       {
//         index++;
//         playTone(1046, 250);
//       }
//     }

//     if (arduboy.pressed(DOWN_BUTTON))
//     {
//       initials[index]++;
//       playTone(523, 250);
//       // A-Z 0-9 :-? !-/ ' '
//       if (initials[index] == '0')
//       {
//         initials[index] = ' ';
//       }
//       if (initials[index] == '!')
//       {
//         initials[index] = 'A';
//       }
//       if (initials[index] == '[')
//       {
//         initials[index] = '0';
//       }
//       if (initials[index] == '@')
//       {
//         initials[index] = '!';
//       }
//     }

//     if (arduboy.pressed(UP_BUTTON))
//     {
//       initials[index]--;
//       playTone(523, 250);
//       if (initials[index] == ' ') {
//         initials[index] = '?';
//       }
//       if (initials[index] == '/') {
//         initials[index] = 'Z';
//       }
//       if (initials[index] == 31) {
//         initials[index] = '/';
//       }
//       if (initials[index] == '@') {
//         initials[index] = ' ';
//       }
//     }

//     if (arduboy.pressed(A_BUTTON))
//     {
//       if (index < 2)
//       {
//         index++;
//         playTone(1046, 250);
//       } else {
//         playTone(1046, 250);
//         return;
//       }
//     }
//   }

// }

// void enterHighScore(byte file)
// {
//   // Each block of EEPROM has 7 high scores, and each high score entry
//   // is 5 bytes long:  3 bytes for initials and two bytes for score.
//   int address = file * 7 * 5 + EEPROM_STORAGE_SPACE_START;
//   byte hi, lo;
//   char tmpInitials[3];
//   unsigned int tmpScore = 0;

//   // High score processing
//   for(byte i = 0; i < 7; i++)
//   {
//     hi = EEPROM.read(address + (5*i));
//     lo = EEPROM.read(address + (5*i) + 1);
//     if ((hi == 0xFF) && (lo == 0xFF))
//     {
//       // The values are uninitialized, so treat this entry
//       // as a score of 0.
//       tmpScore = 0;
//     } else
//     {
//       tmpScore = (hi << 8) | lo;
//     }
//     if (score > tmpScore)
//     {
//       enterInitials();
//       for(byte j = i; j < 7; j++)
//       {
//         hi = EEPROM.read(address + (5*j));
//         lo = EEPROM.read(address + (5*j) + 1);

//         if ((hi == 0xFF) && (lo == 0xFF))
//         {
//         tmpScore = 0;
//         }
//         else
//         {
//           tmpScore = (hi << 8) | lo;
//         }

//         tmpInitials[0] = (char)EEPROM.read(address + (5*j) + 2);
//         tmpInitials[1] = (char)EEPROM.read(address + (5*j) + 3);
//         tmpInitials[2] = (char)EEPROM.read(address + (5*j) + 4);

//         // write score and initials to current slot
//         EEPROM.update(address + (5*j), ((score >> 8) & 0xFF));
//         EEPROM.update(address + (5*j) + 1, (score & 0xFF));
//         EEPROM.update(address + (5*j) + 2, initials[0]);
//         EEPROM.update(address + (5*j) + 3, initials[1]);
//         EEPROM.update(address + (5*j) + 4, initials[2]);

//         // tmpScore and tmpInitials now hold what we want to
//         //write in the next slot.
//         score = tmpScore;
//         initials[0] = tmpInitials[0];
//         initials[1] = tmpInitials[1];
//         initials[2] = tmpInitials[2];
//       }

//       score = 0;
//       initials[0] = ' ';
//       initials[1] = ' ';
//       initials[2] = ' ';

//       return;
//     }
//   }
// }

// // Wrap the Arduino tone() function so that the pin doesn't have to be
// // specified each time. Also, don't play if audio is set to off.
// void playTone(unsigned int frequency, unsigned long duration)
// {
//   if (arduboy.audio.enabled() == true)
//   {
//     tone(PIN_SPEAKER_1, frequency, duration);
//   }
// }