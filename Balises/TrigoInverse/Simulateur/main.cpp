// Oufff Team 2007
// Simulateur balises
// Par PCrack

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>


typedef struct Predefined_Command{ 
   int Number;
   char *Name;
   char *Command;
   Predefined_Command *Next;
}Predefined_Command;

///////////////////////////////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////////////////////////////

void CreateGraphical (void); // Creation de la fenetre et des objets

void OnDestroy(GtkWidget *pWidget, gpointer pData); // Sortie de l'application

gboolean callback_label(GtkWidget *widget, GdkEventButton *event, gpointer user_data);

static gboolean realisation( GtkWidget *aire_de_dessin, GdkEventConfigure *event );

static gboolean rafraichissement( GtkWidget *aire_de_dessin, GdkEventExpose *event );

void inter_beacons_angles_calculation (GtkSpinButton *spinbutton, gpointer user_data);

///////////////////////////////////////////////////////////////////////////////
// VARIABLES GLOBALES
///////////////////////////////////////////////////////////////////////////////

GtkWidget *pTextView1; // Zone de texte de l'espion
GtkWidget *pTextView2; // Zone de texte de la zone de commande
GtkTextBuffer* pTextBuffer1; // Buffer de la zone de texte de l'espion

Predefined_Command *Head=NULL;


   GtkWidget *pWindow; // Fenetre
   GtkWidget *pAire_de_dessin ;
   GtkWidget *pScrolled1; // Barre de defilement de la zone de l'espion
   
   
   GdkPixmap *pixmap;
   
   
  GtkWidget *pSpin1; // Barre de defilement de la zone de resultats
  GtkWidget *pSpin2; // Barre de defilement de la zone de resultats
  GtkWidget *pSpin3; // Barre de defilement de la zone de resultat
  GtkWidget *pSpin4; // Barre de defilement de la zone de resultats 
  GtkWidget *pSpin5; // Barre de defilement de la zone de resultats
  GtkWidget *pSpin6; // Barre de defilement de la zone de resultats
  
  int x_robot, y_robot;
  double theta;

///////////////////////////////////////////////////////////////////////////////
// Define de map
///////////////////////////////////////////////////////////////////////////////

//taille du terrain
#define TAILLE_MAP_L_Y (3000)
#define TAILLE_MAP_l_X (2100)

//Balise
        // balise 1
        #define BALISE_1_X (1050)
        #define BALISE_1_Y (0)
        
        // balise 2
        #define BALISE_2_X (0)
        #define BALISE_2_Y (3000)
        
        // balise 3
        #define BALISE_3_X (2100)
        #define BALISE_3_Y (3000)

//Taile robot
#define TAILLE_R_L 300
#define TAILLE_R_l 200


///////////////////////////////////////////////////////////////////////////////
// Define de dessin
///////////////////////////////////////////////////////////////////////////////

#define X_INIT_MAP 45
#define Y_INIT_MAP 20


//rapport de dessin (passage de mm a pixel)
#define RAPPORT (8)
#define DES_I(x) ((int)((double)(x)/(double)RAPPORT))
#define DES_F(x) ((double)(x)/(double)RAPPORT)
//rapport de dessin (passage de pixel a mm)
#define PIX_I(x) ((int)((double)(x)*(double)RAPPORT))
#define PIX_F(x) ((double)(x)*(double)RAPPORT)

//correction d'origine dans le sens mm -> pixel
#define X(x) (X_INIT_MAP + DES_I((x)) )
#define Y(y) (Y_INIT_MAP + DES_I(TAILLE_MAP_L_Y - (y)) )

//correction d'origine dans le sens dessin -> pixel
#define Xp(x) (PIX_I(x - X_INIT_MAP) )
#define Yp(y) (TAILLE_MAP_L_Y - PIX_I(y - Y_INIT_MAP))


#define R_BALISE 15

#define RAD2DEG(x) ((double)(180.0*(x)/M_PI))
#define DEG2RAD(x) ((double)(M_PI*(x)/180.0))

///////////////////////////////////////////////////////////////////////////////
// Define de debug
///////////////////////////////////////////////////////////////////////////////

#define pf_debug true
#define PFDEBUG(a, ...) if(pf_debug){fprintf(stderr, a, ##__VA_ARGS__);}






