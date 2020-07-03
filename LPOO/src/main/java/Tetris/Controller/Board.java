package Tetris.Controller;

public class Board {
    private int height;
    private int width;
    private int[][] storedBlocks;

    /**
     * Constructor.
     * @param width
     * @param height
     */
    public Board(int width, int height) {
        this.height = height;
        this.width = width;
        this.storedBlocks = new int[width][height];
    }

    /**
     * Get functions.
     */
    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public int[][] getStoredBlocks() {
        return storedBlocks;
    }

    /**
     * Set functions
     */
    public void setStoredBlocks(int[][] storedBlocks) {
        this.storedBlocks = storedBlocks;
    }

    /**
     *
     * @return
     */
    public int clearLine() {

        int flag = 1;
        int height = -5;
        for (int j = this.height - 1; j > 0; j--) {
            height = j;
            flag = 1;

            for (int i = 1; i < width; i++) {
                if (storedBlocks[i][j] == 0)
                    flag = 0;
            }

            if (flag == 1)
                break;
        }

        if (height == -5)
            return 2;

        if (flag == 1) {
            for (int i = 1; i < width; i++)
                storedBlocks[i][height] = 0;

            for (int i = 1; i < width; i++) {
                for (int j = height; j > 0; j--)
                    storedBlocks[i][j] = storedBlocks[i][j - 1];
            }
        }
        return flag;
    }

    /**
     *
     * @return
     */
    public boolean gameOverCheck () {
        boolean end = false;
        for (int i = 0; i < width; i++) {
            if (storedBlocks[i][0] != 0) {
                end = true;
                break;
            }
        }
        return end;
    }
}
