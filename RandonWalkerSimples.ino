// Pinos dos LEDs
int leds[] = {4,5,6,7,8,9,10,11,12};
int N = 9;

// Posição atual do random walker
int pos = 4;  // começa no meio

// NOVO: contador de passos
int passos = 0;
int maxPassos = 100;

void setup() {
  // Configura os pinos como saída
  for (int i = 0; i < N; i++) {
    pinMode(leds[i], OUTPUT);
  }

  // Inicializa o gerador de números aleatórios
  randomSeed(analogRead(A0));

  // NOVO: inicia comunicação serial
  Serial.begin(9600);
}

void loop() {
  if (passos < maxPassos) {   // NOVO: só executa até 100 passos
    // Apaga todos os LEDs
    for (int i = 0; i < N; i++) {
      digitalWrite(leds[i], LOW);
    }

    // Acende o LED da posição atual
    digitalWrite(leds[pos], HIGH);

    // NOVO: envia posição atual pela serial
    Serial.println(pos);

    delay(500); // tempo entre passos

    // Sorteia o passo: 0 = esquerda, 1 = direita
    int passo = random(0, 2);

    if (passo == 0) {
      // esquerda
      if (pos > 0) {
        pos--;
      }
    } else {
      // direita
      if (pos < N - 1) {
        pos++;
      }
    }

    // NOVO: incrementa contador
    passos++;
  } else {
    // NOVO: depois de 100 passos, trava aqui
    while (true) {
      // opcional: piscar todos os LEDs para indicar fim
      for (int i = 0; i < N; i++) {
        digitalWrite(leds[i], HIGH);
      }
      delay(300);
      for (int i = 0; i < N; i++) {
        digitalWrite(leds[i], LOW);
      }
      delay(300);
    }
  }
}
