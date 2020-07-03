package Tetris;

import Tetris.Controller.Board;
import Tetris.Controller.Piece;
import Tetris.Model.*;
import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;

public class PieceTest {
    private Board board;
    private Piece[] pieces;
    private int[][] testCoords;

    private void setTestCoords(int startX, int startY, String piece) {
        if (piece.equals("Model.SPiece") && startY == 0)
            startY++;
        testCoords[0][0] = startX; //x
        testCoords[0][1] = startY; //y

        if (piece.equals("Model.Square")) {
            testCoords[1][0] = startX + 1; //x
            testCoords[1][1] = startY; //y
            testCoords[2][0] = startX; //x
            testCoords[2][1] = startY + 1; //y
            testCoords[3][0] = startX + 1; //x
            testCoords[3][1] = startY + 1; //y
        }

        if (piece.equals("Model.Rectangle")) {
            testCoords[1][0] = startX + 1; //x
            testCoords[1][1] = startY; //y
            testCoords[2][0] = startX + 2; //x
            testCoords[2][1] = startY; //y
            testCoords[3][0] = startX + 3; //x
            testCoords[3][1] = startY; //y
        }

        if (piece.equals("Model.TPiece")) {
            testCoords[1][0] = startX + 1; //x
            testCoords[1][1] = startY; //y
            testCoords[2][0] = startX + 1; //x
            testCoords[2][1] = startY + 1; //y
            testCoords[3][0] = startX + 2; //x
            testCoords[3][1] = startY; //y
        }

        if (piece.equals("Model.SPiece")) {
            testCoords[1][0] = startX + 1; //x
            testCoords[1][1] = startY; //y
            testCoords[2][0] = startX + 1; //x
            testCoords[2][1] = startY - 1; //y
            testCoords[3][0] = startX + 2; //x
            testCoords[3][1] = startY - 1; //y
        }

        if (piece.equals("Model.ZPiece")) {
            testCoords[1][0] = startX + 1; //x
            testCoords[1][1] = startY; //y
            testCoords[2][0] = startX + 1; //x
            testCoords[2][1] = startY + 1; //y
            testCoords[3][0] = startX + 2; //x
            testCoords[3][1] = startY + 1; //y
        }

        if (piece.equals("Model.LPiece")) {
            testCoords[1][0] = startX; //x
            testCoords[1][1] = startY - 1; //y
            testCoords[2][0] = startX - 1; //x
            testCoords[2][1] = startY; //y
            testCoords[3][0] = startX - 2; //x
            testCoords[3][1] = startY; //y
        }

        if (piece.equals("Model.JPiece")) {
            testCoords[1][0] = startX; //x
            testCoords[1][1] = startY - 1; //y
            testCoords[2][0] = startX + 1; //x
            testCoords[2][1] = startY; //y
            testCoords[3][0] = startX + 2; //x
            testCoords[3][1] = startY; //y
        }
    }

    @Before
    public void createTest() {
        board = new Board(11, 22);
        pieces = new Piece[7];
        testCoords = new int[4][2];
    }

