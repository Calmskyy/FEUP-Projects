package Tetris.Model;

import java.util.Random;
import Tetris.Controller.Piece;

public class SPiece extends Piece {

    /**
     * Constructor.
     * @param width
     */
    public SPiece(int width){
        super(4, 3, "#00F100", 0, new int[]{0, 90}, new int[]{0, 90, 0});
        Random rand = new Random();

        int[][] coords = new int[4][2];
        int randX = rand.nextInt(width - 3) + 1;
        coords[0][0] = randX;
        coords[0][1] = 1;
        coords[1][0] = randX + 1;
        coords[1][1] = 1;
        coords[2][0] = randX + 1;
        coords[2][1] = 0;
        coords[3][0] = randX + 2;
        coords[3][1] = 0;

        super.setCoords(coords);
    }

    /**
     * Constructor.
     * @param startX
     * @param startY
     */
    public SPiece(int startX, int startY) {
        super(4, 3, "#00F100", 0, new int[]{0, 90}, new int[]{0, 90, 0});

        int[][] coords = new int[4][2];
        coords[0][0] = startX;
        coords[0][1] = startY;
        coords[1][0] = startX + 1;
        coords[1][1] = startY;
        coords[2][0] = startX + 1;
        coords[2][1] = startY - 1;
        coords[3][0] = startX + 2;
        coords[3][1] = startY - 1;

        super.setCoords(coords);
    }
}