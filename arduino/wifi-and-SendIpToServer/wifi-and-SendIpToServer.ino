#include "WiFiEspAT.h"

// Emulate Serial1 on pins 7/6 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7);  // RX, TX
#endif

// Informações do Wi-Fi
char ssid[] = "Seixas";      // seu SSID de rede
char pwd[] = "@ianaseixas";  // sua senha de rede

// Informações do servidor
const char* server = "192.168.0.238";  // Substitua com o IP correto do servidor
WiFiClient client;  // Variável para a conexão HTTP com o servidor

void setup() {
  Serial.begin(115200);   // Comunicação com o Serial Monitor
  Serial1.begin(115200);  // Comunicação com o ESP-01 (ajustado para 115200)

  // Aguarda alguns segundos para estabilizar a comunicação com o ESP
  delay(2000);
  Serial.println("Iniciando comunicação com ESP-01");

  // Inicializa o ESP-01 com WiFiEspAT
  WiFi.init(&Serial1);

  // Verifica se o módulo ESP-01 foi detectado
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("ESP-01 não foi detectado. Verifique as conexões e o baud rate.");
    while (true) ;  // Pausa infinita para diagnóstico
  }

  IPAddress serverIP(192, 168, 222, 140);  // IP do servidor (pode ser o do computador)
  Serial.println("Pingando o servidor...");
  WiFi.ping(serverIP);

  // Conectando ao Wi-Fi uma vez
  Serial.println("Tentando conectar ao Wi-Fi...");
  if (WiFi.begin(ssid, pwd) == WL_CONNECTED) {
    Serial.println("Conectado com sucesso ao Wi-Fi!");

    IPAddress ip = WiFi.localIP();

    // Tenta obter o IP até que seja válido
    int attempt = 0;
    while (ip[0] == 0 && attempt < 10) {  // Tenta até 10 vezes
      Serial.println("Falha ao obter IP. Tentando novamente...");
      delay(1000);  // Aguarda 1 segundo antes de tentar novamente
      ip = WiFi.localIP();
      attempt++;
    }

    if (ip[0] != 0) {
      Serial.print("Endereço IP: ");
      Serial.println(ip);

      // Envia o IP para o servidor
      sendIPToServer(ip);  // Envia o IP ao servidor via HTTP
    } else {
      Serial.println("Falha ao obter IP após várias tentativas.");
    }

  } else {
    Serial.println("Falha ao conectar. Verifique SSID e senha.");
  }
}

void sendIPToServer(IPAddress ip) {
  Serial.println("Tentando conectar ao servidor...");
  if (client.connect(server, 8000)) {
    Serial.println("Conectado ao servidor.");

    // Construindo e enviando a requisição
    String ipStr = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    Serial.print("Enviando IP: ");
    Serial.println(ipStr);

    // Enviando cada linha com delays
    client.print("GET /register_ip HTTP/1.1\r\n");
    delay(10);
    client.print("Host: ");
    client.print(server);
    client.print("\r\n");
    delay(10);
    client.print("Connection: close\r\n");
    delay(10);
    client.print("X-ESP-IP: ");
    client.print(ipStr);
    client.print("\r\n\r\n");  // Finaliza com duas quebras de linha
    delay(10);

    // Lê a resposta
    String response = "";
    while (client.connected() || client.available()) {
      if (client.available()) {
        char c = client.read();
        response += c;
      }
    }
    Serial.println("Resposta do servidor:");
    Serial.println(response);  // Exibe a resposta do servidor no monitor

    // Verifica resposta
    if (response.indexOf("200 OK") != -1) {
      Serial.println("IP enviado com sucesso.");
    } else {
      Serial.println("Erro ao enviar IP. Tentando novamente...");
    }

    client.stop();  // Fecha a conexão após a requisição
  } else {
    Serial.println("Falha ao conectar ao servidor.");
  }
}


void loop() {
  // O loop pode ficar vazio ou ser usado para outras funções, já que a conexão Wi-Fi
  // já foi estabelecida no setup e não precisa ser reconectada.
  // Você pode adicionar outras funcionalidades aqui, se necessário.
}
