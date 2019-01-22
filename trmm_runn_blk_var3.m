
% Copyright 2018 The University of Texas at Austin
%
% For licensing information see
%                http://www.cs.utexas.edu/users/flame/license.html 
%                                                                                 
% Programmed by: Pejmon Rahimi
%                

function [ B_out ] = trmm_blk_var3( B, U, nb_alg )

  [ BL, BR ] = FLA_Part_1x2( B, ...
                               0, 'FLA_RIGHT' );

  [ UTL, UTR, ...
    UBL, UBR ] = FLA_Part_2x2( U, ...
                               0, 0, 'FLA_BR' );

  while ( size( BR, 2 ) < size( B, 2 ) )

    b = min( size( BL, 2 ), nb_alg );

    [ B0, B1, B2 ]= FLA_Repart_1x2_to_1x3( BL, BR, ...
                                         b, 'FLA_LEFT' );

    [ U00, U01, U02, ...
      U10, U11, U12, ...
      U20, U21, U22 ] = FLA_Repart_2x2_to_3x3( UTL, UTR, ...
                                               UBL, UBR, ...
                                               b, b, 'FLA_TL' );

    %------------------------------------------------------------%

    FLA_Scal( U01, B0 );
    FLA_Ger( FLA_ONE, B0, FLA_ONE, b1 );
    FLA_Ger( FLA_ONE, -b1, u12t, B2 );

    %------------------------------------------------------------%

    [ BL, BR ] = FLA_Cont_with_1x3_to_1x2( B0, B1, B2, ...
                                           'FLA_RIGHT' );

    [ UTL, UTR, ...
      UBL, UBR ] = FLA_Cont_with_3x3_to_2x2( U00, U01, U02, ...
                                             U10, U11, U12, ...
                                             U20, U21, U22, ...
                                             'FLA_BR' );

  end

  B_out = [ BL, BR ];

end
