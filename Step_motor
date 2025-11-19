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

// flag de controle (1 = girando, 0 = parado)
bool girando = false;

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

    if (comando == 'G' || comando == 'g') {
      girando = true;
      Serial.println("Girando motor...");
    }
    else if (comando == 'P' || comando == 'p') {
      girando = false;
      desligaBobinas();
      Serial.println("Motor parado.");
    }
  }

  // se estiver girando, executa os passos
  if (girando) {
    giraHorario();
  }
}
