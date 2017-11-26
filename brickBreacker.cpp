#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>

bool checkCollision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) 
{
	if ( Ay+Ah < By ){
		return false; 
	}else if ( Ay > By+Bh ) {
		return false;
	}else if ( Ax+Aw < Bx ) {
		return false;
	}else if ( Ax > Bx+Bw ) {
		return false; 
	}
	return true;
}

struct Brick {

	float x; 
	float y;
	float width;
	float height;
	bool alive; //bandera para saber si esta viva o no

};

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
  SDL_WM_SetCaption( "Brick Breaker", NULL );

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

  //For handling with event
  SDL_Event event;

  /////////////////////////////////////////
  /////////////////////////////////////////
  //varibles del rectangulo (jugador)
  float myX = 250; //posicion X de inicio del rectangulo (jugador)
  float myY = 370; //posicion Y de inicio del rectangulo (jugador)
  float width = 80; //ancho del rectangulo
  float height = 20; //largo del rectangulo
  /////////////////////////////////////////
  /////////////////////////////////////////

  //siempre se activa solo una a la vez, es el indicador para saber
  //que boton presiona el jugador y asi conocer hacia donde se debe de
  //dirigir el rectangulo
  bool left = false;
  bool right = false; 

  /////////////////////////////////////////
  /////////////////////////////////////////
  //varibles de la bola
  float ballX = 300; //posicion X de inicio de la bola
  float ballY = 345; //posicion Y de inicio de la bola
  float ballWH = 20; //tamanio de la bola (ancho por altura)
  float vellX = 2.5; //velocidad que se desplaza la bola en X
  float vellY = -2.5; //velocidad que se desplaza la bola en Y
  /////////////////////////////////////////
  /////////////////////////////////////////


  /////////////////////////////////////////
  //creacion de las barras (bricks)
  const static int BRICKS = 45; //cantidad de barras

  Brick bricks[BRICKS];

  for ( int n = 0, x = 4, y = 10; n < BRICKS; n++, x+=66 ) {
      //se estable los limites de la pantalla para que cuando se dibuje
      //las barras no se excedan de la pantalla
      if ( x > 560 ) {
		x = 4;
		y += 25;
	  }
	  
	  //se establecen los valores por defecto de las barras
      bricks[n].x = x;
      bricks[n].y = y;
      bricks[n].width = 60;
      bricks[n].height = 20;
      bricks[n].alive = true;
    }


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
	  if ( event.type == SDL_KEYDOWN ) {
		  //revisa cual boton fue el que se preciono
	      if ( event.key.keysym.sym == SDLK_LEFT ) {
		  left = true;
		}

	      else if ( event.key.keysym.sym == SDLK_RIGHT ) {
		  right = true;
		}
	       
	    }

	  //si se deja de presionar un boton
	  else if ( event.type == SDL_KEYUP ) {
		  //revisa cual se dejo de precionar
	      if ( event.key.keysym.sym == SDLK_LEFT ) {
		  left = false;
		}
	      
	      else if ( event.key.keysym.sym == SDLK_RIGHT ){
		  right = false;
		}
	    }
	}

      if ( left == true ) {
	  myX -= 3;
	}

      if ( right == true ) {
	  myX += 3;
	}

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

      ////////////////////////////////////////////
      //logica de la bola
      ////////////////////////////////////////////
      
      //primero se mueve en el eje x
      ballX += vellX;

	  //revisa todas las barras para verificar si colisiona con alguna
      for ( int n = 0; n < BRICKS; n++ ) {
		  //si la barra esta viva, se revisa si la bola colisiona con la barra
	  if ( bricks[n].alive == true ) {
	      if ( checkCollision(ballX,ballY,ballWH,ballWH,bricks[n].x,bricks[n].y,bricks[n].width, bricks[n].height) == true ) {
			  vellX = -vellX; //efecto de rebote
			  bricks[n].alive = false; //desaparece la barra
			  break;
		}
	    }
	}

	  //se mueve la bola en el eje Y
      ballY += vellY;

	  //se repite la logica de arriba
      for ( int n = 0; n < BRICKS; n++ ) {
	  if ( bricks[n].alive == true ) {
	      if ( checkCollision(ballX,ballY,ballWH,ballWH,bricks[n].x,bricks[n].y,bricks[n].width, bricks[n].height) == true ) {
			  vellY = -vellY;
			  bricks[n].alive = false;
			  break;
		}
	    }
	}


	  //validacion del limite de la pantalla, para que la bola no se salga de la pantalla
      if ( ballX < 0 ) {
	  vellX = -vellX;
	}

      else if ( ballX+ballWH>600 )
	{
	  vellX = -vellX;
	}

      if ( ballY < 0 )
	{
	  vellY = -vellY;
	}
      
      //si la bola toca el piso, el juego se reinicia
      else if ( ballY+ballWH > 400 ) { 
	  //se establecen los valores de inicio
	  myX = 250; 
	  myY = 370; 
	  width = 80; 
	  height = 20;
	  
	  left = false;
	  right = false; 
	  
	  ballX = 300;
	  ballY = 345;
	  ballWH = 20;
	  
	  vellX = 2.5;
	  vellY = -2.5;

	  //revive todas las barras
	  for ( int n = 0; n < BRICKS; n++ ) {
	      bricks[n].alive = true;
	    }
	    
	    
	    //presione enter para continuar
	}

	  //si choca con el rectangulo (jugador), rebota hacia arriba
      if ( checkCollision(ballX,ballY,ballWH,ballWH,myX,myY,width,height) == true )	{
	  vellY = -vellY;
	}
      
      glClear(GL_COLOR_BUFFER_BIT);

      glPushMatrix(); 

      glOrtho(0,600,400,0,-1,1);

      glColor4ub(0,0,0,255); 

      glBegin(GL_QUADS); //dibuja el rectangulo

	  //parametros para dibujar el rectangulo
      glVertex2f(myX,myY); 
      glVertex2f(myX+width,myY);
      glVertex2f(myX+width,myY+height);
      glVertex2f(myX,myY+height);

      glEnd(); //termina de dibujar el rectangulo

      glColor4ub(255,0,0,255);

      glBegin(GL_QUADS); //dibuja de la bola de la misma manera que el rectangulo
      glVertex2f(ballX,ballY);
      glVertex2f(ballX+ballWH,ballY);
      glVertex2f(ballX+ballWH,ballY+ballWH);
      glVertex2f(ballX,ballY+ballWH);
      glEnd();

      glColor4ub(0,0,255,255);

      glBegin(GL_QUADS); //dibuja las barras

      for ( int n = 0; n < BRICKS; n++ ) {
		  //solo se dibujan las barras que esten vivas
	  if ( bricks[n].alive == true ) {
	      //cada 2 barras cambia de color
	      if ( n%2 == 0 ) {
			   glColor4ub(122,0,255,255);
	      }else{
			   glColor4ub(0,0,255,255);
	      }
	      
	      glVertex2f(bricks[n].x,bricks[n].y);
	      glVertex2f(bricks[n].x+bricks[n].width,bricks[n].y);
	      glVertex2f(bricks[n].x+bricks[n].width,bricks[n].y+bricks[n].height);
	      glVertex2f(bricks[n].x,bricks[n].y+bricks[n].height);
	    }
	}

      glEnd();

      glPopMatrix();

      SDL_GL_SwapBuffers();

      SDL_Delay(1); 
    } 

  SDL_Quit();

  return 0;
}
