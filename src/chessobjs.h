#ifndef __CHESSOBJS_H__
#define __CHESSOBJS_H__

#include <vector>
#include <iostream>
#include <string>

namespace Chess
{
    /* Enumeration of all possible chess piece types.
       
       Pieces properties are represented as binary flags within a
       integer type byte in order to minimize storage / maximize
       copying speed.
    */
    typedef unsigned char Piece;

    namespace PieceFlags {
	// Binary flags used to construct individual pieces.
	const Piece NONE = 0;
	const Piece PAWN = 1;
	const Piece KNIGHT = 1 << 1;
	const Piece BISHOP = 1 << 2;
	const Piece ROOK = 1 << 3;
	const Piece QUEEN = 1 << 4;
	const Piece KING = 1 << 5;
	const Piece BLACK = 1 << 6; // white when this flag is off.
    };

    namespace Pieces {
	// Declarations of actual pieces
	const Piece NONE = 0;
	const Piece WHITE_PAWN = PieceFlags::PAWN;
	const Piece BLACK_PAWN = PieceFlags::PAWN | PieceFlags::BLACK;
	const Piece WHITE_KNIGHT = PieceFlags::KNIGHT;
	const Piece BLACK_KNIGHT = PieceFlags::KNIGHT | PieceFlags::BLACK;
	const Piece WHITE_BISHOP = PieceFlags::BISHOP;
	const Piece BLACK_BISHOP = PieceFlags::BISHOP | PieceFlags::BLACK;
	const Piece WHITE_ROOK = PieceFlags::ROOK;
	const Piece BLACK_ROOK = PieceFlags::ROOK | PieceFlags::BLACK;
	const Piece WHITE_QUEEN = PieceFlags::QUEEN;
	const Piece BLACK_QUEEN = PieceFlags::QUEEN | PieceFlags::BLACK;
	const Piece WHITE_KING = PieceFlags::KING;
	const Piece BLACK_KING = PieceFlags::KING | PieceFlags::BLACK;
    };

    class Move
    {
    public:
	Move();
	bool ShortCastle, LongCastle, EnPassant;
	std::string StartSquare, EndSquare;
	Piece CapturedPiece, Promotion;
    };

    class Position
    {
    public:
	Position();
	/* Initializes to an empty position.  As the position is empty,
	   castling validity is assumed false by default. */
	
	void Print( std::ostream & out ) const;
	
	Piece & operator[]( const std::string & coord );
	const Piece operator[]( const std::string & coord ) const;
	/* Access to the piece at the boord location given by coord.
	   All coordinates are assumed to be in algebraic notation. */
	    
	static bool ValidCoordinate( const std::string & coord );
	/* Returns whether a coordinate is a valid location on a chess
	 * board.  Coordinates should be compatible with algebraic
	 * chess notation.
	 */
	
    protected:	
	Piece Board[8][8];
	
    };


    std::ostream & operator<<(std::ostream & out, const Position & p);
    /* Prints the chess position p to the output stream out. */
}

#endif
