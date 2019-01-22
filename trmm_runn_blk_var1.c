
/* Copyright 2018 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Pejmon Rahimi
                  
                                                                     */

#include "FLAME.h"

int trmm_blk_var1( FLA_Obj B, FLA_Obj U, int nb_alg )
{
  FLA_Obj BL,    BR,       B0,  B1,  B2;

  FLA_Obj UTL,   UTR,      U00, U01, U02, 
          UBL,   UBR,      U10, U11, U12,
                           U20, U21, U22;

  int b;

  FLA_Part_1x2( B,    &BL,  &BR,      0, FLA_RIGHT );

  FLA_Part_2x2( U,    &UTL, &UTR,
                      &UBL, &UBR,     0, 0, FLA_BR );

  while ( FLA_Obj_width( BR ) < FLA_Obj_width( B ) ){

    b = min( FLA_Obj_width( BL ), nb_alg );

    FLA_Repart_1x2_to_1x3( BL,  /**/ BR,        &B0, &B1, /**/ &B2,
                           b, FLA_LEFT );

    FLA_Repart_2x2_to_3x3( UTL, /**/ UTR,       &U00, &U01, /**/ &U02,
                                                &U10, &U11, /**/ &U12,
                        /* ************* */   /* ******************** */
                           UBL, /**/ UBR,       &U20, &U21, /**/ &U22,
                           b, b, FLA_TL );

    /*------------------------------------------------------------*/

    FLA_Ger( FLA_ONE, B1, U12, B2 );
    FLA_Scal( U11, B1 );


    /*------------------------------------------------------------*/

    FLA_Cont_with_1x3_to_1x2( &BL,  /**/ &BR,        B0, /**/ B1, B2,
                              FLA_RIGHT );

    FLA_Cont_with_3x3_to_2x2( &UTL, /**/ &UTR,       U00, /**/ U01, U02,
                            /* ************** */  /* ****************** */
                                                     U10, /**/ U11, U12,
                              &UBL, /**/ &UBR,       U20, /**/ U21, U22,
                              FLA_BR );

  }

  return FLA_SUCCESS;
}