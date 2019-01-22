
/* Copyright 2018 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Pejmon Rahimi
                  
                                                                     */

#include "FLAME.h"

int trmm_unb_var2( FLA_Obj B, FLA_Obj U )
{
  FLA_Obj BL,    BR,       B0,  b1,  B2;

  FLA_Obj UTL,   UTR,      U00,  u01,       U02, 
          UBL,   UBR,      u10t, upsilon11, u12t,
                           U20,  u21,       U22;

  FLA_Part_1x2( B,    &BL,  &BR,      0, FLA_LEFT );

  FLA_Part_2x2( U,    &UTL, &UTR,
                      &UBL, &UBR,     0, 0, FLA_BR );

  while ( FLA_Obj_width( BL ) < FLA_Obj_width( B ) ){

    FLA_Repart_1x2_to_1x3( BL,  /**/ BR,        &B0, /**/ &b1, &B2,
                           1, FLA_RIGHT );

    FLA_Repart_2x2_to_3x3( UTL, /**/ UTR,       &U00,  &u01,       /**/ &U02,
                                                &u10t, &upsilon11, /**/ &u12t,
                        /* ************* */   /* **************************** */
                           UBL, /**/ UBR,       &U20,  &u21,       /**/ &U22,
                           1, 1, FLA_TL );

    /*------------------------------------------------------------*/

    FLA_Ger( FLA_ONE, B0, u01, b1 );
    FLA_Ger( FLA_ONE, b1, upsilon11, b1 );

    /*------------------------------------------------------------*/

    FLA_Cont_with_1x3_to_1x2( &BL,  /**/ &BR,        B0, b1, /**/ B2,
                              FLA_LEFT );

    FLA_Cont_with_3x3_to_2x2( &UTL, /**/ &UTR,       U00,  /**/ u01,       U02,
                            /* ************** */  /* ************************** */
                                                     u10t, /**/ upsilon11, u12t,
                              &UBL, /**/ &UBR,       U20,  /**/ u21,       U22,
                              FLA_BR );

  }

  return FLA_SUCCESS;
}

