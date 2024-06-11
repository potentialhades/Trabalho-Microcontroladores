#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>

#define LCD_CS A3 // Chip Select
#define LCD_CD A2 // Command/Data
#define LCD_WR A1 // LCD Write
#define LCD_RD A0 // LCD Read
#define LCD_RESET A4

/*____CALIBRAR TFT LCD_____*/
#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_LEFT 155
#define TS_RT   871
#define TS_TOP  944
#define TS_BOT  102

//#define TS_LEFT 129
//#define TS_RT   924
//#define TS_TOP  82
//#define TS_BOT  896

/*______FIM DA CALIBRAÇÃO______*/

// DEFINIÇÃO DE CORES
#define WHITE          0xFFFF
#define YELLOW         0xFFE0
#define RED            0xF800
#define BLUE           0x001F
#define BLACK          0x0000
#define GREEN          0x07E0
#define PURPLE           0x6DABD0

//PRESSÃO DO TOQUE
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//VARIÁVEIS GLOBAIS
int X, Y;
int estado = 1;
char currentInput[7];
char codigo[7];
char quantidade[6];
int BOX = 70;

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void tela_codigo(){
  tft.fillScreen(BLACK);
  intr_codigo();
  teclado();
  }

void tela_quantidade(){
  tft.fillScreen(BLACK);
  intr_quantidade();
  teclado();
}

void setup() {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID); // CÓDIGO DO DRIVER DO SEU DISPLAY
  tft.setRotation(2);
  tft.fillScreen(BLACK);
  //tft.reset();
  tela_codigo();
}

void teclado(){
  tft.fillRect(20, 10, 270, 70, PURPLE); // ÁREA DO DISPLAY
  tft.setCursor (30, 20);
  tft.setTextSize (3);
  tft.setTextColor(WHITE);
  tft.print("0");

  desenharBotao(20, 90, "1", WHITE);
  desenharBotao(120, 90, "2", WHITE);
  desenharBotao(220, 90, "3", WHITE);
  desenharBotao(20, 190, "4", WHITE);
  desenharBotao(120, 190, "5", WHITE);
  desenharBotao(220, 190, "6", WHITE);
  desenharBotao(20, 290, "7", WHITE);
  desenharBotao(120, 290, "8", WHITE);
  desenharBotao(220, 290, "9", WHITE);
  desenharBotao(20, 390, "DEL", RED);
  desenharBotao(120, 390, "0", WHITE);
  desenharBotao(220, 390, "OK", GREEN);

}

void intr_quantidade(){
  tft.setCursor (55, 80);
  tft.setTextSize (5);
  tft.setTextColor(WHITE);
  tft.println("INSIRA");

  tft.setCursor (120, 150);
  tft.setTextSize (5);
  tft.setTextColor(YELLOW);
  tft.println("A");

  tft.setCursor (20, 220);
  tft.setTextSize (5);
  tft.setTextColor(YELLOW);
  tft.println("QUANTIDADE");
  
  tft.setCursor (20, 300);
  tft.setTextSize (5);
  tft.setTextColor(WHITE);
  tft.println("ABERTA P/");
  
  tft.setCursor (20, 380);
  tft.setTextSize (5);
  tft.setTextColor(WHITE);
  tft.println("VAREJO");
  
  delay(3500);
  
  tft.fillScreen(BLACK);
}

void intr_codigo(){
  tft.setCursor (55, 80);
  tft.setTextSize (5);
  tft.setTextColor(WHITE);
  tft.println("INSIRA");

  tft.setCursor (30, 150);
  tft.setTextSize (5);
  tft.setTextColor(YELLOW);
  tft.println("O CODIGO");
  
  tft.setCursor (120, 220);
  tft.setTextSize (5);
  tft.setTextColor(WHITE);
  tft.println("DO");
  
  tft.setCursor (55, 290);
  tft.setTextSize (5);
  tft.setTextColor(WHITE);
  tft.println("PRODUTO");
  
  delay(3500);
  
  tft.fillScreen(BLACK);
}

void desenharBotao(int eixox, int eixoy, char* nome, const int cor){
  tft.fillRect(eixox, eixoy , BOX, BOX, cor);
  tft.setTextColor(BLACK);
  tft.setTextSize (3);
  tft.setCursor(eixox + BOX / 4, eixoy + BOX / 4);
  tft.println(nome);
}

void updateEntrada(char input){
  int len = strlen(currentInput);
  if (len < sizeof(currentInput) - 1){
    currentInput[len] = input;
    currentInput[len + 1] = '\0';
    tft.fillRect(20, 10, 270, 70, PURPLE);
    tft.setCursor (30, 20);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    tft.print(currentInput);
  }
}

void limparEntrada(){
  memset(currentInput, 0, sizeof(currentInput));
  tft.fillRect(20, 10, 270, 70, PURPLE);
  tft.setCursor (30, 20);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("0");
}

TSPoint waitTouch() {
  TSPoint p;
  do {
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  } while ((p.z < MINPRESSURE ) || (p.z > MAXPRESSURE));
  
  p.x = map(p.x, TS_LEFT, TS_RT, 0, 320);
  p.y = map(p.y, TS_BOT, TS_TOP, 0, 480);
  
  return p;
}

void touch(){
  if (Y > 80 && Y < 180){
    if(X > 20 && X < 110){
        //Serial.println("3");
        updateEntrada('3');
    }
    if(X > 120 && X < 210){
        //Serial.println("2");
        updateEntrada('2');
    }
    if(X > 210 && X < 310){
        //Serial.println("1");
        updateEntrada('1');
    } 
  }
  if (Y > 180 && Y < 280){
    if(X > 20 && X < 110){
        //Serial.println("6");
        updateEntrada('6');
    }
    if(X > 120 && X < 210){
        //Serial.println("5");
        updateEntrada('5');
    }
    if(X > 210 && X < 310){
        //Serial.println("4");
        updateEntrada('4');
    }
  }
  if (Y > 280 && Y < 380){
    if(X > 20 && X < 110){
        //Serial.println("9");
        updateEntrada('9');
    }
    if(X > 120 && X < 210){
        //Serial.println("8");
        updateEntrada('8');
    }
    if(X > 210 && X < 310){
        //Serial.println("7");
        updateEntrada('7');
    }
  }
  if (Y > 380 && Y < 480){
    if(X > 20 && X < 110){
      if(estado == 1){
          //Serial.println("OK estado 1");
          strncpy(codigo, currentInput, sizeof(codigo) - 1);
          codigo[sizeof(codigo) - 1] = '\0'; // APAGAR NULO
          //Serial.print("Valor Salvo: ");
          Serial.print(codigo);
          limparEntrada();
          estado = 0;
          tela_quantidade();
        }
      else if(estado != 1){
          //Serial.println("OK estado 2");
          strncpy(quantidade, currentInput, sizeof(quantidade) - 1);
          quantidade[sizeof(quantidade) - 1] = '\0'; // APAGAR NULO
          //Serial.print("Valor Salvo: ");
          Serial.print(quantidade);
          limparEntrada();
          estado = 1;
          tela_codigo();
        }
    }
    if(X > 120 && X < 210){
        //Serial.println("0");
        updateEntrada('0');
    }
    if(X > 210 && X < 310){
        //Serial.println("DEL");
        limparEntrada();
    }
  }
}

void loop() {
  TSPoint p = waitTouch();
  X = p.x; Y = p.y;
  touch();

  delay(300);
}