#include <vector>

namespace CheckerBoard
{
    // Enumeration of piece types (as flags within a binary decomposition of
    // integers)
    typedef char Piece;
        
    // Each piece is represented by an integer with the following 
    namespace PieceFlags {
        // Binary mask flags for piece properties
        const Piece NONE = 0;
        const Piece OCCUPIED = 1;
        const Piece KING = 1 << 1;
        const Piece LIGHT_PIECE = 1 << 2;
        const Piece DARK_PIECE = 1 << 3;
    }

    namespace Pieces {
        // Piece declarations
        const Piece NONE = 0;
        const Piece LIGHT_STANDARD =
            PieceFlags::OCCUPIED & PieceFlags::LIGHT_PIECE;
        const Piece LIGHT_KING =
            PieceFlags::LIGHT_STANDARD & PieceFlags::KING;
        const Piece DARK_STANDARD =
            PieceFlags::OCCUPIED & PieceFlags::DARK_PIECE;
        const Piece DARK_KING =
            PieceFlags::DARK_STANDARD & PieceFlags::KING;
    }
    
    /* Standard 8 x 8 checker board for playing English Draughts.  It consists
     * of 32 playable squares indexed via the standard locations 1 to 32 for
     * English Draughts notation.
     */
    class CheckerBoard
    {
    public:
        // Creates an empty checkers board
        CheckerBoard();

        // Get and set what piece is in a board location
        Piece SetPiece( Piece p, int loc );
        inline Piece GetPiece( int loc ) const { return Board[loc - 1]; }

        // Test piece properties (without grabbing full piece for equality
        // testing)
        inline bool IsKing( int loc ) const
        { return PieceFlags::KING & GetPiece( loc ); }
        inline bool IsLightPiece( int loc ) const
        { return PieceFlags::LIGHT_PIECE & GetPiece( loc ); }
        inline bool IsDarkPiece( int loc ) const
        { return PieceFlags::DARK_PIECE & GetPiece( loc ); }
        inline bool IsOccupied( int loc ) const
        { return PieceFlags::OCCUPIED & GetPiece( loc ); }

    protected:

        std::vector<Piece> Board;
    };
}



