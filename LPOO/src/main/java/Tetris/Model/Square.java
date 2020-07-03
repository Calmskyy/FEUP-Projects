package Tetris.Model;

import java.util.Random;
import Tetris.Controller.Piece;

public class Square extends Piece {

    /**
     * Constructor.
     * @param width
     */
    public Square(int width){
        super(1, 2, "#FFFF33",0, new int[]{-90, 1}, new int[]{0, -90, 1});
        Random rand = new Random();

        int[][] coords = new int[4][2];
        int randX = rand.nextInt(width - 2) + 1;
        coords[0][0] = randX;
        coords[0][1] = 0;
        coords[1][0] = randX + 1;
        coords[1][1] = 0;
        coords[2][0] = randX;
        coords[2][1] = 1;
        coords[3][0] = randX + 1;
        coords[3][1] = 1;

        super.setCoords(coords);
    }

    /**
     * Constructor.
     * @param startX
     * @param startY
     */
    public Square(int startX, int startY) {
        super(1, 2, "#FFFF33", 0, new int[]{-90, 1}, new int[]{0, -90, 1});

        int[][] coords = new int[4][2];
        coords[0][0] = startX;
        coords[0][1] = startY;
        coords[1][0] = startX + 1;
        coords[1][1] = startY;
        coords[2][0] = startX;
        coords[2][1] = startY + 1;
        coords[3][0] = startX + 1;
        coords[3][1] = startY + 1;

        super.setCoords(coords);
    }
}
