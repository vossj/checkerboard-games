#ifndef __CHESSOBJS_H__
#define __CHESSOBJS_H__

#include <ctype.h>
#include <iostream>
#include <string>
#include <vector>

namespace Chess
{
    /* Enumeration of all possible chess piece types.
       
       Pieces properties are represented as binary flags within a
       integer type byte in order to minimize storage / maximize
       copying speed.
    */
    typedef unsigned char ProtoPiece;
    namespace PieceFlags {
	// Binary flags used to construct individual pieces.
	const ProtoPiece NONE = 0;
	const ProtoPiece PAWN = 1;
	const ProtoPiece KNIGHT = 2;
	const ProtoPiece BISHOP = 3;
	const ProtoPiece ROOK = 4;
	const ProtoPiece QUEEN = 5;
	const ProtoPiece KING = 6;
	const ProtoPiece TYPE_MASK = 7;
	const ProtoPiece TYPE_MAX = 6; // Maximum value assigned to
					  // describe a piece type.
	const ProtoPiece BLACK = 1 << 3;
	const ProtoPiece WHITE = 1 << 4;
	const ProtoPiece COLOR_MASK = BLACK | WHITE;
    };

    class Piece
    {
    public:
	Piece();
	// Creates an empty (NONE) piece
	
	Piece(ProtoPiece p);
	// Creates a piece of the prototype p.
	
	bool IsValid();
	/* Tests an returns whether the piece givin is a validly
	 * defined piece.  The NONE piece, and all listed defined
	 * Pieces in the Pieces namespace are valid, and no other
	 * pieces are considered valid. */

	operator ProtoPiece() const;

	Piece & operator=(const ProtoPiece & p);
	
	/* Tests for piece properties (type and color).  To check if a
	 * piece is a particular piece, then instead of checking
	 * particular properties of the piece, one may directly test
	 * equality with one of the pieces as enumerated below this
	 * class definition. */
	inline bool IsWhite() const
	    { return Value & PieceFlags::WHITE; }
	inline bool IsBlack() const
	    { return Value & PieceFlags::BLACK; }
	inline bool IsPawn() const
	    { return (Value & PieceFlags::TYPE_MASK) == PieceFlags::PAWN; }
	inline bool IsKnight() const
	    { return (Value & PieceFlags::TYPE_MASK) == PieceFlags::KNIGHT; }
	inline bool IsBishop() const
	    { return (Value & PieceFlags::TYPE_MASK) == PieceFlags::BISHOP; }
	inline bool IsRook() const
	    { return (Value & PieceFlags::TYPE_MASK) == PieceFlags::ROOK; }
	inline bool IsKing() const
	    { return (Value & PieceFlags::TYPE_MASK) == PieceFlags::KING; }
	inline bool IsQueen() const
	    { return (Value & PieceFlags::TYPE_MASK) == PieceFlags::QUEEN; }
    private:
	ProtoPiece Value;
    };
    
    namespace Pieces {
	// Declarations of actual pieces
	const Piece NONE = PieceFlags::NONE;
	const Piece WHITE_PAWN = PieceFlags::PAWN | PieceFlags::WHITE;
	const Piece BLACK_PAWN = PieceFlags::PAWN | PieceFlags::BLACK;
	const Piece WHITE_KNIGHT = PieceFlags::KNIGHT | PieceFlags::WHITE;
	const Piece BLACK_KNIGHT = PieceFlags::KNIGHT | PieceFlags::BLACK;
	const Piece WHITE_BISHOP = PieceFlags::BISHOP | PieceFlags::WHITE;
	const Piece BLACK_BISHOP = PieceFlags::BISHOP | PieceFlags::BLACK;
	const Piece WHITE_ROOK = PieceFlags::ROOK | PieceFlags::WHITE;
	const Piece BLACK_ROOK = PieceFlags::ROOK | PieceFlags::BLACK;
	const Piece WHITE_QUEEN = PieceFlags::QUEEN | PieceFlags::WHITE;
	const Piece BLACK_QUEEN = PieceFlags::QUEEN | PieceFlags::BLACK;
	const Piece WHITE_KING = PieceFlags::KING | PieceFlags::WHITE;
	const Piece BLACK_KING = PieceFlags::KING | PieceFlags::BLACK;
    };

    class Move
    {
    public:
	Move();
	/* Creates a default empty move.

	   Defaults: not a castling move, not an en passant, and no
	   pieces captured or squares specified.
	*/
	
	bool ShortCastle, LongCastle, EnPassant;
	std::string StartSquare, EndSquare;
	/* Move start and end squares are given by a two character
	 * sequence corresponding to the algebraic notation location
	 * of the square.  That is, the ranks of the board are 1-8
	 * with 1 being white's home row.  The files are given by
	 * letters a-h (lower case preferred) with a being the
	 * queenside rook's file. */
	
	Piece CapturedPiece;            // Use to specify any piece captured
	Piece Promotion;                // If a pawn is promoted, use
					// to specify what piece the
					// pawn is promoted to.
    };

    class Position
    {
    public:
	// MEMBER FUNCTIONS -----------------------------------------------
	void ExecuteMove( const Move & m );

	void GenLegalMoves(std::vector< Move > & Moves);
	/* Overwrites the vector Moves with a list of the legal moves
	   for the current position.

	   Note: Behaviour is not standardly defined when more than
	   the proper number of kings of a particular color is on the
	   board.  When too few kings are on the board, then moves are
	   still generated as if the position were legal.
	*/
	
        // Pull properly formatted rank or file from a coordinate
	static char GetRank( const std::string & coord ) { return coord[1]; }
	static char GetFile( const std::string & coord )
	    { return tolower(coord[0]); }
	
	Piece & operator[]( const std::string & coord );
	const Piece operator[]( const std::string & coord ) const;
	/* Access to the piece at the boord location given by coord.
	   All coordinates are assumed to be in algebraic notation. */

	Position();
	/* Initializes to an empty position.  As the position is empty,
	   castling validity is assumed false by default. */

	void Print( std::ostream & out ) const;

	void RetractMove( const Move & m );
	/* Undo the move m.

	   WARNING: Does not keep track of EnPessante legality or the 1st
	   moves of rooks and kings.  These require additional game state
	   information than is provided here. */
	
	
	void SetToEmptyPosition();
	
	void SetToInitialPosition();
	/* Sets the position to the games initial position */
	
	static bool ValidCoordinate( const std::string & coord );
	/* Returns whether a coordinate is a valid location on a chess
	 * board.  Coordinates should be compatible with algebraic
	 * chess notation.
	 */

	// PUBLICALLY ACCESSIBLE MEMBER VARIABLES -------------------------
	
	// Information required to keep track of special moves
	bool WKMoved, BKMoved;    /* Keep track of whether either the white
				     or black king has moved during the game. */
	bool a1RMoved, h1RMoved, a8RMoved, h8RMoved;
	/* Keep track of which rooks have moved during the game. */
	std::string EPPLocale;    /* Store the location of a pawn which on the 
				     prior ply/move has moved 2 spots and is 
				     thus potentially susceptible to en 
				     passante.  If no such move, then this 
				     should be empty. */
	bool WhiteToMove;

	
    protected:
	Piece Board[8][8];        // Actual board	
    };


    std::ostream & operator<<(std::ostream & out, const Position & p);
    /* Prints the chess position p to the output stream out. */
}

#endif
