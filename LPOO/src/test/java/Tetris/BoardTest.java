package Tetris;

import Tetris.Controller.Board;
import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.*;

public class BoardTest {
    private Board board;
    private int [][] testArray;

    @Before
    public void createTest() {
        board = new Board(11, 22);
        testArray = new int[11][22];
    }

    @Test
    public void verifyAttributesTest() {
        assertEquals(11 ,board.getWidth());
        assertEquals(22 ,board.getHeight());
        int[][] storedBlocks = board.getStoredBlocks();
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 22; j++) {
                assertEquals(testArray[i][j], storedBlocks[i][j]);
            }
        }
    }

    @Test
    public void storedBlockChangeTest() {
        for (int i = 0; i < 11; i++) {
            testArray[i][0] = i;
        }
        board.setStoredBlocks(testArray); // update storedBlocks values

        for (int i = 0; i < 11; i++) {
            assertEquals(testArray[i][0], board.getStoredBlocks()[i][0]);
        }
    }

    @Test
    public void lineClearTest() {
        for (int i = 1; i < board.getWidth(); i++) {
            testArray[i][15] = 1; // fill a line
        }

        testArray[5][10] = 1; // lone square to test drop
        board.setStoredBlocks(testArray);

        board.clearLine();

        for (int i = 0; i < 11; i++) {
            assertEquals(0, board.getStoredBlocks()[i][15]); // check if line cleared
        }
        assertEquals(1, board.getStoredBlocks()[5][11]); // check if lone square dropped after clear
    }

    @Test
    public void gameOverTest() {
        for (int i = 1; i < board.getWidth() - 1; i = i + 2) {
            for (int j = 1; j < board.getHeight(); j++) {
                testArray[i][j] = 1; // fill a line
            }
        }

        board.setStoredBlocks(testArray);

        assertFalse(board.gameOverCheck());

        testArray[5][0] = 1;

        assertTrue(board.gameOverCheck());
    }
}
