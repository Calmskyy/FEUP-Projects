package Tetris;

import Tetris.Controller.*;
import Tetris.Model.Rectangle;
import Tetris.Model.Square;
import org.junit.Before;
import org.junit.Test;

import java.lang.reflect.Method;
import java.lang.reflect.Field;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertNull;
import static org.junit.Assert.assertFalse;

public class GameTest {
    private Game game;
    private Board board;
    private Piece testPiece;
    private Class gameClass;
    private Method[] methods;

    @Before
    public void createTest() {
        game = new Game("NO DISPLAY");
        board = new Board(11, 22);
        gameClass = game.getClass();
        methods = gameClass.getMethods();
    }

    @Test
    public void resetGameTest() throws Exception{
        Method resetCall = gameClass.getDeclaredMethod("resetGame");
        Method placeCall = gameClass.getDeclaredMethod("placePiece", board.getClass());
        resetCall.setAccessible(true);
        placeCall.setAccessible(true);

        Field pieceField = gameClass.getDeclaredField("piece");
        pieceField.setAccessible(true);

        Field nextPiecesField = gameClass.getDeclaredField("nextPieces");
        nextPiecesField.setAccessible(true);

        Piece[] nextPieces = new Piece[3];
        nextPieces[0] = new Square(board.getWidth());
        nextPieces[1] = new Square(board.getWidth());
        nextPieces[2] = new Square(board.getWidth());

        testPiece = new Rectangle(1, 18);
        nextPiecesField.set(game, nextPieces);
        pieceField.set(game, testPiece);
        placeCall.invoke(game, board);

        testPiece = new Rectangle(5, 18);
        nextPiecesField.set(game, nextPieces);
        pieceField.set(game, testPiece);
        placeCall.invoke(game, board);

        testPiece = new Square(9, 18);
        nextPiecesField.set(game, nextPieces);
        pieceField.set(game, testPiece);
        placeCall.invoke(game, board);

        assertEquals(1300, game.getScore()); // 3 pieces placed (300) + 1 line clear (1000)
        assertEquals(1100, game.getScoreIncrement()); // last play gave 1100 points

        resetCall.invoke(game); // reset both values, alongside others, back to 0 / starting point

        assertEquals(0, game.getScore());
        assertEquals(0, game.getScoreIncrement());
    }

    @Test
    public void highScoresTest() throws Exception{
        Method initializeScoreCall = gameClass.getDeclaredMethod("initializeHighScores");
        Method saveScoreCall = gameClass.getDeclaredMethod("saveHighScore", boolean.class);
        initializeScoreCall.setAccessible(true);
        saveScoreCall.setAccessible(true);

        Field scoreNameField = gameClass.getDeclaredField("highScoreName");
        scoreNameField.setAccessible(true);
        Field scoreField = gameClass.getDeclaredField("score");
        scoreField.setAccessible(true);

        initializeScoreCall.invoke(game);
        saveScoreCall.invoke(game, true);

        assertEquals("PLACEHOLDER 1", game.getHighScoreNames()[0]);
        assertEquals(50000, game.getScores()[0]);

        char[] highScoreName = new char[16];
        for(int i = 0; i < highScoreName.length; i++) {
            highScoreName[i] = ' ';
        }
        highScoreName[0] = 'R';
        highScoreName[1] = 'A';
        highScoreName[2] = 'N';
        highScoreName[3] = 'K';
        highScoreName[4] = ' ';
        highScoreName[5] = '1';

        scoreField.set(game, 65000);
        scoreNameField.set(game, highScoreName);

        saveScoreCall.invoke(game, false);

        assertEquals("RANK 1          ", game.getHighScoreNames()[0]);
        assertEquals(65000, game.getScores()[0]);
        assertEquals("PLACEHOLDER 1", game.getHighScoreNames()[1]);
        assertEquals(50000, game.getScores()[1]);
    }

    @Test
    public void levelTest() throws Exception{
        Method changeLevelCall = gameClass.getDeclaredMethod("changeLevel");
        changeLevelCall.setAccessible(true);

        Field scoreField = gameClass.getDeclaredField("score");
        scoreField.setAccessible(true);

        assertEquals(1, game.getLevel());

        scoreField.set(game, 1000);
        changeLevelCall.invoke(game);
        assertEquals(2, game.getLevel());

        scoreField.set(game, 2000);
        changeLevelCall.invoke(game);
        assertEquals(3, game.getLevel());

        scoreField.set(game, 3000);
        changeLevelCall.invoke(game);
        assertEquals(3, game.getLevel()); // doesn't change level yet, needs another 1000

        scoreField.set(game, 4000);
        changeLevelCall.invoke(game);
        assertEquals(4, game.getLevel());

        scoreField.set(game, 999999);
        changeLevelCall.invoke(game);
        assertEquals(10, game.getLevel());
    }

    @Test
    public void bankTest() throws Exception{
        Method bankSwapCall = gameClass.getDeclaredMethod("bankSwap");
        bankSwapCall.setAccessible(true);

        Field bankSwapField = gameClass.getDeclaredField("bankSwapAvailable");
        Field pieceField = gameClass.getDeclaredField("piece");
        Field nextPiecesField = gameClass.getDeclaredField("nextPieces");
        bankSwapField.setAccessible(true);
        pieceField.setAccessible(true);
        nextPiecesField.setAccessible(true);

        Piece[] nextPieces = new Piece[3];
        nextPieces[0] = new Square(board.getWidth());
        nextPieces[1] = new Square(board.getWidth());
        nextPieces[2] = new Square(board.getWidth());
        nextPiecesField.set(game, nextPieces);

        assertNull(game.getBankPiece());

        testPiece = new Rectangle(board.getWidth());
        pieceField.set(game, testPiece);
        bankSwapCall.invoke(game);

        Piece bankPiece = game.getBankPiece();
        assertEquals(testPiece.getIdentifier(), bankPiece.getIdentifier());

        testPiece = new Square(board.getWidth());
        pieceField.set(game, testPiece);
        bankSwapCall.invoke(game);

        bankPiece = game.getBankPiece();

        boolean numberComparison;
        numberComparison = testPiece.getIdentifier() == bankPiece.getIdentifier();

        assertFalse(numberComparison); // doesn't change, because bank swap isn't available

        Piece pieceToSwap = game.getPiece();
        bankSwapField.set(game, true); // second swap attempt should be successful now
        bankSwapCall.invoke(game);

        assertEquals(bankPiece.getIdentifier(), game.getPiece().getIdentifier());
        assertEquals(pieceToSwap.getIdentifier(), game.getBankPiece().getIdentifier());
    }
}
