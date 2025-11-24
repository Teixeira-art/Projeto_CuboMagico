// Motor de passo 28BYJ-48 + ULN2003 na ESP32 DevKit v1
// Controle via Serial: G = girar, P = parar

const int IN1 = 12;
const int IN2 = 14;
const int IN3 = 27;
const int IN4 = 26;

// tempo entre cada meio-passo (menor = mais rápido)
int tempoPasso = 1;

// índice do passo atual
int passoAtual = 0;

// variavel de controle (2 = girando horario, 1 = girando anti-horario, 0 = parado)
int girando = 0;

// Sequência de meio-passo (8 etapas)
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

void giraHorario() {
  passoAtual++;
  if (passoAtual > 7) passoAtual = 0;
  aplicaPasso(passoAtual);
  delay(tempoPasso);
}

void giraAntiHorario(){
   passoAtual = 7;
   if(passoAtual < 0) passoAtual = 7;
   aplicaPasso(passoAtual);
   delay(tempoPasso);
}

void desligaBobinas() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  desligaBobinas();
  Serial.println("Digite 'G' para girar e 'P' para parar.");
}

void loop() {
  // verifica se tem algo digitado no monitor serial
  if (Serial.available() > 0) {
    char comando = Serial.read();

    if (comando == 'H' || comando == 'h') {
      girando = 2;
      Serial.println("Girando motor no sentido horário...");
    }

    if (comando == 'A' || comando == 'a') {
      girando = 1;
      Serial.println("Girando motor no sentido anti-horário...");
    }

    else if (comando == 'P' || comando == 'p') {
      girando = false;
      desligaBobinas();
      Serial.println("Motor parado.");
    }
  }

  // se estiver girando, executa os passos
  if (girando == 2) {
    giraHorario();
  }
  if (girando == 1) {
    giraAntiHorario();
  }
}
