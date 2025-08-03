//Biblioteca do Sensor DHT11 

#include "dht.h"
#include <LiquidCrystal.h>

//Mapeamento de Hardware
#define sensor_dht_pino 6
#define sensor_solo_pino A0
#define sensor_chuva_pino A1
#define ldr_pino A2
#define nivel_alto 7
#define nivel_baixo 8
#define bomba 9
#define valvula 10
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Configurações iniciais 
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(bomba, OUTPUT);
  pinMode(nivel_alto, INPUT);
  pinMode(nivel_baixo, INPUT);
}

void loop() {
  lcd_display();
  lerTemperatura();
  float leitura = humidade_solo(); 
  chuva ();
  luminosidade ();
  nivel();
  if(leitura < 1000){
    digitalWrite(bomba, 1);
  }else{
    digitalWrite(bomba, 0);
  }
  delay(1000);
  Serial.print("\n");
}

void lerTemperatura (){
  int temperatura = 0;
  int umidade = 0;
  //Declaração de Objetos
  dht obj_dht;
  obj_dht.read11(sensor_dht_pino);
  temperatura = obj_dht.temperature;
  umidade = obj_dht.humidity;

  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Temperatrua C");
  lcd.setCursor(0,1);
  lcd.print(temperatura);
  delay(5000);

  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Humidade");
  lcd.setCursor(0,1);
  lcd.print(umidade);
  delay(5000);
  
  Serial.print("Temperatura :");
  Serial.print(" ");
  Serial.print(temperatura);
  Serial.print("C");
  Serial.print(" ");
  Serial.print("Umidade:");
  Serial.print(" ");
  Serial.print(umidade);
  Serial.print("% \n");
}

float humidade_solo(){
  float leitura = analogRead(sensor_solo_pino);
  Serial.print("Humidade do Solo: ");
  Serial.print("  ");
  Serial.print(leitura); 
  Serial.print("\n");
  
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Solo");
  lcd.setCursor(0,1);
  lcd.print(leitura);
  delay(5000);
  return leitura;
}

void chuva (){
  float chuva = analogRead(sensor_chuva_pino);
  Serial.print("Chuva:");
  Serial.print(chuva); 
  Serial.print("  ");
  Serial.print("\n");
}

void luminosidade (){
  float luz = analogRead(ldr_pino);

  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Solo");
  lcd.setCursor(0,1);
  lcd.print(luz);
  delay(5000);
  
  
  Serial.print("Luminosidade:");
  Serial.print("  ");
  Serial.print(luz); 
  Serial.print("\n");
}

void nivel (){
  int nivel = digitalRead(nivel_alto);
  if(nivel)
    Serial.print("Alto \n");
  else
    Serial.print("Baixo \n");
}

void lcd_display (){
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(3, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Projeto CNPQ");
  lcd.setCursor(3, 1);
  lcd.print("");
  delay(5000);

  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Meninas na");
  lcd.setCursor(0,1);
  lcd.print("Engenharia");
  delay(5000);
  
}
