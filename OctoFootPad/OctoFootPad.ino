//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ***************************** Projet *************************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
/*	controleur clavier à pied										*/
/* **************************************************************** */
/*  Version: 1.0					---       		Date: 03/05/2020*/  
/*  OctoGeeK						---           			OctoJulo*/
/* **************************************************************** */
/*  REQUIS:		- teensy LC                     					*/
/*				- une matrice de bp 2*4               				*/
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
const byte ROWS = 2; 												// nombre de ligne
const byte COLS = 4; 												// nombre de colonne

char keys[ROWS][COLS] = {											// c'est ici que l'on place les commandes que l'on veut lier au bp.
	{KEY_ESC,KEY_A,KEY_E,KEY_R},									// les valeurs sont trouvable sur le site: https://www.pjrc.com/teensy/td_keyboard.html
	{KEY_LEFT_SHIFT,KEY_TAB,KEY_SPACE,KEY_ENTER}  
};
byte rowPins[ROWS] = {7,8};											// pins utilisées pour les lignes
byte colPins[COLS] = {9,10,11,12};                  // pins utilisées pour les colonnes 


Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // affecte à chaque ligne et colonne les commandes voulu avec la lib Keypad
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Principal ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void setup()
{
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
						break;
				} 
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