///////////////////////////////////////////////////////////////////////////////
// MAIN
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
   // FENETRE GRAPHIQUE
   // Initialisation de GTK+
   gtk_init(&argc, &argv);
   // Creation de la fenetre et des objets
   CreateGraphical();
   
   // Lancement de la boucle principale
	gtk_main();

	return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// FONCTIONS
///////////////////////////////////////////////////////////////////////////////

// Creation de la fenetre et des objets
void CreateGraphical (void)
{
 //  GtkWidget *pWindow; // Fenetre
   
   GtkWidget *pTable1; // Table permettant de decouper la fenetre en 3
   GtkWidget *pTable2; // Table permettant de decouper l'espace du controlleur
   
   GtkWidget *pLabel; // Label principal ( en haut de l'application )
            
   GtkWidget *pFrame1; // Decoration de l'espace du controlleur
   GtkWidget *pFrame2; // Decoration de l'espace de l'espion
   GtkWidget *pFrame3; // Decoration de la liste de commandes predefinies
   GtkWidget *pFrame4; // Decoration de la zone de commande
   GtkWidget *pFrame5; // Decoration de la zone de resultats
   GtkWidget *pFrame6;
   GtkWidget *pFrame7;
   GtkWidget *pFrame8;


   GtkWidget *pScrolled2; // Barre de defilement de la liste de commandes predefinies
   GtkWidget *pScrolled3; // Barre de defilement de la zone de commande
   GtkWidget *pScrolled4; // Barre de defilement de la zone de resultats
 
  
   GtkWidget *pTextView3; // Zone de texte de la zone de resultats
   
   GtkTextBuffer *pTextBuffer2; // Buffer de la zone de texte de la zone de commande
   GtkTextBuffer *pTextBuffer3; // Buffer de la zone de texte de la zone de resultats

   GtkWidget *pBox; // Box servant a centrer le bouton
   
   GtkWidget *pButton; // Bouton Send

   GtkListStore *pListStore; // Buffer de liste de commandes predefinies
   
   GtkCellRenderer *pCellRenderer; // Type de la cellule de la liste
   
   GtkWidget *pListView; // Liste de commandes predefinies
   
   GtkTreeViewColumn *pColumn; // Colonne dans la liste de commandes predefinies

   gchar* sUtf8; // Permet les conversions en UTF8
   
   
   
   
  	GtkWidget *event_box;
   	
   	//init de la position du robot
   	x_robot = 0;
    y_robot = 0;
    theta = 0.0;
   
   // FENETRE     
   // Creation de la fenetre principale de l'application
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// Titre de la fenetre principale
   sUtf8 = g_locale_to_utf8("SIMULATEUR BALISES", -1, NULL, NULL, NULL);
	gtk_window_set_title(GTK_WINDOW(pWindow), sUtf8);
   g_free(sUtf8);
	// Taille de la fenetre principale
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 800, 480);
	// Ajout d'une bordure autour de la fenetre principale
	gtk_container_set_border_width(GTK_CONTAINER(pWindow), 5);
	// Position de la fenetre principale
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_window_set_resizable (GTK_WINDOW(pWindow),FALSE);

	// Attachement du signal de destruction
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);
	
	

	

	// Creation de la table principale de 18 lignes 20 colonnes et insertion à l'interieur de la fenetre
   pTable1=gtk_table_new(18,20,TRUE);
   gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable1));

   // LABLE PRINCIPAL ET DECORATIONS
	// Creation du label de titre avec conversion en UTF8
   sUtf8 = g_locale_to_utf8("<span size=\"12\"><b>SIMULATEUR BALISES</b></span>\nOufff TEAM 2007\nPCrack - Chronos", -1, NULL, NULL, NULL);
   pLabel=gtk_label_new(sUtf8);
   g_free(sUtf8);
   gtk_label_set_use_markup(GTK_LABEL(pLabel), TRUE);
	gtk_label_set_justify (GTK_LABEL(pLabel), GTK_JUSTIFY_CENTER);

   // Creation des decorations pour marquer les zones avec conversion en UTF8
	sUtf8 = g_locale_to_utf8("Terrain :", -1, NULL, NULL, NULL);
    pFrame1 = gtk_frame_new(sUtf8);
    g_free(sUtf8);
   	
	sUtf8 = g_locale_to_utf8("Paramètres issus du simulateur :", -1, NULL, NULL, NULL);
    pFrame2 = gtk_frame_new(sUtf8);
    g_free(sUtf8);
   
  	sUtf8 = g_locale_to_utf8("x:", -1, NULL, NULL, NULL);
    pFrame3 = gtk_frame_new(sUtf8);
    g_free(sUtf8);
   
  	sUtf8 = g_locale_to_utf8("y:", -1, NULL, NULL, NULL);
    pFrame4 = gtk_frame_new(sUtf8);
    g_free(sUtf8);
    
  	sUtf8 = g_locale_to_utf8("theta:", -1, NULL, NULL, NULL);
    pFrame5 = gtk_frame_new(sUtf8);
    g_free(sUtf8);
   
  	sUtf8 = g_locale_to_utf8("alpha:", -1, NULL, NULL, NULL);
    pFrame6 = gtk_frame_new(sUtf8);
    g_free(sUtf8);
   
  	sUtf8 = g_locale_to_utf8("beta:", -1, NULL, NULL, NULL);
    pFrame7 = gtk_frame_new(sUtf8);
    g_free(sUtf8);
   
  	sUtf8 = g_locale_to_utf8("gamma:", -1, NULL, NULL, NULL);
    pFrame8 = gtk_frame_new(sUtf8);
    g_free(sUtf8);
    

   
   
    pAire_de_dessin = gtk_drawing_area_new();
    g_signal_connect( G_OBJECT(pAire_de_dessin), "realize", G_CALLBACK(realisation), NULL ) ;
    g_signal_connect( G_OBJECT(pAire_de_dessin), "expose_event", G_CALLBACK(rafraichissement), NULL ) ;

    // Création d'un GtkEventBox et insertion de celui-ci dans la fenêtre principale.
	event_box=gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(pFrame1), event_box);

    gtk_container_add(GTK_CONTAINER(event_box), GTK_WIDGET(pAire_de_dessin));
   
    gtk_widget_set_size_request (pTable1, 800, 480);

    // Insertion des decorations principales dans la table principale
    gtk_table_attach_defaults(GTK_TABLE(pTable1), pLabel, 0,20, 0, 2 );
    gtk_table_attach_defaults(GTK_TABLE(pTable1), pFrame1, 0,9, 2, 18 );
    gtk_table_attach_defaults(GTK_TABLE(pTable1), pFrame2, 9,20, 2, 6 );
    
    GtkWidget *pHBox1,*pHBox2;
       GtkWidget *pVBox;
    /* Creation de la box horizontale */
