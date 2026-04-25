const int IN1 = 12;
const int IN2 = 14;
const int IN3 = 27;
const int IN4 = 26;

const int IN5 = 18;
const int IN6 = 19;
const int IN7 = 21;
const int IN8 = 22;

int tempoPasso = 3;
int passoAtual = 0;
int passoAtual2 = 0;

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

void aplicaPasso2(int idx) {
  digitalWrite(IN5, sequencia[idx][0]);
  digitalWrite(IN6, sequencia[idx][1]);
  digitalWrite(IN7, sequencia[idx][2]);
  digitalWrite(IN8, sequencia[idx][3]);
}

void desligaBobinas() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, LOW);
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

void giraHorario2() {
  for (int i = 0; i < 1024; i++) {
    passoAtual2++;
    if (passoAtual2 > 7) passoAtual2 = 0;
    aplicaPasso2(passoAtual2);
    delay(tempoPasso);
  }
  desligaBobinas();
}

void giraAntiHorario2() {
  for (int i = 0; i < 1024; i++) {
    passoAtual2--;
    if (passoAtual2 < 0) passoAtual2 = 7;
    aplicaPasso2(passoAtual2);
    delay(tempoPasso);
  }
  desligaBobinas();
}

void giraDuplo2() {
  for (int i = 0; i < 2048; i++) {
    passoAtual2++;
    if (passoAtual2 > 7) passoAtual2 = 0;
    aplicaPasso2(passoAtual2);
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

  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);

  desligaBobinas();

  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();

    if (comando == "H1" || comando == "h1") {
      Serial.println("Motor 1: 90 horario");
      giraHorario();
    }
    else if (comando == "A1" || comando == "a1") {
      Serial.println("Motor 1: 90 anti-horario");
      giraAntiHorario();
    }
    else if (comando == "D1" || comando == "d1") {
      Serial.println("Motor 1: 180 graus");
      giraDuplo();
    }
    else if (comando == "H2" || comando == "h2") {
      Serial.println("Motor 2: 90 horario");
      giraHorario2();
    }
    else if (comando == "A2" || comando == "a2") {
      Serial.println("Motor 2: 90 anti-horario");
      giraAntiHorario2();
    }
    else if (comando == "D2" || comando == "d2") {
      Serial.println("Motor 2: 180 graus");
      giraDuplo2();
    }
    else {
      Serial.println("Comando invalido");
    }
  }
}
