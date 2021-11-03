#include "ADRC.h"

int8_t sign( float x ){
	if( x < 0 ) return -1;
	else if( x == 0 ) return 0;
	else return 1;
}

float ADRC_PROCEDURE( ADRC_Param *ADRC, int16_t Target ){
	
	//*****************TD******************//
	TD( ADRC, Target );
	//*************************************//
	
	//****************NLSEF****************//
	ADRC->e1 = ADRC->x1 - ADRC->z1;
	ADRC->e2 = ADRC->x2 - ADRC->z2;
	ADRC->u0 = ADRC->Kp * ADRC->e1 + ADRC->Kd * ADRC->e2;
	//*************************************//
	
	ADRC->output = ADRC->u0 - ADRC->z3 / ADRC->b;    //u
	
	ESO( ADRC );
	
	return ADRC->output;
	
}

float fst( float v1, float x2 ){
	
	static float z;
	static float a0;
	static float a;
	static float f;
	
	z	= (float)v1 + (float)h * (float)x2;
  a0 = sqrt( pow( d, 2 ) + 8 * r * fabs( z ) );
	
	if( fabs( z ) <= d0 ){
		a = (float)x2 + (float)z / (float)h;
	}
	else{
		a = x2 + ( a0 - d ) / 2;
	}
	
	if( fabs( a ) <= d ){
		f = ( ( -r ) * a / ( r * (float)h ) );
	}
	else{
		f = ( -r ) * sign(a);
	}
	
	return f;
	
}

void TD( ADRC_Param *ADRC, int16_t Target ){
	
	ADRC->x1 = ADRC->x1 + (float)T * ADRC->x2;
	ADRC->x2 = ADRC->x2 + (float)T * fst( ADRC->x1 - Target, ADRC->x2 );
	
}

void ESO( ADRC_Param *ADRC ){
	
	int16_t speed = GetMotorData( ADRC->MotorSerialNumber, false ).speed;
	ADRC->e = ADRC->z1 - speed;
	ADRC->z1 = ADRC->z1 + (float)T * ( ADRC->z2 - 3.0f * ADRC->w0 * ADRC->e );
	ADRC->z2 = ADRC->z2 + T * ( ADRC->z3 - 3.0f * pow( ADRC->w0, 2 ) * ADRC->e + ADRC->b * ADRC->output );
	ADRC->z3 = ADRC->z3 + T * pow( ADRC->w0, 3 ) * ADRC->e;
	
}

//需要先令ADRC结构体等于ADRC_DEFAULT
void ADRC_Init( ADRC_Param *ADRC, uint16_t W0, float b, float kp, float kd, uint8_t Motor_Number ){
	
	ADRC->w0 = W0;
	ADRC->b = b;
	ADRC->Kp = kp;
	ADRC->Kd = kd;
	ADRC->MotorSerialNumber = Motor_Number;
	
}