pHBox1 = gtk_hbox_new(TRUE, 0);
pHBox2 = gtk_hbox_new(TRUE, 0);
pVBox = gtk_vbox_new(TRUE, 0);
/* Ajout de la GtkHBox dans la GtkVBox */

gtk_box_pack_start(GTK_BOX(pVBox), pHBox1, TRUE, TRUE, 0);
gtk_box_pack_start(GTK_BOX(pVBox), pHBox2, TRUE, TRUE, 0);

/* Ajout des boutons 2 et 3 dans la GtkHBox */
gtk_box_pack_start(GTK_BOX(pHBox1), pFrame3, TRUE, TRUE, 0);
gtk_box_pack_start(GTK_BOX(pHBox1), pFrame4, TRUE, TRUE, 0);
gtk_box_pack_start(GTK_BOX(pHBox1), pFrame5, TRUE, TRUE, 0);

gtk_box_pack_start(GTK_BOX(pHBox2), pFrame6, TRUE, TRUE, 0);
gtk_box_pack_start(GTK_BOX(pHBox2), pFrame7, TRUE, TRUE, 0);
gtk_box_pack_start(GTK_BOX(pHBox2), pFrame8, TRUE, TRUE, 0);
     

     // Creation de la table pour la partie Paramètres de 10 lignes 4 colonnes et insertion dans la decoration du controleur 
 //    pTable2=gtk_table_new(10,10,TRUE);
 //    gtk_container_set_border_width(GTK_CONTAINER(pTable2), 5);
 //    gtk_container_add(GTK_CONTAINER(pFrame2), GTK_WIDGET(pTable2));

     gtk_container_add(GTK_CONTAINER(pFrame2), GTK_WIDGET(pVBox));
     
     // Insertion des decorations dans la zone des paramètres
 //    gtk_table_attach_defaults(GTK_TABLE(pTable2), pFrame3, 1,3, 0, 1 );
 //    gtk_table_attach_defaults(GTK_TABLE(pTable2), pFrame4, 4,6, 0, 1 );
 //    gtk_table_attach_defaults(GTK_TABLE(pTable2), pFrame5, 7,9, 0, 1 );
 //    gtk_table_attach_defaults(GTK_TABLE(pTable2), pFrame6, 1,3, 4, 5 );
 //    gtk_table_attach_defaults(GTK_TABLE(pTable2), pFrame7, 1,3, 5, 6 );
 //    gtk_table_attach_defaults(GTK_TABLE(pTable2), pFrame8, 1,3, 6, 7 );   
     
     pSpin1 = gtk_spin_button_new_with_range (0, 2100, 1);
     gtk_container_add(GTK_CONTAINER(pFrame3), GTK_WIDGET(pSpin1));
     
     pSpin2 = gtk_spin_button_new_with_range (0, 3000, 1);
     gtk_container_add(GTK_CONTAINER(pFrame4), GTK_WIDGET(pSpin2));
     
     pSpin6 = gtk_spin_button_new_with_range (0.00, 360.00, 0.5);
     gtk_container_add(GTK_CONTAINER(pFrame5), GTK_WIDGET(pSpin6));
     
     pSpin3 = gtk_spin_button_new_with_range (0.00, 360.00, 0.01);
     gtk_container_add(GTK_CONTAINER(pFrame6), GTK_WIDGET(pSpin3));
     
     pSpin4 = gtk_spin_button_new_with_range (0.00, 360.00, 0.01);
     gtk_container_add(GTK_CONTAINER(pFrame7), GTK_WIDGET(pSpin4));
     
     pSpin5 = gtk_spin_button_new_with_range (0.00, 360.00, 0.01);
     gtk_container_add(GTK_CONTAINER(pFrame8), GTK_WIDGET(pSpin5));
     
	 g_signal_connect(G_OBJECT(pSpin1), "value-changed", G_CALLBACK(inter_beacons_angles_calculation ), NULL);
	 g_signal_connect(G_OBJECT(pSpin2), "value-changed", G_CALLBACK(inter_beacons_angles_calculation ), NULL);
	 g_signal_connect(G_OBJECT(pSpin6), "value-changed", G_CALLBACK(inter_beacons_angles_calculation ), NULL);
	 
	// On ajoute le signal "button_press_event" au GtkEventBox.
	gtk_widget_add_events(event_box,GDK_BUTTON_PRESS_MASK );
	
	
	// On attache un CALLBACK au widget event_box.
	g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(callback_label), NULL);
	g_signal_connect(G_OBJECT(event_box), "motion_notify_event", G_CALLBACK(callback_label), NULL);
	g_signal_connect(G_OBJECT(event_box), "key_press_event", G_CALLBACK(callback_label), NULL);

   // Affichage de toutes les fenetres
	gtk_widget_show_all(pWindow);
}

