// variaveis
unsigned int tempo=0,pressionado=0;
unsigned char tamlargura=2;
unsigned char tamcomprimento=3;
unsigned char tamaltura=4;
unsigned int valorbinario;
long valormv;   // variavel para conversao em mV
unsigned char flag1;
unsigned char  estado=1;	//declara variavel global
unsigned char digitos[tam_vetor];
unsigned int deseja_polir;
unsigned int deseja_furar;
///  funcoes da maquina de fazer vasos
//descricao dos pinos I/O
// ENTRADAS
#define botao_mais PC0 // botao mais
#define botao_menos PC1 // botao menos
#define botao_enter PC2 // botao ENTER / STOP processo
#define sensor_pronto PC3 // sensor molde pronto
#define sensor_frio PC4 // sensor vaso resfriado

//SAIDAS
#define furando PB5    // liga a broca para o furo
#define cozinhando PB4 // liga o forno
#define moldando PB3 // liga a maquina de molda o vaso nas medidas
#define polindo PB2 // liga a maquina de polir

//defini�ao para acessar a mem�ria flash 
PROGMEM const char msg_bemvindo[] = "Bem vindo !!!            \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_largura[] = "Def Largura     \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_comprimento[] = "Def Comprimento     \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_altura[] = "Def Altura    \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_furar[] = "Furo no Vaso       \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_polir[] = "Polir o Vaso    \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_inicializando[] = "Em processo....   \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_fim[] = "Fim do processo      \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_Moldando[] = "Moldando      \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_Cozinhando[] = "Cozinhando      \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_Resfriando[] = "Resfriando      \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_furandovaso [] = "Furando      \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_polindovaso [] = "Polindo      \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_ERRO [] = "Interrompendo!     \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_sim[] = "[sim]  [nao] \0";
PROGMEM const char msg_nao[] = "[sim]  [nao] \0";
PROGMEM const char msg_reiniciando[] = "Reiniciando....  \0"; //mensagem armazenada na memoria Flash


void bemvindo()
{
	cmd_LCD(0x80,0);  //limpa display
	escreve_LCD_Flash(msg_bemvindo);  // imprime mensagem
	if(!tempo) 
		{    // vefica tempo=0
			estado=2;  //muda de estado
			cmd_LCD(0x01,0);  // limpa display
		}
}

void DefineLargura()
{
	cmd_LCD(0x80,0);
	escreve_LCD_Flash(msg_largura);
	ident_num(tamlargura,digitos);  // separa digitos
			cmd_LCD(0xC5,0);	//posiciona lcd
			cmd_LCD(digitos[2],1); //imprime centena
			cmd_LCD(digitos[1],1);  //imprime dezena
			cmd_LCD(digitos[0],1); //imprime unidade
			cmd_LCD(0xC9,0);  //posiciona lcd
			cmd_LCD('<',1);  //imprime
			cmd_LCD('E',1);   //imprime
			cmd_LCD('N',1);   //imprime
			cmd_LCD('T',1);   //imprime
			cmd_LCD('E',1);   //imprime
			cmd_LCD('R',1);   //imprime
			cmd_LCD('>',1);	  //imprime
			if(!tst_bit(PINC,0)) { tamlargura++; _delay_ms(100);}  //if botao+
			if(!tst_bit(PINC,1)) { tamlargura--; _delay_ms(100); }  //if botao-
			if(!tst_bit(PINC,2)) { estado=3;  _delay_ms(300); cmd_LCD(0x01,0); }

}

void DefineComprimento()
{
	cmd_LCD(0x80,0);
	escreve_LCD_Flash(msg_comprimento);
	ident_num(tamcomprimento,digitos);  // separa digitos
			cmd_LCD(0xC5,0);	//posiciona lcd
			cmd_LCD(digitos[2],1); //imprime centena
			cmd_LCD(digitos[1],1);  //imprime dezena
			cmd_LCD(digitos[0],1); //imprime unidade
			cmd_LCD(0xC9,0);  //posiciona lcd
			cmd_LCD('<',1);  //imprime
			cmd_LCD('E',1);   //imprime
			cmd_LCD('N',1);   //imprime
			cmd_LCD('T',1);   //imprime
			cmd_LCD('E',1);   //imprime
			cmd_LCD('R',1);   //imprime
			cmd_LCD('>',1);	  //imprime
			if(!tst_bit(PINC,0)) { tamcomprimento++; _delay_ms(100);}  //if botao+
			if(!tst_bit(PINC,1)) { tamcomprimento--; _delay_ms(100); }  //if botao-
			if(!tst_bit(PINC,2)) { estado=4;  _delay_ms(300); cmd_LCD(0x01,0); }
}

