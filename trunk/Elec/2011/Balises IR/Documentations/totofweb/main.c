/*
 * Carte de réception de balise
 *
 * Christophe Le Lann <contact@totofweb.net>
 * http://www.totofweb.net/robots-projet-67.html
 *
 * Envoie à intervalle de temps régulier un message CAN de 4 octets :
 *  - 2 octets contenant l'état bit à bit des 16 capteurs, après filtrage des orphelins
 *  - 1 octet contenant l'angle décodé (centre de l'amas principal)
 *  - 1 octet contenant la largeur de l'amas principal (indique grossièrement la proximité)
 */

//-----------------------------
// Paramétrages divers
//-----------------------------

// Taille des buffers série
#define UART0_RXBUF_SIZE		64
#define UART0_TXBUF_SIZE		1
#define UART1_RXBUF_SIZE		64
#define UART1_TXBUF_SIZE		255


#define NBTSOP					16			// Nombre de capteurs TSOP
#define NBAMAS					8			// Nombre maximal d'amas possibles
#define NBMOYENNE				5			// Nombre de mesures pour la moyenne flottante
#define DETECTION_SEUIL			2			// Nombre minimal de détections de BALISE_CODE pour valider la bonne vue de la balise
#define PI8						(M_PI / 8)	// Pi/8
#define FLOAT_PRECISION			0.000001f

#define CAN_MOB_DATA			1			// MOb dédié à l'envoi des données

#include "../common/can_protocol.h"
#include "../common/balise_protocol.h"

//-----------------------------
// Librairies
//-----------------------------

#include <math.h>
#include <compat/deprecated.h>	// Macros sbi et cbi       - http://www.nongnu.org/avr-libc/user-manual/group__deprecated__items.html

//-----------------------------
// Librairies persos
//-----------------------------

#include "drivers/timer1.h"
#include "drivers/uart0.h"
#include "drivers/uart1.h"
#include "drivers/can.h"
#include "periphs/mux.h"
#include "libs/delais.h"

//-----------------------------
// Types spéciaux
//-----------------------------

typedef struct {
	unsigned char premier;
	unsigned char dernier;
	unsigned char count;
} amas_t;

//-----------------------------
// Variables globales
//-----------------------------

volatile unsigned char tmr1_ovf = 0;

// Buffers de liaison série
unsigned char uart0_RxBuf_tab[UART0_RXBUF_SIZE];
unsigned char uart1_RxBuf_tab[UART1_RXBUF_SIZE];
unsigned char uart0_TxBuf_tab[UART0_TXBUF_SIZE];
unsigned char uart1_TxBuf_tab[UART1_TXBUF_SIZE];

//-----------------------------
// Prototypes
//-----------------------------

// Fonctions
void can_mob_configping(void);

// Interruptions
void timer1_int(void);
void can_int_mob_func(unsigned char mob);

//-----------------------------
// Fonctions
//-----------------------------

void can_mob_configping(void) {
	can_mob_select(CAN_MOB_PING);
	can_mob_clear();
	can_mob_setid_std(CAN_ID11_BAL_PING);
	can_mob_setmsk_std(CAN_MSK_11B);
	can_mob_setidemsk();
	can_mob_setrtr();
	can_mob_setrtrmsk();
	can_mob_setdlc(0);
	can_mob_irqon(CAN_MOB_PING);
	can_mob_setmode(CAN_MOB_MODE_RX_AUTOREPLY);
}

//-----------------------------
// Interruptions
//-----------------------------

void timer1_int(void) {								// Fonction appelée à 32Hz
	tmr1_ovf = 1;
}
void can_int_mob_func(unsigned char mob) {
	if (mob == CAN_MOB_PING) {
		// On le réactive en autoreply
		can_mob_configping();
	}
}

//-----------------------------
// Fonction principale
//-----------------------------