// Sortie de l'application
void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
   // Arret de la boucle evenementielle
   gtk_main_quit();
}

void gdk_draw_cercle(GdkDrawable *drawable, GdkGC *gc, gboolean filled, gint x, gint y, gint rayon)
{
     gdk_draw_arc( drawable, gc, filled, x-rayon, y-rayon, rayon*2, rayon*2, 0, 180*130 );
}

void gdk_draw_balise(GdkDrawable *drawable, GtkWidget *widget, gint x, gint y, gint rayon, int taille_trait = 1)
{
     gdk_draw_cercle( drawable, widget->style->black_gc, TRUE, x, y, rayon);
     if(taille_trait < (int)rayon){
                     gdk_draw_cercle( drawable, widget->style->white_gc, TRUE,x, y, rayon - taille_trait);
     }
}


void gdk_draw_robot(GdkDrawable *drawable, GtkWidget *widget, gint x_centre, gint y_centre, gint x_l, gint y_L, gdouble angle)
{
     GdkPoint qi[4];
     //initialisation
	 qi[0].x = -x_l/2;
	 qi[0].y = -y_L/2;
	 qi[1].x = x_l/2;
	 qi[1].y = -y_L/2;
	 qi[2].x = x_l/2;
	 qi[2].y = y_L/2;
	 qi[3].x = -x_l/2;
	 qi[3].y = y_L/2;
	 
	 //rotation a l'origine
	 GdkPoint q[4];
	 double d_cos = cos(-angle);
	 double d_sin = sin(-angle);
	 q[0].x = (int)(d_cos*qi[0].x - d_sin*qi[0].y);
	 q[0].y = (int)(d_sin*qi[0].x + d_cos*qi[0].y);
	 q[1].x = (int)(d_cos*qi[1].x - d_sin*qi[1].y);
	 q[1].y = (int)(d_sin*qi[1].x + d_cos*qi[1].y);
	 q[2].x = (int)(d_cos*qi[2].x - d_sin*qi[2].y);
	 q[2].y = (int)(d_sin*qi[2].x + d_cos*qi[2].y);
	 q[3].x = (int)(d_cos*qi[3].x - d_sin*qi[3].y);
	 q[3].y = (int)(d_sin*qi[3].x + d_cos*qi[3].y);
	 
	 //translation
	 q[0].x += x_centre;
	 q[0].y += y_centre;
	 q[1].x += x_centre;
	 q[1].y += y_centre;
	 q[2].x += x_centre;
	 q[2].y += y_centre;
	 q[3].x += x_centre;
	 q[3].y += y_centre;
     gdk_draw_polygon( pixmap, widget->style->black_gc, true, q, 4 );
     
     //ligne de la fleche
     gdk_draw_line( pixmap, widget->style->white_gc,(int)((double)(q[0].x+q[1].x)/2.0), (int)((double)(q[0].y+q[1].y)/2.0), (int)((double)(q[2].x+q[3].x)/2.0), (int)((double)(q[2].y+q[3].y)/2.0) );
}

