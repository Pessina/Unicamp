#include "Arduino.h"
#include "Keyboard.h" //Biblioteca pra usar o arduino como teclado

int sequencia[32] = {};
int botoes[4] = {6, 7, 8, 9};
int leds[4] = {2, 3, 4, 5};
int ton = 15;
int tons[4] = {262, 294, 330, 349};
int rodada = 0;
int passo = 0;
bool game_over = false;
bool game_start = false;

void proximaRodada() {
  int sorteio = random(4);
  sequencia[rodada] = sorteio;
  rodada = rodada + 1;
}

void reproduzirSequencia() {
  for (int i = 0; i < rodada; i++) {
    tone(ton, tons[sequencia[i]]);
    digitalWrite(leds[sequencia[i]], HIGH);
    delay(500);
    noTone(ton);
    digitalWrite(leds[sequencia[i]], LOW);
    delay(100);
  }
}

void aguardarJogador() {
  int botao_pressionado = 0;
  for (int i = 0; i < rodada; i++) {
    bool jogada_efetuada = false;
    while (!jogada_efetuada) {
      for (int i = 0; i <= 3; i++) {
        if (digitalRead(botoes[i]) == HIGH) {
          botao_pressionado = i;
          tone(ton, tons[i]);
          digitalWrite(leds[i], HIGH);
          delay(300);
          digitalWrite(leds[i], LOW);
          noTone(ton);
          jogada_efetuada = true;
        }
      }
    }
    //verificar a jogada
    if (sequencia[passo] != botao_pressionado) {
      //led e buzzer indicam que perdeu
      for (int i = 0; i <= 3; i++) {
        tone (ton, 70);
        digitalWrite(leds[i], HIGH);
        delay(100);
        digitalWrite(leds[i], LOW);
        noTone(ton);
      }
      game_over = true;
      break;
    }
    passo = passo + 1;
  }
  passo = 0;
}


void setup() {
  // Leds
  pinMode(leds[0], OUTPUT);
  pinMode(leds[1], OUTPUT);
  pinMode(leds[2], OUTPUT);
  pinMode(leds[3], OUTPUT);
  // Buzzer
  pinMode(ton, OUTPUT);
  // Botões
  pinMode(botoes[0], INPUT);
  pinMode(botoes[1], INPUT);
  pinMode(botoes[2], INPUT);
  pinMode(botoes[3], INPUT);
  Keyboard.begin();
}

void loop() {

  if (game_start == false) {
    digitalWrite(leds[3], HIGH);
    if (digitalRead(botoes[3]) == HIGH) {
      digitalWrite(leds[3], LOW);
      game_start = true;
      delay(1000);
    }
  } else {
    // Iniciou o game
    if (rodada == 0) {
      Keyboard.print("s");
    }

    proximaRodada();
    reproduzirSequencia();
    aguardarJogador();
    // restart game
    if (game_over == true) {
      sequencia[32] = {};
      rodada = 0;
      passo = 0;
      game_over = false;
      game_start = false;
      Keyboard.print("l");
    } else {
      Keyboard.print("w");
    }
    delay(1000);
  }
}
