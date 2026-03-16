// Motor de passo 28BYJ-48 + ULN2003 na ESP32 DevKit v1
// Controle via Serial: H = 90 horario, A = 90 anti-horario, D = 180, P = parar

const int IN1 = 12;
const int IN2 = 14;
const int IN3 = 27;
const int IN4 = 26;

int tempoPasso = 1;
int passoAtual = 0;
int girando = 0;

int sequencia[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

void aplicaPasso(int idx) {
  digitalWrite(IN1, sequencia[idx][0]);
  digitalWrite(IN2, sequencia[idx][1]);
  digitalWrite(IN3, sequencia[idx][2]);
  digitalWrite(IN4, sequencia[idx][3]);
}

void desligaBobinas() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void giraHorario() {
  for (int i = 0; i < 1024; i++) {
    passoAtual++;
    if (passoAtual > 7) passoAtual = 0;
    aplicaPasso(passoAtual);
    delay(tempoPasso);
  }
  desligaBobinas();
}

void giraAntiHorario() {
  for (int i = 0; i < 1024; i++) {
    passoAtual--;
    if (passoAtual < 0) passoAtual = 7;
    aplicaPasso(passoAtual);
    delay(tempoPasso);
  }
  desligaBobinas();
}

void giraDuplo() {
  for (int i = 0; i < 2048; i++) {
    passoAtual++;
    if (passoAtual > 7) passoAtual = 0;
    aplicaPasso(passoAtual);
    delay(tempoPasso);
  }
  desligaBobinas();
}

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  desligaBobinas();
  Serial.println("Digite 'H' para 90 horario, 'A' para 90 anti-horario, 'D' para 180 e 'P' para parar.");
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();

    if (comando == 'H' || comando == 'h') {
      girando = 3;
      Serial.println("Girando 90 graus no sentido horario...");
    }
    else if (comando == 'A' || comando == 'a') {
      girando = 2;
      Serial.println("Girando 90 graus no sentido anti-horario...");
    }
    else if (comando == 'D' || comando == 'd') {
      girando = 1;
      Serial.println("Girando 180 graus...");
    }
    else if (comando == 'P' || comando == 'p') {
      girando = 0;
      desligaBobinas();
      Serial.println("Motor parado.");
    }
  }

  if (girando == 3) {
    giraHorario();
    girando = 0;
  }
  else if (girando == 2) {
    giraAntiHorario();
    girando = 0;
  }
  else if (girando == 1) {
    giraDuplo();
    girando = 0;
  }
}
