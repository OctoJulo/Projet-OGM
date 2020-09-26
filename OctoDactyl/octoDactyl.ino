//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ***************************** Projet *************************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
/*	Controleur dactyl en 6x6										*/
/*  + un joystick analogique										*/
/* **************************************************************** */
/*  Version: 1.0					---       		Date: 26/09/2020*/  
/*  OctoGeeK						---           			OctoJulo*/
/* **************************************************************** */
/*  REQUIS:		- teensy LC                     					*/
/*				- une matrice de bp 6*6               				*/
/*				- un joystick analogique type manette				*/
/* **************************************************************** */
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Bibliothèque ************************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
#include <Keypad.h>

//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ********** Constantes, Variables, Fonctions Internes *********** // 
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
const byte ROWS = 6; 												// nombre de ligne
const byte COLS = 6; 												// nombre de colonne
/*
char keys[ROWS][COLS] = {											// c'est ici que l'on place les commandes que l'on veut lier au bp.
	{KEY_ESC,KEY_F1,KEY_F2,KEY_F3,KEY_F4,KEY_F5},
	{KEY_O,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5},		
	{KEY_TAB,KEY_A,KEY_Z,KEY_E,KEY_R,KEY_T},	
	{KEY_SPACE,KEY_Q,KEY_S,KEY_D,KEY_F,KEY_G},	
	{KEY_LEFT_SHIFT,KEY_W,KEY_X,KEY_C,KEY_V,KEY_B},
	{KEY_SPACE,KEY_TAB,KEY_SPACE,KEY_ENTER}  // les valeurs sont trouvable sur le site: https://www.pjrc.com/teensy/td_keyboard.html
};
char keys[ROWS][COLS] = {											// c'est ici que l'on place les commandes que l'on veut lier au bp.
	{KEY_A,KEY_Z,KEY_E,KEY_R,KEY_T,KEY_Y},
	{KEY_U,KEY_I,KEY_O,KEY_P,KEY_Q,KEY_S},		
	{KEY_D,KEY_F,KEY_G,KEY_H,KEY_J,KEY_K},	
	{KEY_L,KEY_M,KEY_W,KEY_X,KEY_C,KEY_V},	
	{KEY_B,KEY_N,KEY_1,KEY_2,KEY_3,KEY_4},
	{KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0}  // les valeurs sont trouvable sur le site: https://www.pjrc.com/teensy/td_keyboard.html
};
*/

// PARCE QUE JE SUIS UN CONNARD, j'ai cablé en inverse ligne et colonne....
char keys[ROWS][COLS] = {											// c'est ici que l'on place les commandes que l'on veut lier au bp.
	{KEY_ESC,KEY_M,KEY_M,KEY_M,KEY_M,KEY_SPACE},
	{KEY_F1,KEY_1,KEY_TAB,KEY_LEFT_SHIFT,KEY_LEFT_CTRL,KEY_SPACE},		
	{KEY_F2,KEY_2,KEY_Q,KEY_A,KEY_Z,KEY_Y},	
	{KEY_F3,KEY_3,KEY_W,KEY_S,KEY_X,KEY_B},	
	{KEY_F4,KEY_4,KEY_E,KEY_D,KEY_C,KEY_ENTER},
	{KEY_F5,KEY_5,KEY_R,KEY_F,KEY_V,KEY_ENTER}  // les valeurs sont trouvable sur le site: https://www.pjrc.com/teensy/td_keyboard.html
};
//////////////////////////////////////////////////////////////////////
/*		mapping :
	k00 correspond a : bp colonne1 ligne1
		k00 k01 k02 k03 k04 k05
		k10 k11	k12	k13	k14	k15	
		k20 k21 k22 k23 k24 k25
		k30 k31 k32 k33 k34 k35 
		k40 k41 k42 k43 k44 k45
				k54	k55 
						--- JOY
							k51 ---
		    				k52 K53
//////////////////////////////////////////////////////////////////////
		esc F1  F2  F3  F4  F5
		²   &	é	"	'	(
		?	tab	a 	z 	e 	r
		?   shi q  	s 	d 	f   g
		?	ctl w 	x 	c 	v 	b
				b	g 
						--- joy
							spa ---
		    				t y
*/
//////////////////////////////////////////////////////////////////////
byte rowPins[ROWS] = {12,11,10,9,8,7};   //{7,8,9,10,11,12};						    // pins utilisées pour les lignes   {12,11,10,9,8,7};		
byte colPins[COLS] =	{21,20,17,16,15,14};						// pins utilisées pour les colonnes  !!!! coté cathode  {14,15,16,17,20,21};



//Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // affecte à chaque ligne et colonne les commandes voulu avec la lib Keypad

//essai
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, COLS, ROWS ); 


//int angle=0;														// pour le 
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Principal ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  Serial.println("Octo dactyl debug");
//	Joystick.useManualSend(true);
} 
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Progamme Boucle ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void loop()
{
	if (kpd.getKeys())
	{
  Serial.println("getkeys");
		for (int i=0; i<LIST_MAX; i++)   							// Scan the whole key list.
		{
			if ( kpd.key[i].stateChanged )  						// rentre dans la boucle si il y a changement d'etat.
			{
				switch (kpd.key[i].kstate) 							// renvoi une valeur si pressed,hold,released
				{
					case PRESSED:	
						Keyboard.set_key1(kpd.key[i].kchar);
						Keyboard.send_now();
						if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) 
						{
							Keyboard.set_modifier(MODIFIERKEY_SHIFT);
							Keyboard.send_now();
						}
						else if (kpd.key[i].kchar == char(KEY_LEFT_CTRL)) 
						{
							Keyboard.set_modifier(MODIFIERKEY_CTRL);
							Keyboard.send_now();
						}
						break;
					case HOLD:
						Keyboard.set_key1(kpd.key[i].kchar);
						Keyboard.send_now();
						break;
					case RELEASED:
						Keyboard.set_key1(0);
						Keyboard.send_now();
						if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT))
						{
							Keyboard.set_modifier(0);
							Keyboard.send_now();
						}
						else if(kpd.key[i].kchar == char(KEY_LEFT_CTRL))
						{
							Keyboard.set_modifier(0);
							Keyboard.send_now();
						}
						break;
				} 
			}
		}
	}



//////////////////////////////////////////////////////////////	
/*	Joystick.X(analogRead(0));
	Joystick.Y(analogRead(1));
	// make the hat switch automatically move in a circle
	angle = angle + 1;
	if (angle >= 360) angle = 0;
	Joystick.hat(angle);
	Joystick.send_now();
*/
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
