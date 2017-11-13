#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>

int main( int argc, char* args[] )
{
  //inicializacion de SDL
  SDL_Init(SDL_INIT_EVERYTHING);

  //se establece la memoria a usar de OpenGL 
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  //titulo de la ventana
  SDL_WM_SetCaption( "Tron", NULL );

  //tamanio de la ventana
  SDL_SetVideoMode(600,400,32, SDL_OPENGL );

  //color de fondo(blanco)
  glClearColor(1,1,1,1); //RED,GREEN,BLUE,ALPHA

  glViewport(0,0,600,400);

  glShadeModel(GL_SMOOTH);

  //2D rendering
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
 
  glDisable(GL_DEPTH_TEST);

  //bandera del ciclo principal del juego
  bool isRunning = true;
  
  int grid[600][400];
  
  for (int k = 0; k < 600; k++) {
	for (int l = 0; l < 400; l++) {
		grid[k][l] = 0;
	}  
  }
  
  bool left = false;
  bool right = true;
  bool down = false;
  bool up = false;
  
  bool left2 = false;
  bool right2 = true;
  bool down2 = false;
  bool up2 = false;

  //For handling with event
  SDL_Event event;

  /////////////////////////////////////////
  /////////////////////////////////////////
  //varibles del rectangulo (jugador)
  float myX = 250; //posicion X de inicio del rectangulo (jugador)
  float myY = 370; //posicion Y de inicio del rectangulo (jugador)
  float myX2 = 250; //posicion X de inicio del rectangulo (jugador)
  float myY2 = 12; //posicion Y de inicio del rectangulo (jugador)
  float width = 1; //ancho del rectangulo
  float height = 1; //largo del rectangulo
  grid[(int)myX][(int)myY] = 1;
  grid[(int)myX2][(int)myY2] = 1;
  /////////////////////////////////////////
  /////////////////////////////////////////
  int P1X[100000];
  int P1Y[100000];
  int P2X[100000];
  int P2Y[100000];
int i = 0;
int j;
  //ciclo principal del juego
  while ( isRunning ) {
      //eventos
      while ( SDL_PollEvent(&event) ) {
	  //si cierran la venta del juego
	  if ( event.type == SDL_QUIT ) {
	      isRunning = false;
	    }

	  //si se preciona ESC
	  if ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE ) {
	      isRunning = false;
	    }

	  //si se presiona algun boton
	  //if ( event.type == SDL_KEYDOWN ) {
		  //revisa cual boton fue el que se preciono
	    //  if ( event.key.keysym.sym == SDLK_LEFT ) {
		  //left = true;
		//}

	     // else if ( event.key.keysym.sym == SDLK_RIGHT ) {
		  //right = true;
		//}
	       
	    //}

	  //si se deja de presionar un boton
	  //else if ( event.type == SDL_KEYUP ) {
		if ( event.type == SDL_KEYUP ) {
		  //revisa cual se dejo de precionar
	      if ( event.key.keysym.sym == SDLK_LEFT) {
		   if (right == false){
		   left = true;
		   right = false;
		   down = false;
		   up = false;
	      }
		}
	      
	      else if ( event.key.keysym.sym == SDLK_RIGHT ){
			if (left == false){  
		   left = false;
		   right = true;
		   down = false;
		   up = false;
	   }
		}
		else if ( event.key.keysym.sym == SDLK_UP ){
			if (down == false){
		   left = false;
		   right = false;
		   down = false;
		   up = true;
	   }
		}
		else if ( event.key.keysym.sym == SDLK_DOWN ){
			if (up == false){
		   left = false;
		   right = false;
		   down = true;
		   up = false;
	   }
		}
		
		///////////////////////////////////
		//////////////////////////////////
		//segundo jugador
		if ( event.key.keysym.sym == SDLK_a) {
		   if (right2 == false){
		   left2 = true;
		   right2 = false;
		   down2 = false;
		   up2 = false;
	      }
		}
	      
	      else if ( event.key.keysym.sym == SDLK_d ){
			if (left2 == false){  
		   left2 = false;
		   right2 = true;
		   down2 = false;
		   up2 = false;
	   }
		}
		else if ( event.key.keysym.sym == SDLK_w ){
			if (down2 == false){
		   left2 = false;
		   right2 = false;
		   down2 = false;
		   up2 = true;
	   }
		}
		else if ( event.key.keysym.sym == SDLK_s ){
			if (up2 == false){
		   left2 = false;
		   right2 = false;
		   down2 = true;
		   up2 = false;
	   }
		}
		
	    }
	}

     if ( left == true ) {
	  myX -= 1;
	  if (grid[(int)myX][(int)myY]) {
		printf("Ganador Jugador 2\n");
		SDL_Delay(2000);   
		isRunning = false;
      }
	}else if ( right == true ) {
	  myX += 1;
	  if (grid[(int)myX][(int)myY]) {
		printf("Ganador Jugador 2\n");
		SDL_Delay(2000);
		isRunning = false;   
      }
	}else if ( up == true ) {
	  myY -= 1;
	  if (grid[(int)myX][(int)myY]) {
		printf("Ganador Jugador 2\n");
		SDL_Delay(2000);  
		isRunning = false; 
      }
	}else if ( down == true ) {
	  myY += 1;
	  if (grid[(int)myX][(int)myY]) {
		printf("Ganador Jugador 2\n");
		SDL_Delay(2000);  
		isRunning = false; 
      }
	}
	
	/////////////////////////////////
	//SEGUNDO JUGADOR
	/////////////////////////////////
	if ( left2 == true ) {
	  myX2 -= 1;
	  if (grid[(int)myX2][(int)myY2]) {
		printf("Ganador Jugador 1\n");  
		SDL_Delay(2000);   
		isRunning = false;

      }
	}else if ( right2 == true ) {
	  myX2 += 1;
	  if (grid[(int)myX2][(int)myY2]) {
		printf("Ganador Jugador 1\n");  
		SDL_Delay(2000);   
		isRunning = false;

      }
	}else if ( up2 == true ) {
	  myY2 -= 1;
	  if (grid[(int)myX2][(int)myY2]) {
		printf("Ganador Jugador 1\n"); 
		SDL_Delay(2000);   
		isRunning = false;
 
      }
	}else if ( down2 == true ) {
	  myY2 += 1;
	  if (grid[(int)myX2][(int)myY2]) {
		printf("Ganador Jugador 1\n"); 
		SDL_Delay(2000);   
		isRunning = false;
 
      }
	}
	
	if (myX == 0 || myX == 599 || myY == 0 || myY == 400) {
		printf("Ganador Jugador 2\n"); 
		SDL_Delay(2000);   
		isRunning = false;
	}else if (myX2 == 0 || myX2 == 599 || myY2 == 0 || myY2 == 400) {
		printf("Ganador Jugador 1\n"); 
		SDL_Delay(2000);   
		isRunning = false;
	}
	
	
	
	P1X[i] = myX;
	P1Y[i] = myY;
	P2X[i] = myX2;
	P2Y[i] = myY2;

	grid[(int)myX][(int)myY] = 1;
	grid[(int)myX2][(int)myY2] = 1;
	  ////////////////////////////////////////////
	  //logica del rectangulo (jugador)
	  ////////////////////////////////////////////

	  //validacion para que la barra no se salga de la pantalla
      if ( myX < 0 ) {
	  myX = 0;
	}

	  //validacion para que la barra no se salga de la pantalla
      if ( myX+width > 600 ) {
	  myX = 600-width; //Move it back so it only touches the right border
	}

      glClear(GL_COLOR_BUFFER_BIT);

      glPushMatrix(); 

      glOrtho(0,600,400,0,-1,1);

      glColor4ub(0,0,0,255); 
	  
	  j = i;
	  while (j >= 0){
		  glBegin(GL_QUADS); //dibuja el rectangulo

		  //parametros para dibujar el rectangulo
		  glVertex2f(P1X[j],P1Y[j]); 
		  glVertex2f(P1X[j]+1,P1Y[j]);
		  glVertex2f(P1X[j]+1,P1Y[j]+1);
		  glVertex2f(P1X[j],P1Y[j]+1);

		  glEnd();
		  
		  j--; 
      
      }
      
      glColor4ub(0,0,255,255);
      
      j = i;
	  while (j >= 0){
		  glBegin(GL_QUADS); //dibuja el rectangulo

		  //parametros para dibujar el rectangulo
		  glVertex2f(P2X[j],P2Y[j]); 
		  glVertex2f(P2X[j]+1,P2Y[j]);
		  glVertex2f(P2X[j]+1,P2Y[j]+1);
		  glVertex2f(P2X[j],P2Y[j]+1);

		  glEnd();
		  
		  j--; 
      
      }
      
      glPopMatrix();

      SDL_GL_SwapBuffers();

      SDL_Delay(1); 
      i++;
    } 

  SDL_Quit();

  return 0;
}