int main (void) {

	// Correspondance entre la position sur les multiplexeurs et le bit de capteurs_state
	unsigned char bit[2][8] = {
		{8,	9,	10,	7,	11,	14,	12,	13},	// Mux 1, UART 1
		{0,	1,	2,	15,	3,	6,	4,	5}		// Mux 0, UART 0
	};

	unsigned char i, j;								// Variables sans lesquelles un programmeur n'est rien
	unsigned char decoding_index = 0;				// Indice de 0 à 7 du capteur en cours de décodage (adresse de multiplexage)
	unsigned char receptions;
	unsigned char wrongcode;						// Nombre de caractères reçus différents du code attendu

	// État des capteurs en bit à bit
	/*
	 *           AVANT
	 *             7
	 *          6     8
	 *       5           9
	 *     4              10
	 * G  3                11  D
	 *     2              12
	 *       1          13
	 *         0      14
	 *            15
	 *         ARRIERE
	 */
	unsigned int  tsop_state = 0;					// État lu sur les TSOP
	unsigned int  capteurs_state = 0;				// État lu sur les TSOP après traitement d'orphelins

	amas_t amas[NBAMAS];							// Regroupement en amas des différentes détections

	unsigned char valid[NBMOYENNE];					// Indique la validité des 5 dernières mesures
	float angle[NBMOYENNE];							// Les 5 derniers angles (0 = le plus récent), de 0 à 360 (attention au modulo)
	float cosinus[NBMOYENNE];						// Valeurs des cosinus des angles
	float sinus[NBMOYENNE];							// Valeurs des sinus des angles
	float moyenne;									// Angle moyen sur les 5 dernières valeurs (seulement les valides)
	float x, y, temp;								// Variables utilisées pour le moyennage temporel

	enum {
		POS_SSW		=  0,
		POS_SW		=  1,
		POS_SWW		=  2,
		POS_W		=  3,
		POS_NWW		=  4,
		POS_NW		=  5,
		POS_NNW		=  6,
		POS_N		=  7,
		POS_NNE		=  8,
		POS_NE		=  9,
		POS_NEE		= 10,
		POS_E		= 11,
		POS_SEE		= 12,
		POS_SE		= 13,
		POS_SSE		= 14,
		POS_S		= 15,
		POS_UNKNOWN	= 0xFF,
	} balise_angle;									// Valeurs retournées

	unsigned char can_data[4];						// 4 octets de la trame CAN envoyée

	cli();
	mux_init();
	uart0_init(BALISE_BAUDRATE, BALISE_NBBITS, BALISE_PARITY, BALISE_NBSTOP, uart0_RxBuf_tab, UART0_RXBUF_SIZE, uart0_TxBuf_tab, UART0_TXBUF_SIZE);
	uart1_init(BALISE_BAUDRATE, BALISE_NBBITS, BALISE_PARITY, BALISE_NBSTOP, uart1_RxBuf_tab, UART1_RXBUF_SIZE, uart1_TxBuf_tab, UART1_TXBUF_SIZE);
	can_init(CAN_BAUDRATE, CAN_MODE_ENABLED, INTERRUPTS);
	can_int_mob_enable(can_int_mob_func);			// Configuration de l'interruption qui écoute le CAN
	can_mob_configping();							// Configuration du MOb 0 en autoreply de PING
	timer1_setmode(T1_MODE_CTC);					// Timer1 en mode Clear on Timer Compare
	timer1ctc_setfreq(32);							// 32 Hz
	timer1ctc_isr_enable(timer1_int);				// Interruption sur Compare A
	sei();

	for (i = 0; i < NBAMAS; i++)
		amas[0].count = 0;


	uart1_puts_buffered("Demarrage...\n");

	// On attend une demi-seconde, au cas où on voudrait reprogrammer l'AVR
	// Parce que l'activation des multiplexeurs entre en conflit avec la reprogrammation

	delay_ms(500);
	mux_enable();

	while (1) {
		// On attend le déclenchement du Timer1 (32Hz)
		while (!tmr1_ovf);
		tmr1_ovf = 0;

/*
		// Séquence de débug renvoyant les vues des capteurs
		uart1_putc_buffered('0'+decoding_index);
		while (uart0_RxBuf_GetLength() > 0) {
			uart1_putc_buffered(uart0_RxBuf_GetFromFront());
		}
		uart1_putc_buffered('\t');
		while (uart1_RxBuf_GetLength() > 0) {
			uart1_putc_buffered(uart1_RxBuf_GetFromFront());
		}
		uart1_putc_buffered('\n');*/

		// La pêche a-t-elle été bonne avec le précédent capteur ?
		receptions = 0;
		wrongcode = 0;
		while (uart0_RxBuf_GetLength() > 0)
			if (uart0_RxBuf_GetFromFront() == BALISE_CODE)
				receptions++;
			else
				wrongcode++;
		if (receptions >= DETECTION_SEUIL)
			tsop_state |= (1 << bit[0][decoding_index]);
		else
			tsop_state &= ~((unsigned int)(1 << bit[0][decoding_index]));

		receptions = 0;
		while (uart1_RxBuf_GetLength() > 0)
			if (uart1_RxBuf_GetFromFront() == BALISE_CODE)
				receptions++;
			else
				wrongcode++;
		if (receptions >= DETECTION_SEUIL)
			tsop_state |= (1 << bit[1][decoding_index]);
		else
			tsop_state &= ~((unsigned int)(1 << bit[1][decoding_index]));

		uart0_RxBuf_Flush();
		uart1_RxBuf_Flush();

		// On passe au capteur suivant
		decoding_index++;
		if (decoding_index > 7)
			decoding_index = 0;
		mux_set(decoding_index);

		// On passe au décodage de la mesure courante

		capteurs_state = tsop_state;
		// Elimination des orphelins (11011 => 11111)
		for (i = 0; i < NBTSOP; i++)
			if ((capteurs_state & (1 << ((i-1)%NBTSOP))) && !(capteurs_state & (1 << (i%NBTSOP))) && (capteurs_state & (1 << ((i+1)%NBTSOP))))
				capteurs_state |= (1 << i);

		// On décale d'un cran tout l'historique de détection
		for (i = (NBMOYENNE-1); i > 0; i--) {
			angle[i] = angle[i-1];
			valid[i] = valid[i-1];
			cosinus[i] = cosinus[i-1];
			sinus[i] = sinus[i-1];
		}

		if (capteurs_state == 0 || capteurs_state == 0xFF) {
			// On ne distingue pas la balise adverse
			valid[0] = 0;
			amas[0].count = 0;
		} else {
			// Au moins un TSOP voit la balise adverse
			valid[0] = 1;

			// Réinitialisation des amas
			for (i = 0; i < NBAMAS; i++)
				amas[i].count = 0;
			// On classe en amas, en stockant le tsop de début et celui de fin
			j = 0;
			for (i = 0; i < NBTSOP; i++) {
				if (capteurs_state & (1 << i)) {
					if (amas[j].count == 0) {
						// Nouvel amas
						amas[j].premier = i;
						amas[j].dernier = i;
						amas[j].count = 1;
					} else {
						// On continue l'amas en cours
						amas[j].dernier = i;
						amas[j].count++;
					}
				} else {
					// Si le précédent était encore dans l'amas, on passe à l'amas suivant
					if (amas[j].count > 0 && amas[j].dernier == i-1)
						j++;
				}
			}
			// On raccorde éventuellement le 0 avec le 15
			if ((capteurs_state & (1 << 0)) && (capteurs_state & (1 << 15))) {
				// On fusionne le dernier amas dans le premier
				// On commence par chercher le dernier amas en j
				for (i = 0; i < (NBAMAS-2); i++)
					if (amas[i+1].count == 0)
						break;
				// Si on a plus d'un amas, on fusionne
				if (i > 0) {
					amas[0].premier = amas[i].premier;
					amas[0].count += amas[i].count;
					amas[i].count = 0;
				}
			}

			// Anti-reflet : on ne conserve que le plus grand amas, que l'on stocke dans l'amas 0
			for (i = 1; i < NBAMAS; i++) {
				if (amas[i].count > amas[0].count) {
					amas[0].count   = amas[i].count;
					amas[0].premier = amas[i].premier;
					amas[0].dernier = amas[i].dernier;
				}
			}

			// On calcule l'angle milieu, en prenant garde au saut 16-1
			if (amas[0].dernier < amas[0].premier)
				amas[0].dernier += NBTSOP;
			angle[0] = (float)(amas[0].dernier+amas[0].premier)/2;
			// Modulo en float :
			while (angle[0] < 0) angle[0] += NBTSOP;
			while (angle[0] >= NBTSOP) angle[0] -= NBTSOP;
		}

		// Moyennage de l'angle
		// On avance de 1 dans chacune des directions valides de angle[]
		// On calcule ensuite l'angle du vecteur obtenu pour avoir une direction moyenne
		moyenne = 0.0f;
		x = 0.0f;
		y = 0.0f;
		sinus[0] = sin(PI8 * angle[0]);
		cosinus[0] = cos(PI8 * angle[0]);
		for(i = 0; i < NBMOYENNE; i++){
			if (valid[i]) {
				x += cosinus[i];
				y += sinus[i];
			}
		}
		if (x < FLOAT_PRECISION && y < FLOAT_PRECISION)
				valid[0] = 0;
		else {
				// Rotation pour se ramener à y > 0
				if (y < 0.0f) { // Moitié Ouest
					moyenne += 8.0f;
					y = -y;
					x = -x;
				}
				// Rotation pour se ramener à x > 0
				if (x < 0.0f) {
					moyenne += 4.0f;
					temp = y;
					y = -x;
					x = temp;
				}
				moyenne += atan2(y, x)/M_PI*8;
		}
		// Discrétisation de l'angle
		if (valid[0]) {
			if (moyenne < 6.5 || moyenne >= 14.5) {
				if (moyenne < 2.5 || moyenne >= 14.5) {
					if (moyenne < 0.5 || moyenne >= 14.5) {
						if (moyenne < 15.5 && moyenne >= 14.5)
							balise_angle = POS_S;
						else
							balise_angle = POS_SSW;
					} else {
						if (moyenne < 1.5)
							balise_angle = POS_SW;
						else
							balise_angle = POS_SWW;
					}
				} else {
					if (moyenne < 4.5) {
						if (moyenne < 3.5)
							balise_angle = POS_W;
						else
							balise_angle = POS_NWW;
					} else {
						if (moyenne < 5.5)
							balise_angle = POS_NW;
						else
							balise_angle = POS_NNW;
					}
				}
			} else {
				if (moyenne < 10.5) {
					if (moyenne < 8.5) {
						if (moyenne < 7.5)
							balise_angle = POS_N;
						else
							balise_angle = POS_NNE;
					} else {
						if (moyenne < 9.5)
							balise_angle = POS_NE;
						else
							balise_angle = POS_NEE;
					}
				} else {
					if (moyenne < 12.5) {
						if (moyenne < 11.5)
							balise_angle = POS_E;
						else
							balise_angle = POS_SEE;
					} else {
						if (moyenne < 13.5)
							balise_angle = POS_SE;
						else
							balise_angle = POS_SSE;
					}
				}
			}
		} else {
			balise_angle = POS_UNKNOWN;
		}

		// Envoi des données sur le bus CAN
		can_data[0] = (unsigned char)(capteurs_state >> 8);
		can_data[1] = (unsigned char)(capteurs_state & 0xFF);
		can_data[2] = (unsigned char)(balise_angle);
		can_data[3] = amas[0].count;
		can_mob_select(CAN_MOB_DATA);
		can_mob_clear();
		can_mob_setid_std(CAN_ID11_BAL_DATA);
		can_mob_setdata(can_data, 4);
		can_mob_setmode(CAN_MOB_MODE_TX_DATA);

		// Message de débug
		uart1_puts_buffered("AMAS:");
		uart1_putc_buffered('0'+(char)(amas[0].count));
		switch (balise_angle) {
			case POS_N:		uart1_puts_buffered("\tN\n");	break;
			case POS_NNE:	uart1_puts_buffered("\tNNE\n");	break;
			case POS_NE:	uart1_puts_buffered("\tNE\n");	break;
			case POS_NEE:	uart1_puts_buffered("\tNEE\n");	break;
			case POS_E:		uart1_puts_buffered("\tE\n");	break;
			case POS_SEE:	uart1_puts_buffered("\tSEE\n");	break;
			case POS_SE:	uart1_puts_buffered("\tSE\n");	break;
			case POS_SSE:	uart1_puts_buffered("\tSSE\n");	break;
			case POS_S:		uart1_puts_buffered("\tS\n");	break;
			case POS_SSW:	uart1_puts_buffered("\tSSW\n");	break;
			case POS_SW:	uart1_puts_buffered("\tSW\n");	break;
			case POS_SWW:	uart1_puts_buffered("\tSWW\n");	break;
			case POS_W:		uart1_puts_buffered("\tW\n");	break;
			case POS_NWW:	uart1_puts_buffered("\tNWW\n");	break;
			case POS_NW:	uart1_puts_buffered("\tNW\n");	break;
			case POS_NNW:	uart1_puts_buffered("\tNNW\n");	break;
			case POS_UNKNOWN:
			default:		uart1_puts_buffered("\t?\n");	break;
		}
	}

	return 0;
}
