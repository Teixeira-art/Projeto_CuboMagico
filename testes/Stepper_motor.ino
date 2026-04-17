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
  Serial.println("Digite 'H' para 90° horario, 'A' para 90° anti-horario, 'D' para 180°");
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();

    if (comando == 'H' || comando == 'h') {
      giraHorario();
      Serial.println("Girando 90 graus no sentido horario...");
    }
    else if (comando == 'A' || comando == 'a') {
      giraAntiHorario();
      Serial.println("Girando 90 graus no sentido anti-horario...");
    }
    else if (comando == 'D' || comando == 'd') {
      giraDuplo();
      Serial.println("Girando 180 graus...");
    }
  }

}