    @Test
    public void moveDownTest() {
        pieces[0] = new Square(5, 5);
        pieces[1] = new Rectangle(5, 5);
        pieces[2] = new TPiece(5, 5);
        pieces[3] = new SPiece(5, 5);
        pieces[4] = new ZPiece(5, 5);
        pieces[5] = new LPiece(5, 5);
        pieces[6] = new JPiece(5, 5);

        pieces[0].moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords");
        pieces[1].moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords");
        pieces[2].moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords");
        pieces[3].moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords");
        pieces[4].moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords");
        pieces[5].moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords");
        pieces[6].moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords");


        setTestCoords(5, 6, "Model.Square");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[0].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[0].getCoords()[i][1]);
        }

        setTestCoords(5, 6, "Model.Rectangle");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[1].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[1].getCoords()[i][1]);
        }

        setTestCoords(5, 6, "Model.TPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[2].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[2].getCoords()[i][1]);
        }

        setTestCoords(5, 6, "Model.SPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[3].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[3].getCoords()[i][1]);
        }

        setTestCoords(5, 6, "Model.ZPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[4].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[4].getCoords()[i][1]);
        }

        setTestCoords(5, 6, "Model.LPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[5].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[5].getCoords()[i][1]);
        }

        setTestCoords(5, 6, "Model.JPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[6].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[6].getCoords()[i][1]);
        }

        pieces[2] = new TPiece(5, 20);
        setTestCoords(5, 20, "Model.TPiece"); // shouldn't move, because of board bounds
        pieces[2].moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[2].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[2].getCoords()[i][1]);
        }

        pieces[3] = new SPiece(5, 5);
        board.getStoredBlocks()[7][5] = 1;
        setTestCoords(5, 5, "Model.SPiece"); // shouldn't move, because of a block in the board
        pieces[3].moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[3].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[3].getCoords()[i][1]);
        }
    }

    @Test
    public void moveUpTest() {
        pieces[0] = new Square(5, 5);
        pieces[1] = new Rectangle(5, 5);
        pieces[2] = new TPiece(5, 5);
        pieces[3] = new SPiece(5, 5);
        pieces[4] = new ZPiece(5, 5);
        pieces[5] = new LPiece(5, 5);
        pieces[6] = new JPiece(5, 5);

        pieces[0].moveUp(board.getStoredBlocks(), "currentCoords");
        pieces[1].moveUp(board.getStoredBlocks(), "currentCoords");
        pieces[2].moveUp(board.getStoredBlocks(), "currentCoords");
        pieces[3].moveUp(board.getStoredBlocks(), "currentCoords");
        pieces[4].moveUp(board.getStoredBlocks(), "currentCoords");
        pieces[5].moveUp(board.getStoredBlocks(), "currentCoords");
        pieces[6].moveUp(board.getStoredBlocks(), "currentCoords");


        setTestCoords(5, 4, "Model.Square");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[0].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[0].getCoords()[i][1]);
        }

        setTestCoords(5, 4, "Model.Rectangle");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[1].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[1].getCoords()[i][1]);
        }

        setTestCoords(5, 4, "Model.TPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[2].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[2].getCoords()[i][1]);
        }

        setTestCoords(5, 4, "Model.SPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[3].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[3].getCoords()[i][1]);
        }

        setTestCoords(5, 4, "Model.ZPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[4].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[4].getCoords()[i][1]);
        }

        setTestCoords(5, 4, "Model.LPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[5].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[5].getCoords()[i][1]);
        }

        setTestCoords(5, 4, "Model.JPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[6].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[6].getCoords()[i][1]);
        }

        pieces[2] = new TPiece(5, 1);
        setTestCoords(5, 1, "Model.TPiece"); // shouldn't move, because of board bounds
        pieces[2].moveUp(board.getStoredBlocks(), "currentCoords");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[2].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[2].getCoords()[i][1]);
        }

        pieces[3] = new SPiece(5, 5);
        board.getStoredBlocks()[5][4] = 1;
        setTestCoords(5, 5, "Model.SPiece"); // shouldn't move, because of a block in the board
        pieces[3].moveUp(board.getStoredBlocks(), "currentCoords");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[3].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[3].getCoords()[i][1]);
        }
    }

    @Test
    public void moveLeftTest() {
        pieces[0] = new Square(5, 5);
        pieces[1] = new Rectangle(5, 5);
        pieces[2] = new TPiece(5, 5);
        pieces[3] = new SPiece(5, 5);
        pieces[4] = new ZPiece(5, 5);
        pieces[5] = new LPiece(5, 5);
        pieces[6] = new JPiece(5, 5);


        pieces[0].moveLeft(board.getStoredBlocks(), "currentCoords");
        pieces[1].moveLeft(board.getStoredBlocks(), "currentCoords");
        pieces[2].moveLeft(board.getStoredBlocks(), "currentCoords");
        pieces[3].moveLeft(board.getStoredBlocks(), "currentCoords");
        pieces[4].moveLeft(board.getStoredBlocks(), "currentCoords");
        pieces[5].moveLeft(board.getStoredBlocks(), "currentCoords");
        pieces[6].moveLeft(board.getStoredBlocks(), "currentCoords");

        setTestCoords(4, 5, "Model.Square");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[0].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[0].getCoords()[i][1]);
        }

        setTestCoords(4, 5, "Model.Rectangle");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[1].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[1].getCoords()[i][1]);
        }

        setTestCoords(4, 5, "Model.TPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[2].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[2].getCoords()[i][1]);
        }

        setTestCoords(4, 5, "Model.SPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[3].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[3].getCoords()[i][1]);
        }

        setTestCoords(4, 5, "Model.ZPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[4].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[4].getCoords()[i][1]);
        }

        setTestCoords(4, 5, "Model.LPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[5].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[5].getCoords()[i][1]);
        }

        setTestCoords(4, 5, "Model.JPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[6].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[6].getCoords()[i][1]);
        }

        pieces[2] = new TPiece(1, 5);
        setTestCoords(1, 5, "Model.TPiece"); // shouldn't move, because of board bounds
        pieces[2].moveLeft(board.getStoredBlocks(), "currentCoords");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[2].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[2].getCoords()[i][1]);
        }

        pieces[3] = new SPiece(5, 5);
        board.getStoredBlocks()[4][5] = 1;
        setTestCoords(5, 5, "Model.SPiece"); // shouldn't move, because of a block in the board
        pieces[3].moveLeft(board.getStoredBlocks(), "currentCoords");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[3].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[3].getCoords()[i][1]);
        }
    }

    @Test
    public void moveRightTest() {
        pieces[0] = new Square(5, 5);
        pieces[1] = new Rectangle(5, 5);
        pieces[2] = new TPiece(5, 5);
        pieces[3] = new SPiece(5, 5);
        pieces[4] = new ZPiece(5, 5);
        pieces[5] = new LPiece(5, 5);
        pieces[6] = new JPiece(5, 5);

        pieces[0].moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");
        pieces[1].moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");
        pieces[2].moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");
        pieces[3].moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");
        pieces[4].moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");
        pieces[5].moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");
        pieces[6].moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");

        setTestCoords(6, 5, "Model.Square");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[0].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[0].getCoords()[i][1]);
        }

        setTestCoords(6, 5, "Model.Rectangle");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[1].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[1].getCoords()[i][1]);
        }

        setTestCoords(6, 5, "Model.TPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[2].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[2].getCoords()[i][1]);
        }

        setTestCoords(6, 5, "Model.SPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[3].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[3].getCoords()[i][1]);
        }

        setTestCoords(6, 5, "Model.ZPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[4].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[4].getCoords()[i][1]);
        }

        setTestCoords(6, 5, "Model.LPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[5].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[5].getCoords()[i][1]);
        }

        setTestCoords(6, 5, "Model.JPiece");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[6].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[6].getCoords()[i][1]);
        }

        pieces[2] = new TPiece(8, 5);
        setTestCoords(8, 5, "Model.TPiece"); // shouldn't move, because of board bounds
        pieces[2].moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[2].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[2].getCoords()[i][1]);
        }

        pieces[3] = new SPiece(5, 5);
        board.getStoredBlocks()[7][5] = 1;
        setTestCoords(5, 5, "Model.SPiece"); // shouldn't move, because of a block in the board
        pieces[3].moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");
        for (int i = 0; i < 4; i++) {
            assertEquals(testCoords[i][0], pieces[3].getCoords()[i][0]);
            assertEquals(testCoords[i][1], pieces[3].getCoords()[i][1]);
        }
    }

    @Test
    public void placeTest() {
        pieces[0] = new Square(2, 16);
        pieces[1] = new Rectangle(2, 12);
        pieces[2] = new TPiece(2, 8);
        pieces[3] = new SPiece(2, 4);
        pieces[4] = new ZPiece(6, 15);
        pieces[5] = new LPiece(6, 10);
        pieces[6] = new JPiece(6, 4);

        int[][] blockStorage = new int[11][22];

        blockStorage[2][16] = 1;
        blockStorage[2][17] = 1;
        blockStorage[3][16] = 1;
        blockStorage[3][17] = 1;

        blockStorage[2][12] = 2;
        blockStorage[3][12] = 2;
        blockStorage[4][12] = 2;
        blockStorage[5][12] = 2;

        blockStorage[2][8] = 3;
        blockStorage[3][8] = 3;
        blockStorage[4][8] = 3;
        blockStorage[3][9] = 3;

        blockStorage[2][4] = 4;
        blockStorage[3][4] = 4;
        blockStorage[3][3] = 4;
        blockStorage[4][3] = 4;

        blockStorage[6][15] = 5;
        blockStorage[7][15] = 5;
        blockStorage[7][16] = 5;
        blockStorage[8][16] = 5;

        blockStorage[6][10] = 6;
        blockStorage[6][9] = 6;
        blockStorage[5][10] = 6;
        blockStorage[4][10] = 6;

        blockStorage[6][4] = 7;
        blockStorage[6][3] = 7;
        blockStorage[7][4] = 7;
        blockStorage[8][4] = 7;

        pieces[0].place(board);
        pieces[1].place(board);
        pieces[2].place(board);
        pieces[3].place(board);
        pieces[4].place(board);
        pieces[5].place(board);
        pieces[6].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }
    }

    @Test
    public void firstFourRotateLeftTest() {
        pieces[0] = new Square(2, 16);
        pieces[1] = new Rectangle(6, 12);
        pieces[2] = new TPiece(4, 8);
        pieces[3] = new SPiece(6, 4);

        pieces[0].rotateLeft(board);
        pieces[1].rotateLeft(board);
        pieces[2].rotateLeft(board);
        pieces[3].rotateLeft(board);

        int[][] blockStorage = new int[11][22];

        blockStorage[2][15] = 1;
        blockStorage[2][16] = 1;
        blockStorage[3][15] = 1;
        blockStorage[3][16] = 1;

        blockStorage[6][12] = 2;
        blockStorage[6][11] = 2;
        blockStorage[6][10] = 2;
        blockStorage[6][9] = 2;

        blockStorage[4][8] = 3;
        blockStorage[4][7] = 3;
        blockStorage[5][7] = 3;
        blockStorage[4][6] = 3;

        blockStorage[6][4] = 4;
        blockStorage[6][3] = 4;
        blockStorage[5][3] = 4;
        blockStorage[5][2] = 4;

        pieces[0].place(board);
        pieces[1].place(board);
        pieces[2].place(board);
        pieces[3].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[0].rotateLeft(board);
        pieces[1].rotateLeft(board);
        pieces[2].rotateLeft(board);
        pieces[3].rotateLeft(board);

        blockStorage[2][15] = 1;
        blockStorage[2][16] = 1;
        blockStorage[1][15] = 1;
        blockStorage[1][16] = 1;

        blockStorage[6][12] = 2;
        blockStorage[5][12] = 2;
        blockStorage[4][12] = 2;
        blockStorage[3][12] = 2;

        blockStorage[4][8] = 3;
        blockStorage[3][8] = 3;
        blockStorage[3][7] = 3;
        blockStorage[2][8] = 3;

        blockStorage[6][4] = 4;
        blockStorage[5][4] = 4;
        blockStorage[5][5] = 4;
        blockStorage[4][5] = 4;

        pieces[0].place(board);
        pieces[1].place(board);
        pieces[2].place(board);
        pieces[3].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }
    }

    @Test
    public void lastThreeRotateLeftTest()  {
        pieces[0] = new ZPiece(5, 15);
        pieces[1] = new LPiece(6, 10);
        pieces[2] = new JPiece(4, 5);

        pieces[0].rotateLeft(board);
        pieces[1].rotateLeft(board);
        pieces[2].rotateLeft(board);

        int[][] blockStorage = new int[11][22];

        blockStorage[5][15] = 5;
        blockStorage[5][14] = 5;
        blockStorage[6][14] = 5;
        blockStorage[6][13] = 5;

        blockStorage[6][10] = 6;
        blockStorage[5][10] = 6;
        blockStorage[6][11] = 6;
        blockStorage[6][12] = 6;

        blockStorage[4][5] = 7;
        blockStorage[3][5] = 7;
        blockStorage[4][4] = 7;
        blockStorage[4][3] = 7;

        pieces[0].place(board);
        pieces[1].place(board);
        pieces[2].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[0].rotateLeft(board);
        pieces[1].rotateLeft(board);
        pieces[2].rotateLeft(board);

        blockStorage[5][15] = 5;
        blockStorage[4][15] = 5;
        blockStorage[4][14] = 5;
        blockStorage[3][14] = 5;

        blockStorage[6][10] = 6;
        blockStorage[6][11] = 6;
        blockStorage[7][10] = 6;
        blockStorage[8][10] = 6;

        blockStorage[4][5] = 7;
        blockStorage[4][6] = 7;
        blockStorage[3][5] = 7;
        blockStorage[2][5] = 7;

        pieces[0].place(board);
        pieces[1].place(board);
        pieces[2].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }
    }

    @Test
    public void firstFourRotateRightTest() {
        pieces[0] = new Square(2, 16);
        pieces[1] = new Rectangle(6, 12);
        pieces[2] = new TPiece(4, 8);
        pieces[3] = new SPiece(6, 4);

        pieces[0].rotateRight(board);
        pieces[1].rotateRight(board);
        pieces[2].rotateRight(board);
        pieces[3].rotateRight(board);

        int[][] blockStorage = new int[11][22];

        blockStorage[2][17] = 1;
        blockStorage[2][16] = 1;
        blockStorage[1][17] = 1;
        blockStorage[1][16] = 1;

        blockStorage[6][12] = 2;
        blockStorage[6][13] = 2;
        blockStorage[6][14] = 2;
        blockStorage[6][15] = 2;

        blockStorage[4][8] = 3;
        blockStorage[4][9] = 3;
        blockStorage[3][9] = 3;
        blockStorage[4][10] = 3;

        blockStorage[6][4] = 4;
        blockStorage[6][5] = 4;
        blockStorage[7][5] = 4;
        blockStorage[7][6] = 4;

        pieces[0].place(board);
        pieces[1].place(board);
        pieces[2].place(board);
        pieces[3].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[0].rotateRight(board);
        pieces[1].rotateRight(board);
        pieces[2].rotateRight(board);
        pieces[3].rotateRight(board);

        blockStorage[2][15] = 1;
        blockStorage[2][16] = 1;
        blockStorage[1][15] = 1;
        blockStorage[1][16] = 1;

        blockStorage[6][12] = 2;
        blockStorage[5][12] = 2;
        blockStorage[4][12] = 2;
        blockStorage[3][12] = 2;

        blockStorage[4][8] = 3;
        blockStorage[3][8] = 3;
        blockStorage[3][7] = 3;
        blockStorage[2][8] = 3;

        blockStorage[6][4] = 4;
        blockStorage[5][4] = 4;
        blockStorage[5][5] = 4;
        blockStorage[4][5] = 4;

        pieces[0].place(board);
        pieces[1].place(board);
        pieces[2].place(board);
        pieces[3].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }
    }

    @Test
    public void lastThreeRotateRightTest(){
        pieces[0] = new ZPiece(5, 15);
        pieces[1] = new LPiece(6, 10);
        pieces[2] = new JPiece(4, 5);
        pieces[0].rotateRight(board);
        pieces[1].rotateRight(board);
        pieces[2].rotateRight(board);

        int[][] blockStorage = new int[11][22];

        blockStorage[5][15] = 5;
        blockStorage[5][16] = 5;
        blockStorage[4][16] = 5;
        blockStorage[4][17] = 5;

        blockStorage[6][10] = 6;
        blockStorage[7][10] = 6;
        blockStorage[6][9] = 6;
        blockStorage[6][8] = 6;

        blockStorage[4][5] = 7;
        blockStorage[5][5] = 7;
        blockStorage[4][6] = 7;
        blockStorage[4][7] = 7;

        pieces[0].place(board);
        pieces[1].place(board);
        pieces[2].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[0].rotateRight(board);
        pieces[1].rotateRight(board);
        pieces[2].rotateRight(board);

        blockStorage[5][15] = 5;
        blockStorage[4][15] = 5;
        blockStorage[4][14] = 5;
        blockStorage[3][14] = 5;

        blockStorage[6][10] = 6;
        blockStorage[6][11] = 6;
        blockStorage[7][10] = 6;
        blockStorage[8][10] = 6;

        blockStorage[4][5] = 7;
        blockStorage[4][6] = 7;
        blockStorage[3][5] = 7;
        blockStorage[2][5] = 7;

        pieces[0].place(board);
        pieces[1].place(board);
        pieces[2].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }
    }

    @Test
    public void rotateCycleTest() {
        pieces[1] = new Rectangle(6, 12);

        int [][] blockStorage = new int[11][22];

        pieces[1].rotateLeft(board);

        blockStorage[6][12] = 2;
        blockStorage[6][11] = 2;
        blockStorage[6][10] = 2;
        blockStorage[6][9] = 2;

        pieces[1].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[1].rotateLeft(board);

        blockStorage[6][12] = 2;
        blockStorage[5][12] = 2;
        blockStorage[4][12] = 2;
        blockStorage[3][12] = 2;

        pieces[1].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[1].rotateLeft(board);

        blockStorage[6][12] = 2;
        blockStorage[6][13] = 2;
        blockStorage[6][14] = 2;
        blockStorage[6][15] = 2;

        pieces[1].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[1].rotateLeft(board);

        blockStorage[6][12] = 2;
        blockStorage[7][12] = 2;
        blockStorage[8][12] = 2;
        blockStorage[9][12] = 2;

        pieces[1].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[1].rotateLeft(board);

        blockStorage[6][12] = 2;
        blockStorage[6][11] = 2;
        blockStorage[6][10] = 2;
        blockStorage[6][9] = 2;

        pieces[1].place(board);

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }
    }

    @Test
    public void rotateBoundsTest() {
        pieces[1] = new Rectangle(6, 2);

        int [][] blockStorage = new int[11][22];

        pieces[1].rotateLeft(board);

        pieces[1].place(board);

        blockStorage[6][1] = 2;
        blockStorage[6][2] = 2;
        blockStorage[6][3] = 2;
        blockStorage[6][4] = 2; // gets moved down 2 blocks, due to the board edge

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        pieces[1] = new Rectangle(3, 8);
        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[1].rotateLeft(board);
        pieces[1].rotateLeft(board);

        pieces[1].place(board);

        blockStorage[1][8] = 2;
        blockStorage[2][8] = 2;
        blockStorage[3][8] = 2;
        blockStorage[4][8] = 2; // gets moved right 1 block, due to the board edge

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        pieces[1] = new Rectangle(4, 21);
        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[1].rotateRight(board);

        pieces[1].place(board);

        blockStorage[4][21] = 2;
        blockStorage[4][20] = 2;
        blockStorage[4][19] = 2;
        blockStorage[4][18] = 2; // gets moved up 3 blocks, due to the board edge

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }

        pieces[1] = new Rectangle(5, 5);
        blockStorage = new int[11][22];
        board = new Board(11, 22);

        pieces[1].rotateLeft(board);
        for (int i = 0; i < 5; i++) {
            pieces[1].moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");
        }

        pieces[1].rotateRight(board);

        pieces[1].place(board);

        blockStorage[10][5] = 2;
        blockStorage[9][5] = 2;
        blockStorage[8][5] = 2;
        blockStorage[7][5] = 2; // gets moved to the left 3 blocks, due to the board edge

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(blockStorage[i][j], board.getStoredBlocks()[i][j]);
            }
        }
    }
}