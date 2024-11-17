# Miautomatic

Este projeto utiliza um módulo ESP-01 para se conectar a uma rede Wi-Fi e enviar seu endereço IP a um servidor Node.js rodando com Express. O objetivo é registrar o IP do ESP-01 assim que ele se conecta à rede, usando uma requisição HTTP.

Para iniciar a interface utilize o comando:

### `npm start`

E em seu navegador abra [http://localhost:3000](http://localhost:3000).

## Componentes Necessários
- Arduino Uno
- ESP-01
- Adaptador ESP-01 v1.0
- Cabo USB ou fonte para alimentação do Arduino
- 4 Jumpers para as conexões

## Requisitos de Funcionamento
Para que o projeto funcione corretamente, é necessário garantir o seguinte:
1. O Arduino deve estar ligado e alimentado por uma porta USB ou por uma fonte de 7v a 12v.
2. O ESP-01 deve estar conectado ao adaptador ESP-01 v1.0.

## Conexões de Hardware
Conecte os componentes conforme a tabela a seguir:

| Pino Adaptador ESP-01 | Pino Arduino       |
|------------------------|--------------------|
| RX                     | 7                 |
| TX                     | 6                 |
| VCC                    | 5V                |
| GND                    | GND               |

## Configuração do Código
Antes de carregar o código no Arduino, configure o IP correto do servidor no código para que o Arduino possa enviar o endereço IP do ESP-01. O IP do servidor deve estar definido no código e o servidor deve estar na mesma rede Wi-Fi que o ESP-01.

### Passo a Passo de Configuração
1. **Defina o IP do servidor** no código Arduino, alterando a variável `server` para o endereço IP da máquina onde o servidor Node.js está rodando.
2. **Carregue o código** no Arduino usando a IDE do Arduino.
3. **Conecte todos os componentes** de acordo com as instruções de conexões de hardware.

## Funcionamento do Projeto
1. Ao ser ligado, o Arduino inicia a comunicação com o ESP-01 e tenta conectá-lo à rede Wi-Fi usando as credenciais definidas no código.
2. Uma vez conectado, o ESP-01 obtém seu endereço IP.
3. O Arduino envia uma requisição HTTP ao servidor Node.js, incluindo o IP do ESP-01 via cabeçalho `X-ESP-IP`.
4. O servidor recebe e registra o IP.

## Requisitos do Servidor
O servidor deve estar rodando Node.js com Express para receber o IP. Certifique-se de que:
- O servidor está configurado para escutar requisições na porta 8000.
- O servidor e o ESP-01 estão conectados à mesma rede Wi-Fi.

### Exemplo de Inicialização do Servidor
```bash
# Navegue até o diretório do servidor
cd /caminho/para/o/servidor

# Inicie o servidor
node server.js