void DefineAltura()
{
	cmd_LCD(0x80,0);
	escreve_LCD_Flash(msg_altura);
	ident_num(tamaltura,digitos);  // separa digitos
			cmd_LCD(0xC5,0);	//posiciona lcd
			cmd_LCD(digitos[2],1); //imprime centena
			cmd_LCD(digitos[1],1);  //imprime dezena
			cmd_LCD(digitos[0],1); //imprime unidade
			cmd_LCD(0xC9,0);  //posiciona lcd
			cmd_LCD('<',1);  //imprime
			cmd_LCD('E',1);   //imprime
			cmd_LCD('N',1);   //imprime
			cmd_LCD('T',1);   //imprime
			cmd_LCD('E',1);   //imprime
			cmd_LCD('R',1);   //imprime
			cmd_LCD('>',1);	  //imprime
			if(!tst_bit(PINC,0)) { tamaltura++; _delay_ms(100);}  //if botao+
			if(!tst_bit(PINC,1)) { tamaltura--; _delay_ms(100); }  //if botao-
			if(!tst_bit(PINC,2)) { estado=5;  _delay_ms(300); cmd_LCD(0x01,0); }
}

void DefineFurar()
{
	deseja_furar=0;
	cmd_LCD(0x80,0);
	escreve_LCD_Flash(msg_furar);
	cmd_LCD(0xC0,0);
	if(tst_bit(flag1, deseja_furar)) { escreve_LCD_Flash(msg_sim); } else { escreve_LCD_Flash(msg_nao); }
	
	if(!tst_bit(PINC,0)) { deseja_furar=1; _delay_ms(200); estado=6;}
	if(!tst_bit(PINC,1)) { estado=6;  _delay_ms(300); cmd_LCD(0x01,0); }
}

void DefinePolir()
{
	deseja_polir=0;
	cmd_LCD(0x80,0);
	escreve_LCD_Flash(msg_polir);
	cmd_LCD(0xC0,0);
	if(tst_bit(flag1, deseja_polir)) { escreve_LCD_Flash(msg_sim); } else { escreve_LCD_Flash(msg_nao); }
	
	if(!tst_bit(PINC,0)) { deseja_polir=2; _delay_ms(200); cmd_LCD(0x01,0); cmd_LCD(0xC0,0); estado=7;} 
	
	if(!tst_bit(PINC,1)) { estado=7;  _delay_ms(300); cmd_LCD(0xC0,0); cmd_LCD(0x01,0); }
}

void MoldandoVaso()
{	
	pwm();
	cmd_LCD(0xC0,0);
	cmd_LCD(0x80,0);
	escreve_LCD_Flash(msg_Moldando);
	set_bit(PORTB, moldando);
	  if(!tst_bit(PINC,sensor_pronto))                     // testa sensor molde pronto
	        {
                clr_bit(PORTB, moldando);
								tempo=5;                 
                estado=8;                         // muda estado
                cmd_LCD(0x80,0);                  
								clr_bit(PINC, sensor_pronto);
	    	}
}

void CozinhandoVaso()
{
	pwm();
	cmd_LCD(0xC0,0);
	cmd_LCD(0x80,0);
	escreve_LCD_Flash(msg_Cozinhando);
	set_bit(PORTB, cozinhando);                       
        if(!tempo)                     
	        {
                clr_bit(PORTB, cozinhando);                
                estado=9;                         // muda estado
                
                cmd_LCD(0x80,0);                  
	    	}
}

void ResfriandoVaso()
{
	pwm();
	cmd_LCD(0xC0,0);
	cmd_LCD(0x80,0);
	escreve_LCD_Flash(msg_Resfriando);
	set_bit(PORTB, moldando);                      
        if(!tst_bit(PINC,sensor_frio))                    
	        {
                clr_bit(PORTB, moldando);
								cmd_LCD(0xC0,0);
								cmd_LCD(0x80,0);
								cmd_LCD(0x01,0);
								tempo=4;                
                estado=10;                        
                cmd_LCD(0x80,0);
					}			 
}

void FurandoVaso()
{
	cmd_LCD(0xC0,0);
	cmd_LCD(0x80,0);
	if(deseja_furar!=1)
	{
		estado=11;
		}
	else {cmd_LCD(0x80,0);
	
	escreve_LCD_Flash(msg_furandovaso);
	set_bit(PORTB, furando);
	if(!tempo){
		
	clr_bit(PORTB, furando); tempo=4;
	cmd_LCD(0xC0,0);
	cmd_LCD(0x80,0);
			estado=11;
			}
}
}

void PolindoVaso()
{
	cmd_LCD(0xC0,0);
	cmd_LCD(0x80,0);
	if(deseja_polir!=2)
	{
		estado=12;
	}
	else { cmd_LCD(0x80,0);
	
	escreve_LCD_Flash(msg_polindovaso);
	set_bit(PORTB, polindo);
	if(!tempo){
	clr_bit(PORTB, polindo); tempo=4;
	cmd_LCD(0xC0,0);
	cmd_LCD(0x80,0);
	estado=12;}	
}
}

void Reiniciar()
{		
		cmd_LCD(0xC0,0);
		cmd_LCD(0x80,0);
		escreve_LCD_Flash(msg_fim);
		_delay_ms(3000);
		tempo=3;
		estado=1;
		cmd_LCD(0x01,0);
}


