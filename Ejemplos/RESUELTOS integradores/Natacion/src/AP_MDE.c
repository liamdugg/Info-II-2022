/**
*	\file       AP_MDE.c
*	\brief      Maquina/s de Estado
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       29-01-2023 21:05:56
*/
/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_MDE.h"
#include "AP_FuncionesMDE.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/
#define		RESET		0	
//Maquina: Pileta
#define		ESPERANDO		1	// < Maquina: Pileta >
#define		CARRERA		2	// < Maquina: Pileta >

//Maquina: Display_nadando
#define		ESPERANDO		1	// < Maquina: Display_nadando >
#define		DISPLAY_ON		2	// < Maquina: Display_nadando >

/************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static int Pileta ( int );
static int Display_nadando ( int );

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
int Inicio ;		//
int Pulsador ;		//
int Display_Carrera ;		//
int Timer_2s ;		//
int llegada ;		//
int fin_carrera ;		//

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      static int Pileta ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    29-01-2023 21:05:56
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int Pileta ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :

            Estado = ESPERANDO;

            break;

        case ESPERANDO :
            if ( Inicio == 1 )
            {
                f_Iniciar_Timers();
                Display_Carrera = 1;

                Estado = CARRERA;
            }

            break;

        case CARRERA :
            if ( Pulsador == 1 )
            {
                f_Pausar_sistema();

                Estado = ESPERANDO;
            }

            if ( llegada == 1 )
            {
                llegada = 0;
                f_Envio_trama();
                f_Deneter_Timer();

                Estado = CARRERA;
            }

            if ( fin_carrera == 1 )
            {

                Estado = ESPERANDO;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

/**
*	\fn      static int Display_nadando ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    29-01-2023 21:05:56
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int Display_nadando ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :

            Estado = ESPERANDO;

            break;

        case ESPERANDO :
            if ( Display_Carrera == 1 )
            {
                f_Display_Corredor();
                f_Iniciar_Timer_2s();

                Estado = DISPLAY_ON;
            }

            break;

        case DISPLAY_ON :
            if ( Timer_2s == 0 )
            {
                f_Display_Corredor();
                f_Iniciar_Timer_2s();

                Estado = DISPLAY_ON;
            }

            if ( Pulsador == 1 )
            {
                f_Pausar_sistema();

                Estado = ESPERANDO;
            }

            if ( fin_carrera == 1 )
            {

                Estado = ESPERANDO;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void MaquinaDeEstados ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    29-01-2023 21:05:56
*   \param   void
*	\return  void
*/
void MaquinaDeEstados ( void )
{
    static int estados_Pileta = RESET;
    static int estados_Display_nadando = RESET;

    // Coloque su codigo aqui

    estados_Pileta = Pileta( estados_Pileta );
    estados_Display_nadando = Display_nadando( estados_Display_nadando );


    return ;
}

