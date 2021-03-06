/*****************************************************************************************************************************
	LIT9 ( Linux Interface T9 ) - Human computer interface based on a TV remote control to interact with a Linux operating system.
	
	Copyright (C)  2010 
		Davide Mulfari:	davidemulfari@gmail.com
		Nicola Peditto:	n.peditto@gmail.com
		Carmelo Romeo:	carmelo.romeo85@gmail.com 
		Fabio Verboso:	fabio.verboso@gmail.com	

	This file is part of LIT9.

	LIT9 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	LIT9 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with LIT9.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************************************************************

	Developed at Univesity of Messina - Faculty of Engineering - Visilab
	
	Based on 
		- LIRC code http://www.lirc.org/

		- Predictive text technology (T9)  
			copyright  (C) 2000 by Markku Korsumäki  
			email: markku.t.korsumaki@mbnet.fi
		
****************************************************************************************************************************/


//To compile  
//g++ gtkprova.cpp -o gtkprova -lX11 -lpthread `pkg-config --cflags --libs gtk+-2.0`

#include <gtk/gtk.h>
#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <errno.h>
#include <getopt.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <pthread.h>
#define KEYCODE XK_A
#define N 5
int matrice[8][N];
int tastocor;
int indice;
gchar *sel;
const   gchar   *list_item_data_key="list_item_data";
void *thtel (void *arg);



  GtkWidget *window;
  GtkWidget *fixed;
  GtkWidget       *vbox;
  GtkWidget       *gtklist;
  gchar           buffer[64];
  GtkWidget       *list_item;
 
XKeyEvent createKeyEvent(Display *display, Window &win, Window &winRoot, bool press ,int keycode, int modifiers)
{
   XKeyEvent event;

   event.display     = display;
   event.window      = win;
   event.root        = winRoot;
   event.subwindow   = None;
   event.time        = CurrentTime;
   event.x           = 1;
   event.y           = 1;
   event.x_root      = 1;
   event.y_root      = 1;
   event.same_screen = True;
   event.keycode     = XKeysymToKeycode(display, keycode);
   event.state       = modifiers;

   if(press)
      event.type = KeyPress;
   else
      event.type = KeyRelease;

   return event;
}

void *apribrowser(void *arg)
{
	system("google-chrome");
}

void caricamatrice ()
{
	matrice[0][0]=XK_A;
	matrice[0][1]=XK_B;
        matrice[0][2]=XK_C;
        matrice[0][3]=XK_agrave;
        matrice[0][4]=XK_2;
        matrice[1][0]=XK_D;
	matrice[1][1]=XK_E;
        matrice[1][2]=XK_F;
        matrice[1][3]=XK_egrave;
        matrice[1][4]=XK_3;
        matrice[2][0]=XK_G;
	matrice[2][1]=XK_H;
        matrice[2][2]=XK_I;
        matrice[2][3]=XK_igrave;
        matrice[2][4]=XK_4;
        matrice[3][0]=XK_J;
	matrice[3][1]=XK_K;
        matrice[3][2]=XK_L;
        matrice[3][3]=XK_5;
        matrice[3][4]=XK_0;
        matrice[4][0]=XK_M;
	matrice[4][1]=XK_N;
        matrice[4][2]=XK_O;
        matrice[4][3]=XK_ograve;
        matrice[4][4]=XK_6;
        matrice[5][0]=XK_P;
	matrice[5][1]=XK_Q;
        matrice[5][2]=XK_R;
        matrice[5][3]=XK_S;
        matrice[5][4]=XK_7;
	matrice[6][0]=XK_T;
	matrice[6][1]=XK_U;
        matrice[6][2]=XK_V;
        matrice[6][3]=XK_ugrave;
        matrice[6][4]=XK_8;
        matrice[7][0]=XK_W;
	matrice[7][1]=XK_X;
        matrice[7][2]=XK_Y;
        matrice[7][3]=XK_Z;
        matrice[7][4]=XK_9;
}

void tappa()
{
    if (tastocor==0) return;
	int tasto=matrice[tastocor-2][indice];
 Display *display = XOpenDisplay(0);
   if(display == NULL)
      return;
     Window winRoot = XDefaultRootWindow(display);

// Find the window which has the current keyboard focus.
   Window winFocus;
   int    revert;
   XGetInputFocus(display, &winFocus, &revert);
 
// Send a fake key press event to the window.
   XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, tasto, 0);
   XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

// Send a fake key release event to the window.
   event = createKeyEvent(display, winFocus, winRoot, false, tasto, 0);
   XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

  
XCloseDisplay(display);
}

