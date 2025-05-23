#ifndef BOARD_H
#define BOARD_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include "piece.h"
#include "bot.h"
#include "zobrist.h"
#include "display.h"
#include "bitboards.h"

struct info {
	int pmSq;
	int epSq;
	int pieceMoved;
	int prevOnMoveTo;
	int halfMoveClock;
	unsigned long zobrist;
};

class Board {
	
	friend int search(Board& b);
	friend int alphaBeta(Board& b, int alpha, int beta, int depthLeft, int ext);
	
	public:
		
		Board();
		Board(std::string FEN);
		void initializeVars();
		void emptyBoard();
		void botMove();
		void placePiece(unsigned int p, unsigned int sq);
		void placePiecesDefault();	
		void placePieces(std::string FEN);	
		void initializePieces();
		void initializeZobrist();
		void initializeBitboards();
		void handleInput(int& mF, int& mT, SDL_Event* e);
		void setSquarePositions();
		void setPiecesOnSquares();
		void changeTurn();
		void undoMove();
		void restart();
		void updateDisplay(const int& mF, const int& mT);
		void zobristXorSide() { zobrist.key ^= zobrist.side; };
		//ACCESSORS
		int getMoveFrom() const { return moveFrom; };
		int getMoveTo() const { return moveTo; };
		int getPly() const { return ply; };
		bool getSide() const { return side; };
		int getSideInCheck() const { return sideInCheck; };
		int getSideInCheckmate() const { return sideInCheckmate; };
		int getCastling() const { return castling; };
		int getWhiteMaterial() const { return whiteMaterial; };
		int getBlackMaterial() const { return blackMaterial; };
		int getFromMoveList(bool s, int i) const;
		int getMoveListSize(bool s) const;
		int getEpSq(int i) const;
		int getPmSq(int i) const;
		int getMoveMade(int i) const;
		int getLastMove() const;
		int getNumMovesMade() const;
		int getPrevOnMoveTo(int i) const;
		int getPieceMoved(int i) const;
		std::string getFEN();
		bool getWhiteIsBot() const { return whiteIsBot; };
		bool getBlackIsBot() const { return blackIsBot; };
		bool getFlipped() const { return flipped; };
		unsigned long getZobrist() const { return zobrist.key; };
		
		void setMove(int mF, int mT) { moveFrom = mF; moveTo = mT; };
		void setPly(int newPly) { ply = newPly; };
		void setSide(bool newSide) { side = newSide; };
		void setCastling(int c) { castling = c; };
		void setSideInCheck(int i) { sideInCheck = i; };
		void setSideInCheckmate(int i) { sideInCheckmate = i; };
		void addToMovelist(bool s, int v);
		void clearMoveList(bool s);
		void setWhiteIsBot(bool b) { whiteIsBot = b; };
		void setBlackIsBot(bool b) { blackIsBot = b; };
		void flipBoard() { flipped = 1 - flipped; };
		
		int& operator [](const int index);
		const int& operator [](const int index) const;
	
		void movePiece();
		void movePiece(int mF, int mT);
		void unmovePiece();
		void unmovePiece(int mF, int mT);
	
		bool legalMove(int mF, int mT, bool s, bool v = false);
		bool putSelfInCheck(int mF, int mT, bool s);
		bool validateMove(int mF, int mT, bool s);
		bool validatePawnMove(int mF, int mT, bool s) const;
		bool validateHozMove(int mF, int mT) const;
		bool validateDiagMove(int mF, int mT) const;
		bool validateKnightMove(int mF, int mT) const;
		bool validateKingMove(int mF, int mT, bool s);
		bool checkCheck(bool s);
		bool checkCheck(bool s, std::vector<int>& moveList);
		bool inCheck(bool s) const;
		bool canCastle(int dir, bool s);
		int drawCheck() const;

		int perft(int depth);
		void getCaptures(bool s, std::vector<int>& moveList);
		void sortCaptures(std::vector<int>& moveList);
		void sortNonCaptures(std::vector<int>& moveList);
		void getNonCaptures(bool s, std::vector<int>& moveList);
		void removeNonCaptures(bool s, std::vector<int>& moveList);
		void cleanMoveList(bool s);
		void cleanMoveList(bool s, std::vector<int>& moveList);
		void clearMovelist(std::vector<int>& moveList);
	
		void generateCaptures(bool s, std::vector<int>& moveList);
		void generateCapturePieceMoveLists(bool s);
		void generateCapturePieceMoveListFor(int p);
		void generateHozCaptures(int p, int& counter);
		void generateDiagCaptures(int p, int& counter);
		void generateKnightCaptures(int p, int& counter);
		void generateKingCaptures(int p, int& counter);
		void generatePawnCaptures(int p, int& counter);
	
		int getNonOrderedAllLegalMoves(bool s, std::vector<int>& moveList);
		void genOrderedMoveList();
		void genOrderedMoveList(bool s, std::vector<int>& moveList);
		void genNonOrderedMoveList(bool s, std::vector<int>& moveList);
		void generatePieceMoveLists(bool s);
		void generatePieceMoveListFor(int p);
		void generateHozMoves(int p, int& counter);
		void generateDiagMoves(int p, int& counter);
		void generateKnightMoves(int p, int& counter);
		void generateKingMoves(int p, int& counter);
		void generatePawnMoves(int p, int& counter);
		void addPromotions(bool s, std::vector<int>& moveList);

		int eval(bool verbose = false);
	
		Piece piece[32];	

		Bot whiteBot, blackBot; 

		Display display; 	
	private:
		int board120[120], moveFrom, moveTo, ply;
		int whiteMaterial, blackMaterial, castling;
		
		int sideInCheck, sideInCheckmate;
		bool side, whiteCastled, blackCastled;
		bool whiteIsBot, blackIsBot, flipped;
		int whiteBotLevel, blackBotLevel;
		
		Zobrist zobrist;
		std::vector<int> whiteMoveList, blackMoveList;
		std::vector<int> movesMade; 
		std::vector<info> moveInfo;
		Bitboards bb;
};

#endif