void gdk_draw_line_balises_robot(GdkDrawable *drawable, GdkGC *gc, gint x, gint y)
{
     GdkColor *color; color = new GdkColor();
     color->red = 60000; color->green = 0; color->blue = 0;
     gdk_gc_set_rgb_fg_color(gc, color);
     
     gdk_draw_line( pixmap, gc, x, y, X(BALISE_1_X), Y(BALISE_1_Y));
     gdk_draw_line( pixmap, gc, x, y, X(BALISE_2_X), Y(BALISE_2_Y));
     gdk_draw_line( pixmap, gc, x, y, X(BALISE_3_X), Y(BALISE_3_Y));
     
     color->red = 0; color->green = 0; color->blue = 0;
     gdk_gc_set_rgb_fg_color(gc, color);
     
}

void fonction_de_dessin( GtkWidget *aire_de_dessin)
{
     if (pixmap){
        gdk_pixmap_unref(pixmap);
      }
     pixmap = gdk_pixmap_new( aire_de_dessin->window, aire_de_dessin->allocation.width, aire_de_dessin->allocation.height, -1 );
       gdk_draw_rectangle( pixmap, aire_de_dessin->style->white_gc, TRUE, 0, 0, aire_de_dessin->allocation.width, aire_de_dessin->allocation.height );
       ///dessin
      //terrain
	  gdk_draw_rectangle( pixmap, aire_de_dessin->style->black_gc, FALSE, X_INIT_MAP, Y_INIT_MAP, DES_I(TAILLE_MAP_l_X), DES_I(TAILLE_MAP_L_Y) );
	  
	  //lignes entre balises et robot
	  gdk_draw_line_balises_robot( pixmap, aire_de_dessin->style->black_gc, X(x_robot), Y(y_robot));
	  
      //balises
      gdk_draw_balise(pixmap, aire_de_dessin, X(BALISE_1_X), Y(BALISE_1_Y), R_BALISE);
      gdk_draw_balise(pixmap, aire_de_dessin, X(BALISE_2_X), Y(BALISE_2_Y), R_BALISE);
      gdk_draw_balise(pixmap, aire_de_dessin, X(BALISE_3_X), Y(BALISE_3_Y), R_BALISE);
      
      //robot
      gdk_draw_robot(pixmap, aire_de_dessin, X(x_robot), Y(y_robot), DES_I(TAILLE_R_L), DES_I(TAILLE_R_l), DEG2RAD(theta));
      
      

      gtk_widget_queue_draw( aire_de_dessin );
     
}