void caricalist (int tasto, Display* display)
{
    GtkWidget       *list_item;
    GList           *dlist;
    guint           i;
    gchar           buffer[64];
    gtk_list_clear_items ((GtkList *) gtklist,0,N);

    dlist=NULL;
    gchar  *str;
str = (gchar*)malloc(sizeof(gchar));
sprintf(str,"");
tastocor=tasto;
    for (i=0; i<N; i++) {
    if (tasto ==2)
    {
        if (i==0) sprintf(buffer, "a");
        else if (i==1) sprintf(buffer, "b");
	else if (i==2) sprintf(buffer, "c");
	else if (i==3) sprintf(buffer, "à");
	else if (i==4) sprintf(buffer, "2");
    }
    else if (tasto ==3)
    {
        if (i==0) sprintf(buffer, "d");
        else if (i==1) sprintf(buffer, "e");
	else if (i==2) sprintf(buffer, "f");
	else if (i==3) sprintf(buffer, "è");
	else if (i==4) sprintf(buffer, "3");
    }
    else if (tasto ==4)
    {
        if (i==0) sprintf(buffer, "g");
        else if (i==1) sprintf(buffer, "h");
	else if (i==2) sprintf(buffer, "i");
	else if (i==3) sprintf(buffer, "ì");
	else if (i==4) sprintf(buffer, "4");
    }
    else if (tasto ==5)
    {
        if (i==0) sprintf(buffer, "j");
        else if (i==1) sprintf(buffer, "k");
	else if (i==2) sprintf(buffer, "l");
	else if (i==3) sprintf(buffer, "5");
	else if (i==4) sprintf(buffer, "0");
    }
    else if (tasto ==6)
    {
        if (i==0) sprintf(buffer, "m");
        else if (i==1) sprintf(buffer, "n");
	else if (i==2) sprintf(buffer, "o");
	else if (i==3) sprintf(buffer, "ò");
	else if (i==4) sprintf(buffer, "6");
    }
    else if (tasto ==7)
    {
        if (i==0) sprintf(buffer, "p");
        else if (i==1) sprintf(buffer, "q");
	else if (i==2) sprintf(buffer, "r");
	else if (i==3) sprintf(buffer, "s");
	else if (i==4) sprintf(buffer, "7");
    }
    else if (tasto ==8)
    {
        if (i==0) sprintf(buffer, "t");
        else if (i==1) sprintf(buffer, "u");
	else if (i==2) sprintf(buffer, "v");
	else if (i==3) sprintf(buffer, "ù");
	else if (i==4) sprintf(buffer, "8");
    }
    else if (tasto ==9)
    {
        if (i==0) sprintf(buffer, "w");
        else if (i==1) sprintf(buffer, "x");
	else if (i==2) sprintf(buffer, "y");
	else if (i==3) sprintf(buffer, "z");
	else if (i==4) sprintf(buffer, "9");
    }
       
        list_item=gtk_list_item_new_with_label(buffer);
        dlist=g_list_append(dlist, list_item);
        gtk_widget_show(list_item);
        gtk_object_set_data(GTK_OBJECT(list_item), list_item_data_key,str);
    }

    gtk_list_append_items((GtkList*)(gtklist), dlist);
     indice=0;
        gtk_list_select_item((GtkList *) gtklist,indice);
      
 XWarpPointer(display, None, None, 0, 0, 0, 0, -10000,-10000);
XWarpPointer(display, None, None, 0, 0, 0, 0, 90, 0);
gdk_window_process_all_updates ();

   }


void elabora(char *codice)
{
   gint x=0, y=0, passo=5;
   Display *display = XOpenDisplay(0);
   if(display == NULL)
      return;
gchar  *str;
str = (gchar*)malloc(sizeof(gchar));
sprintf(str,"");
   if (strcmp(codice, "2fdf807")==0)
   {
	if (indice==(N-1)) indice=0;

	else indice = indice+1;
        gtk_list_select_item((GtkList *) gtklist,indice);
        gdk_window_process_all_updates ();
   }
   else  if (strcmp(codice, "2fdd827")==0)
   {
       if (indice==0) indice=N-1;
       else indice = indice-1;
       gtk_list_select_item((GtkList *) gtklist,indice);
       gdk_window_process_all_updates ();
   }
   else  if (strcmp(codice, "2fd48b7")==0) exit(0);
   else  if (strcmp(codice, "2fdd22d")==0)
{
int res;
  pthread_t tel_thread;
  res = pthread_create(&tel_thread, NULL, apribrowser, NULL);
   if (res != 0) {
   	exit(EXIT_FAILURE);
   	 printf("\nerrore partenza thread");

  }
}
   else  if (strcmp(codice, "2fdb847")==0) XWarpPointer(display, None, None, 0, 0, 0, 0, 0,passo);	
   else if (strcmp(codice, "2fd9867")==0) XWarpPointer(display, None, None, 0, 0, 0, 0, 0,passo*(-1));
   
   else if (strcmp(codice, "2fd02fd")==0) XWarpPointer(display, None, None, 0, 0, 0, 0, passo, 0);
   else if (strcmp(codice, "2fd42bd")==0) XWarpPointer(display, None, None, 0, 0, 0, 0, passo*(-1),0);
   else if (strcmp(codice, "2fd847b")==0)
   {
   	XEvent event;
	memset(&event, 0x00, sizeof(event));
	event.type = ButtonPress;
	event.xbutton.button = 1;
	event.xbutton.same_screen = True;
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	event.xbutton.subwindow = event.xbutton.window;
	while(event.xbutton.subwindow)
	{
		event.xbutton.window = event.xbutton.subwindow;
		XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	}
	XSendEvent(display, PointerWindow, True, 0xfff, &event);	
	XFlush(display);	
	usleep(100000);	
	event.type = ButtonRelease;
	event.xbutton.state = 0x100;
	XSendEvent(display, PointerWindow, True, 0xfff, &event);	
	XFlush(display);
   }
   else if (strcmp(codice, "2fd40bf")==0) caricalist(2,display);
   else if (strcmp(codice, "2fdc03f")==0) caricalist(3,display);
   else if (strcmp(codice, "2fd20df")==0) caricalist(4,display);
   else if (strcmp(codice, "2fda05f")==0) caricalist(5,display);
   else if (strcmp(codice, "2fd609f")==0) caricalist(6,display);
   else if (strcmp(codice, "2fde01f")==0) caricalist(7,display);
   else if (strcmp(codice, "2fd10ef")==0) caricalist(8,display);
   else if (strcmp(codice, "2fd906f")==0) caricalist(9,display);
   else if (strcmp(codice, "2fdc23d")==0) tappa();
   
else {
   int tasto=XK_A;  
   if (strcmp(codice, "2fd12ed")==0) tasto=XK_Tab;
   else if (strcmp(codice, "2fd926d")==0) tasto =XK_Return;
   else if (strcmp(codice, "2fd58a7")==0) tasto=XK_Up;
   else if (strcmp(codice, "2fd7887")==0) tasto =XK_Down;
   else if (strcmp(codice, "2fd00ff")==0) tasto = XK_space;
// Get the root window for the current display.
   Window winRoot = XDefaultRootWindow(display);

// Find the window which has the current keyboard focus.
   Window winFocus;
   int    revert;
   XGetInputFocus(display, &winFocus, &revert);
 
// Send a fake key press event to the window.
   XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, tasto, 0);
   XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

// Send a fake key release event to the window.
   event = createKeyEvent(display, winFocus, winRoot, false, tasto, 0);
   XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

       }  
