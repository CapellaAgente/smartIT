**Smart IT - Sistema de Monitoramento e Arrefecimento de Racks**  
**📋 1. Descrição do Projeto**  
Este projeto foi desenvolvido como parte do **Trabalho de Graduação (TG)** para o curso de Engenharia de Computação. O objetivo principal é mitigar o risco de superaquecimento em racks de servidores através de um sistema autônomo de monitoramento térmico e acionamento de arrefecimento ativo.  
O sistema utiliza um microcontrolador **ESP32** para coletar dados de temperatura e umidade em tempo real, enviando-os via protocolo  **MQTT** para um broker  **Mosquitto** hospedado em um servidor local Linux (ambiente de testes "PC Batata"). Os dados são persistidos em um banco de dados de séries temporais  **InfluxDB** para análise histórica e auditoria.  
![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAnEAAAACCAYAAAA3pIp+AAAABmJLR0QA/wD/AP+gvaeTAAAACXBIWXMAAA7EAAAOxAGVKw4bAAAANUlEQVR4nO3OQQmAABRAsSfYxKK/kYXEkyk8WcGbCFuCLTOzVXsAAPzFuVZ3dXw9AQDgtesB/v8F8JQadPwAAAAASUVORK5CYII=)  
**🛠️ 2. Tecnologias Utilizadas**  
- **Microcontrolador:** ESP32 (NodeMCU).  
- **Atuadores/Sensores:** Sensor de Temperatura/Umidade DHT11, Módulo Relé 12V, Micro-ventoinha 12V.  
- **Firmware:** Linguagem C++ (Framework Arduino/PlatformIO).  
- **Comunicação:** Protocolo MQTT (Eclipse Mosquitto).  
- **Banco de Dados:** InfluxDB v1.12.4 (Séries Temporais).  
- **Visualização/Dashboard**: Grafana v13.0.1 (Monitoramento).  
![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAnEAAAACCAYAAAA3pIp+AAAABmJLR0QA/wD/AP+gvaeTAAAACXBIWXMAAA7EAAAOxAGVKw4bAAAANUlEQVR4nO3OYQ1AABSAwY8JoIGqr4Z6Eoiggn9mu0twy8wc1RkAAH9xbdVa7V9PAAB47X4A9C4EIsmYmgsAAAAASUVORK5CYII=)
**🔧 3. Arquitetura e Desafios Técnicos**  
Durante a implementação, o desafio crítico atual é o acionamento da ventoinha de 12V utilizando a lógica de 3.3V do ESP32:  
1. **Isolamento de Potência:** Usaremos uma fonte externa de 12V dedicada para a bobina do relé e para o motor da ventoinha, garantindo torque máximo.  
2. **Unificação de Referenciais (GND):** Interconexão do GND da fonte externa com o GND do microcontrolador para estabilização do sinal de controle.  
3. **Distribuição de Tensão:** Utilização do pino VIN do ESP32 para alimentar a lógica do módulo relé.  
![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAnEAAAACCAYAAAA3pIp+AAAABmJLR0QA/wD/AP+gvaeTAAAACXBIWXMAAA7EAAAOxAGVKw4bAAAANUlEQVR4nO3OQQmAABRAsSd4NIGJjPWxpgGsYQVvImwJtszMXp0BAPAX91pt1fH1BACA164HhZwEOFrXVOsAAAAASUVORK5CYII=)  
**🚀 4. Configuração do Ambiente (Setup)**  
**4.1. Banco de Dados (InfluxDB v1.12.x)**  
Como a versão 1.12 não possui interface web nativa (UI), a gestão é feita via CLI. Acesse o console no terminal e crie o banco:  
influx  
 CREATE DATABASE smart_it_db 
   
**4.2. Monitoramento de Mensagens (MQTT)**  
Para validar o tráfego de dados JSON enviados pelo ESP32, utilize o comando:  
mosquitto_sub -h localhost -t "projeto/smart_it/sensor" -v  
   
**💻 5. Firmware e Código Fonte**  
O código fonte completo reside na pasta /Firmware. Certifique-se de configurar as seguintes variáveis antes do upload:  
SSID / Password: Credenciais da rede Wi-Fi local.  
MQTT_SERVER: Endereço IP do Broker.  
INFLUXDB_DB: Nome do banco de dados criado (smart_it_db).

**📂 6. Estrutura do Repositório**  
/Firmware: Arquivos de código fonte (.cpp).  
README.md: Documentação técnica principal.  
