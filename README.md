
<h1>Projeto Arduino | Tinkercad</h1>
link:
https://www.tinkercad.com/things/2aYy1lji3uj

![image](https://raw.githubusercontent.com/Pontessxx/Arduino-vinheria/main/arfuino-vinheria.png)
<h4>Team:</h4>
<p> RM 98036	Henrique Pontes Olliveira </p>
<p> RM 98460 	Felipe Capriotti da Silva Santos </p>
<p> RM 99679 	Gustavo Kawamura Christofani </p>
<p> RM 550908 	Vinicius Santos Yamashita de Farias </p>
<p> RM 99874 	Rafael Carvalho Mattos </p>

<h2> DESCRIÇÃO E EXPLICAÇÃO DO PROJETO </h2>

<h4>Descrição:</h4>

<p>O projeto visa o case da Vinheria Agnello, levando em consideração a preocupação da exposição dos vinhos ao UV, pois o vinho sofre oxidação resultando em um vinagre (nada bom para os negócios). O vinho é produzido através da fermentação de uvas, é durante este processo que os açúcares (glicose e frutose) são transformados em etanol ao ser exposto a luz agindo junto com o vidro (caso seja transparente potencializa) oxida.
Sendo assim criamos um projeto utilizando o Arduino e outros materiais que possibilita alertar quando a luminosidade do local esteja alta aciona um buzzer (aparelho sonoro) por 3 segundos, caso esteja uma luz incidente mediana acende uma luz amarela, caso esteja com luminosidade baixa o led verde estará aceso.</p>

<h4>Materiais:</h4>
<ul>
    <li>1	Arduino Uno R3</li>
    <li>1	Vermelho LED</li>
    <li>1	Amarelo LED</li>
    <li>1	Verde LED</li>
    <li>4	330 Ω Resistor</li>
    <li>1	Fotorresistor</li>
    <li>1	Piezo</li>
    <li>1	10 kΩ Resistor</li>
    <li>1	LCD 16 x 2</li>
    <li>1	250 kΩ Potenciômetro</li>
    <li>1	Sensor de temperatura [TMP36]</li>
    <li>Sensor de temperatura e umidade (DHT11)</li>
 </ul>
<h4>Mas o que é o LDR:</h4>

<p>Light Dependent Resistor, O LDR (Light Dependent Resistor) é um tipo de resistor que muda sua resistência elétrica conforme a intensidade de luz que incide sobre ele.
Já os conversores analógico para digital do Arduino, são circuitos integrados que convertem um sinal analógico (contínuo) em um sinal digital (discreto), que pode ser processado pelo microcontrolador do Arduino. Permitindo que o microcontrolador do Arduino leia e interprete esses sinais.
O Arduino possui um conversor analógico para digital integrado em sua placa, analógicos p/ digitais de 10 bits entre 0 e 1023. Usa a função “analogRead()” ler valor analógico de um pino especifico do Arduino</p>

<h4>Sensor de Temperatura e Umidade (DHT11):</h4>
<p>O sensor de temperatura e umidade DHT11 é um dispositivo que permite medir a temperatura e a umidade relativa do ar. Ele possui um elemento sensor que captura essas grandezas e um circuito interno que converte os dados em sinais digitais. No projeto, o DHT11 é utilizado para monitorar a temperatura e a umidade do ambiente e fornecer essas informações ao Arduino.
<h4>O que é TMP36:</p>

<p>O sensor TMP36 é um sensor de temperatura que pode ser utilizado em projetos eletrônicos com microcontroladores, como o Arduino. Ele é capaz de medir temperaturas com uma precisão de ±2°C entre -40°C e +125°C e fornece a saída de tensão analógica proporcional à temperatura medida. Sua tensão de alimentação é de 2,7 a 5,5V e ele possui três terminais: um para a alimentação, outro para o terra e um terceiro para a saída de sinal. Ele é um sensor fácil de utilizar e muito utilizado em projetos de automação residencial, controle de temperatura de ambientes, dentre outros.</p>

<h4>O que é LCD:</h4>

<p>Um LCD (Liquid Crystal Display) é um dispositivo eletrônico de exibição que utiliza cristais líquidos para produzir imagens e texto. Ele é composto por uma camada de cristal líquido entre dois polarizadores, que permitem controlar o fluxo de luz através do material e exibir informações na tela. Os LCDs são comuns em dispositivos eletrônicos como telefones celulares, relógios digitais, calculadoras, câmeras digitais, entre outros. Eles são capazes de exibir caracteres alfanuméricos e gráficos simples, além de consumir relativamente pouca energia. No Arduino, o LCD é geralmente utilizado para exibir informações de sensores ou outras variáveis em projetos eletrônicos. </p>

<h4>Pensamento antes da codificação:</h4>
<ul>Temos as condiçoes:
    <li>LDR  lê valor alto => pouca incidência de luz => led verde aceso, led vermelho e amarelo apagado</li>
    <li> LDR  lê valor entre X e y => média incidência de luz => led verde apagado, led amarelo aceso</li>
    <li> LDR lê valor de y a Z  => alta incidência de luz => led vermelho aceso, liga o buzzer de 3 seg duração</li>
    <li> TMP36 le valor menor que 0, alerta led vermelho aciona o buzzer, imprime no lcd Alerta</li>
    <li> TMP36 le valor entre 8-16, alerta led verde , imprime no lcd BOM</li>
    <li> TMP36 le valor maior que 17, alerta led amarelo , imprime no lcd MEDIO</li>
</ul>
    <ul>Variaveis: 
        <li> verde/bom: Luz BOM temp BOM</li>
        <li> Amarelo/MEDIO: Luz med Tempo BOM  ou luz boa tempo medio</li>
        <li> ruim: luz ou temp ruim</li>
        <li> quando estiver entre a temp >=8 e temp<=16: BOA</li>
        <li> temp<=0 e temp<=25: ruim</li>
        <li> se não é temp: Media</li>
 <ul>
