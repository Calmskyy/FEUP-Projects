package Tetris.Model;

import java.util.Random;
import Tetris.Controller.Piece;

public class JPiece extends Piece {

    /**
     * Constructor.
     * @param width
     */
    public JPiece(int width) {
        super(7, 3, "#0000F1", 90, new int[]{0, 1}, new int[]{0, 0, 1});
        Random rand = new Random();

        int[][] coords = new int[4][2];
        int randX = rand.nextInt(width - 3) + 1;
        coords[0][0] = randX;
        coords[0][1] = 1;
        coords[1][0] = randX;
        coords[1][1] = 0;
        coords[2][0] = randX + 1;
        coords[2][1] = 1;
        coords[3][0] = randX + 2;
        coords[3][1] = 1;

        super.setCoords(coords);
    }

    /**
     * Constructor.
     * @param startX
     * @param startY
     */
    public JPiece(int startX, int startY) {
        super(7, 3, "#0000F1", 90, new int[]{0, 1}, new int[]{0, 0, 1});

        int[][] coords = new int[4][2];
        coords[0][0] = startX;
        coords[0][1] = startY;
        coords[1][0] = startX;
        coords[1][1] = startY - 1;
        coords[2][0] = startX + 1;
        coords[2][1] = startY;
        coords[3][0] = startX + 2;
        coords[3][1] = startY;

        super.setCoords(coords);
    }
}
