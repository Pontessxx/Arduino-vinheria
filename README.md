Projeto Arduino | Tinkercad
Team:
    RM 98460 	Felipe Capriotti da Silva Santos
    RM 98036	Henrique Pontes Olliveira
    RM 99679 	Gustavo Kawamura Christofani 
    RM 550908 	Vinicius Santos Yamashita de Farias 
    RM 99874 	Rafael Carvalho Mattos

https://www.tinkercad.com/things/2aYy1lji3uj

=== DESCRIÇÃO E EXPLICAÇÃO DO PROJETO ===

Descrição:

    O projeto visa o case da Vinheria Agnello, levando em consideração a preocupação da exposição dos vinhos ao UV, pois o vinho sofre oxidação resultando em um vinagre (nada bom para os negócios). O vinho é produzido através da fermentação de uvas, é durante este processo que os açúcares (glicose e frutose) são transformados em etanol ao ser exposto a luz agindo junto com o vidro (caso seja transparente potencializa) oxida.
    Sendo assim criamos um projeto utilizando o Arduino e outros materiais que possibilita alertar quando a luminosidade do local esteja alta aciona um buzzer (aparelho sonoro) por 3 segundos, caso esteja uma luz incidente mediana acende uma luz amarela, caso esteja com luminosidade baixa o led verde estará aceso.

Mas o que é o LDR:

    Light Dependent Resistor, O LDR (Light Dependent Resistor) é um tipo de resistor que muda sua resistência elétrica conforme a intensidade de luz que incide sobre ele.
    Já os conversores analógico para digital do Arduino, são circuitos integrados que convertem um sinal analógico (contínuo) em um sinal digital (discreto), que pode ser processado pelo microcontrolador do Arduino. Permitindo que o microcontrolador do Arduino leia e interprete esses sinais.
    O Arduino possui um conversor analógico para digital integrado em sua placa, analógicos p/ digitais de 10 bits entre 0 e 1023. Usa a função “analogRead()” ler valor analógico de um pino especifico do Arduino

O que é TMP36:

    O sensor TMP36 é um sensor de temperatura que pode ser utilizado em projetos eletrônicos com microcontroladores, como o Arduino. Ele é capaz de medir temperaturas com uma precisão de ±2°C entre -40°C e +125°C e fornece a saída de tensão analógica proporcional à temperatura medida. Sua tensão de alimentação é de 2,7 a 5,5V e ele possui três terminais: um para a alimentação, outro para o terra e um terceiro para a saída de sinal. Ele é um sensor fácil de utilizar e muito utilizado em projetos de automação residencial, controle de temperatura de ambientes, dentre outros.

O que é LCD:

    Um LCD (Liquid Crystal Display) é um dispositivo eletrônico de exibição que utiliza cristais líquidos para produzir imagens e texto. Ele é composto por uma camada de cristal líquido entre dois polarizadores, que permitem controlar o fluxo de luz através do material e exibir informações na tela. Os LCDs são comuns em dispositivos eletrônicos como telefones celulares, relógios digitais, calculadoras, câmeras digitais, entre outros. Eles são capazes de exibir caracteres alfanuméricos e gráficos simples, além de consumir relativamente pouca energia. No Arduino, o LCD é geralmente utilizado para exibir informações de sensores ou outras variáveis em projetos eletrônicos.

Pensamento antes da codificação:

    LDR  lê valor alto => pouca incidência de luz => led verde aceso, led vermelho e amarelo apagado
    LDR  lê valor entre X e y => média incidência de luz => led verde apagado, led amarelo aceso
    LDR lê valor de y a Z  => alta incidência de luz => led vermelho aceso, liga o buzzer de 3 seg duração

    TMP36 le valor menor que 0, alerta led vermelho aciona o buzzer, imprime no lcd Alerta
    TMP36 le valor entre 8-16, alerta led verde , imprime no lcd BOM
    TMP36 le valor maior que 17, alerta led amarelo , imprime no lcd MEDIO