XCloseDisplay(display);
}


void *thtel(void *arg)
{

  printf("\npartito thread\n");
 int fd,i;
	char buf[128];
	struct sockaddr_un addr;
	addr.sun_family=AF_UNIX;
	strcpy(addr.sun_path,"/dev/lircd");
	fd=socket(AF_UNIX,SOCK_STREAM,0);
	if(fd==-1)  {
		perror("socket");
		exit(errno);
	};
	if(connect(fd,(struct sockaddr *)&addr,sizeof(addr))==-1)  {
		perror("connect");
		exit(errno);
	};
	
        char cod[8];
	int lun,j,k;
	for(;;)  {
		bzero(buf,128);
		memset(cod,0,sizeof(cod));
		i=read(fd,buf,128);
		if(i==-1)  {
			perror("read");
			exit(errno);
		};
		if(!i)  exit(0);

		
		j=0;
                k=0;
		lun=strlen(buf);
		for (j=9;j<lun;j++)
				{
					if (buf[j]==' ') break;				
					cod[k]=buf[j];
		
					k=k+1;
				}
		printf("\nCodice:\t%s\nStringa restituita dal driver: \t%s\n",cod,buf);
		elabora(cod);
	}

}





int main( int argc, char *argv[])
{
  int res;
  pthread_t tel_thread;
  res = pthread_create(&tel_thread, NULL, thtel, NULL);
   if (res != 0) {
   	 printf("\nerrore partenza thread");
   	exit(EXIT_FAILURE);
   }
   tastocor=0;
   caricamatrice();
   gtk_init(&argc, &argv);
   window = gtk_window_new(GTK_WINDOW_POPUP);
   gtk_window_set_title(GTK_WINDOW(window), "Prova");
   gtk_window_set_default_size(GTK_WINDOW(window), 105, 105);
   gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
   fixed = gtk_fixed_new();
   gtk_container_add(GTK_CONTAINER(window), fixed);
   gtklist=gtk_list_new();
   gtk_list_set_selection_mode((GtkList *) gtklist, GTK_SELECTION_SINGLE);    
   gtk_container_add(GTK_CONTAINER(window), gtklist);
 
   gtk_widget_show(gtklist);
   int i=0;
   for (i=0; i<N; i++) {
        GtkWidget       *label;
        gchar           *string;   
        sprintf(buffer, "%d", i);
        label=gtk_label_new(buffer);
        list_item=gtk_list_item_new();
        gtk_container_add(GTK_CONTAINER(list_item), label);
        gtk_widget_show(label);
        gtk_container_add(GTK_CONTAINER(gtklist), list_item);
        gtk_widget_show(list_item);
        gtk_label_get(GTK_LABEL(label), &string);
        gtk_object_set_data(GTK_OBJECT(list_item),list_item_data_key,string);
    }
   indice=0;  
   gtk_list_select_item((GtkList *) gtklist,indice);
   gtk_fixed_put(GTK_FIXED(fixed), gtklist, 0, 0);
   gtk_widget_set_size_request(gtklist, 100,100);
 g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
