#include "def_principais.h"			//inclusao do arquivo com as principais definicoes
#include "LCD.h"   // biblioteca .c e .h LCD display 16x2
#include "funcoes.h"

ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1 
{
	TCNT1 = 0xC2F7;                                 // Renicia TIMER
	if(tempo)
		{
			tempo--;
		}
}

void configura_AD(){
// configura canal 
ADMUX = (1<<REFS0) | (1<<MUX2) | (1<<MUX0);			//Tens?o interna de ref (+5V), canal ADC5
ADCSRA = (1<<ADEN) | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//habilita o AD e define um prescaler de 128 (clk_AD = F_CPU/128), 125 kHz
}
signed int le_temp();
void set_pwm_pb3(unsigned char valor);


void set_pwm_pb3(unsigned char valor)  //  timer 0
{
	TCCR0A |=  (0<< COM0A1) | (1 << WGM21) | (1<<WGM20); //os WG definem o tipo de pwm (rapido) 
	// 1<< COM0A1 e  0 << COM0A0 define que o registrador OCR0A é limpo quando é igual ao valor de comparação
	// 0<< COM0A1 e  0 << COM0A0 pinos OCR0A e OCR0B desconectados
	TCCR0B =  0b00000101; // pre scalaer 1024 definido pelas tabelas do livro
	OCR0A=valor;
	sei();

	//pino tem que colocar no OCR0A ( olhar portas do arduino)
}

//--------------------------------------------------------------------------------------
int main()
{	
 	//declaracao da vari?vel para armazenagem dos digitos

	DDRB = 0b00111111;			//PORT B saida
	PORTB= 0;		        	//inicia desligado
	DDRC = 0b00000000;			//PORT C entrada
    PORTC= 0b11111111;          //PULL UP portC
	DDRD = 0xFF;				//PORTD como sa?da (display)
	PORTD= 0xFF;				//desliga o display
	UCSR0B = 0x00;				//PD0 e PD1 como I/O gen?rico, para uso no Arduino
	DDRC= 0b00000000;           // saidas motor e valvulas

	//configuração TIMER1
	TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1
 
  TCNT1 = 0xC2F7;                    // incia timer com valor para que estouro ocorra em 1 segundo
                                     // 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
  
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1
	sei();
	
	inic_LCD_4bits();				//inicializa o LCD
	configura_AD();
	cmd_LCD(0x01,0); 				//desloca cursor para a segunda linha
	
	tempo=3;   // varial de contagem de tempo
	while(1) 					//laco infinito
	{
		
		
		switch(estado)
		{  //estado inicial
		    case 1: bemvindo(); break; // Escreve Bem vindo!
				case 2: DefineLargura(); break; // Define o Valor A que vai ser a Largura
				case 3: DefineComprimento(); break; // Define o Valor B que vai ser o Comprimento
				case 4: DefineAltura(); break; // Define o Valor C que vai ser a altura
				case 5: DefineFurar(); break; // Define se o vaso vai ter um furo no fundo ou não.
				case 6: DefinePolir(); break; // Define se o vaso será polido depois de pronto
				case 7: MoldandoVaso(); break; // Constroi o Vaso ao fim do processo ligamos o forno.
				case 8: CozinhandoVaso(); break; // Cozinha a ceramica  ao fim do processo desligamos o forno
				case 9: ResfriandoVaso(); break; // Desligando o forno passamos a resfriar o vaso.
				case 10: FurandoVaso(); break; // Caso a resposta seja sim ele fara um furo no vaso.
				case 11: PolindoVaso(); break; // Caso a resposta seja sim ele irá polir o Vaso
				case 12: Reiniciar(); break; // Ao fim do Processo ele conta 3s e reinicia a maquina do inicio.
				// Em caso de ERRO pode ser apertar o botao Enter depois da configuração e automaticamente ele pula
				// para o Case 12.
		}   // fim switch
		
		if(estado>5)  // testes de estados emergencia tilizando botao ENTER a partir do estado 5
		{
			if(!tst_bit(PINC,2))  // verifica se botao enter pressionado
			{ pressionado++;  // incrementa variavel pressionado
				if(pressionado>3000)  // compara se ultrapassou o valor limit, botao pressionado por longo periodo
				{ escreve_LCD_Flash(msg_ERRO);
				estado=12; }   // direciona para estado 14
			} else
			{
				pressionado=0;  // botao nao pressionado  zera valor
			}  // fim if botao pressionado
		} // fim if teste de estados emergencia
		
	} // fim do while
	
} // fim do main

signed int le_temp()
{
	set_bit(ADCSRA, ADSC);								//inicia a convers?o
	while(tst_bit(ADCSRA,ADSC));						//espera a convers?o ser finalizada
	
	return (ADC);
}

void pwm()
{
		valorbinario=le_temp();  // le o valor binario de 10 bits
		set_pwm_pb3(valorbinario);
		
		
		// imprime valor binario
		ident_num(valorbinario,digitos);
		cmd_LCD(0xCC,0);			//desloca o cursor
		cmd_LCD(digitos[3],1);
		cmd_LCD(digitos[2],1);
		cmd_LCD(digitos[1],1);
		cmd_LCD(digitos[0],1);

		//  conversao em regra de 3 em mV
		valormv=(long)valorbinario*5000;
		valormv=valormv/1023;
		// imprime valor mV
		ident_num(valormv,digitos);
		cmd_LCD(0xC0,0);			//desloca o cursor
		cmd_LCD(digitos[3],1);
		cmd_LCD(digitos[2],1);
		cmd_LCD(digitos[1],1);
		cmd_LCD(digitos[0],1);
		escreve_LCD(" mV");
		
		_delay_ms(100);
}