static gboolean realisation( GtkWidget *aire_de_dessin, GdkEventConfigure *event )
{
      fonction_de_dessin(aire_de_dessin);
      gtk_widget_queue_draw( aire_de_dessin );

	return TRUE;
}


static gboolean rafraichissement( GtkWidget *aire_de_dessin, GdkEventExpose *event )
{
       gdk_draw_drawable( aire_de_dessin->window, aire_de_dessin->style->fg_gc[GTK_WIDGET_STATE(aire_de_dessin)],pixmap, event->area.x, event->area.y, event->area.x, event->area.y, event->area.width, event->area.height);
       return FALSE;
}


void inter_beacons_angles_calculation (GtkSpinButton *spinbutton, gpointer user_data)
{
  double x =    gtk_spin_button_get_value(GTK_SPIN_BUTTON(pSpin1));
  double y =    gtk_spin_button_get_value(GTK_SPIN_BUTTON(pSpin2));
  double teta = gtk_spin_button_get_value(GTK_SPIN_BUTTON(pSpin6));
  
  
  double u = sqrt( pow(TAILLE_MAP_L_Y,2) + pow(TAILLE_MAP_l_X/2,2) );
  double v = u;
  double w = TAILLE_MAP_l_X;
  
  double s = acos( TAILLE_MAP_L_Y / v );
  double r = s;  
  
  double a = sqrt( pow(TAILLE_MAP_L_Y-y,2) + pow(x,2) );
  double b = sqrt( pow(TAILLE_MAP_L_Y-y,2) + pow(TAILLE_MAP_l_X-x,2) );
  double c = sqrt ( pow(y,2) + pow((TAILLE_MAP_l_X/2)-x,2) );
  
  double alpha = acos( ( pow(a,2) + pow(b,2) - pow(w,2) ) / (2*a*b) );
  double beta  = acos( ( pow(b,2) + pow(c,2) - pow(u,2) ) / (2*b*c) );
  double gamma = acos( ( pow(a,2) + pow(c,2) - pow(v,2) ) / (2*a*c) );
  
  double Angle1 = fabs(acos((-TAILLE_MAP_L_Y*(y-TAILLE_MAP_L_Y)) / (TAILLE_MAP_L_Y * sqrt(pow(TAILLE_MAP_L_Y - y,2) + pow(x,2)))));
    
  double Angle2 = fabs(acos((-TAILLE_MAP_L_Y*(y-TAILLE_MAP_L_Y)) / (TAILLE_MAP_L_Y * sqrt( pow(TAILLE_MAP_L_Y - y,2) + pow(TAILLE_MAP_l_X-x,2)))));
    
  if (Angle1 < r) gamma = 2 * M_PI - gamma;
  
  if (Angle2 < s) beta = 2 * M_PI - beta ;
  
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(pSpin3),180*alpha/M_PI);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(pSpin4),180*beta/M_PI);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(pSpin5),180*gamma/M_PI);

  
  //fonction de dessin
  if(spinbutton == GTK_SPIN_BUTTON(pSpin1)){ x_robot = (int)x; }
  if(spinbutton == GTK_SPIN_BUTTON(pSpin2)){ y_robot = (int)y; }
  if(spinbutton == GTK_SPIN_BUTTON(pSpin6)){ theta = (int)teta; }
  fonction_de_dessin(pAire_de_dessin);
}

gboolean callback_label(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{	
	int x = Xp((int)event->x);
	int y = Yp((int)event->y);
	
	if(x >= 0 && x <= TAILLE_MAP_l_X && y >= 0 && y <= TAILLE_MAP_L_Y) {x_robot = x;y_robot = y;}

    //dessin
	fonction_de_dessin(pAire_de_dessin);
	//mise a jour de la position
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(pSpin1),x_robot);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(pSpin2),y_robot);
  
	return TRUE;
}
