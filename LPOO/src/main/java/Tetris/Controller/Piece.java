package Tetris.Controller;

public abstract class Piece {

    /**
     * Instance variables.
     */
    private int identifier;
    private int[][] coords;
    private int[][] newCoords = new int [4][2];
    private int length;
    private String hexColor;
    private int secondBlockAngle;
    private int [] thirdBlockAngle;
    private int [] fourthBlockAngle;
    private int rotateStatus;

    /**
     * Constructor.
     * @param identifier
     * @param length
     * @param color
     * @param secondBlock
     * @param thirdBlock
     * @param fourthBlock
     */
    public Piece(int identifier, int length, String color, int secondBlock, int [] thirdBlock, int [] fourthBlock) {
        this.identifier = identifier;
        this.length = length;
        this.hexColor = color;
        this.secondBlockAngle = secondBlock;
        this.thirdBlockAngle = thirdBlock;
        this.fourthBlockAngle = fourthBlock;
        this.rotateStatus = 0;
    }

    /**
     * Get functions
     */
    public int getIdentifier() {
        return identifier;
    }

    public int getLength() {
        return length;
    }

    public int[][] getCoords() {
        return coords;
    }

    public String getHexColor() { return this.hexColor; }

    /**
     * Rotate functions
     * @param board
     */
    public void rotateLeft(Board board) {
        rotateStatus++;

        if (rotateStatus == 4)
            rotateStatus = 0;

        secondBlockAngle += 90;
        thirdBlockAngle[0] += 90;
        thirdBlockAngle[1] += 90;
        fourthBlockAngle[0] += 90;
        fourthBlockAngle[1] += 90;
        fourthBlockAngle[2] += 90;

        if (secondBlockAngle >= 360)
            secondBlockAngle -= 360;

        if (thirdBlockAngle[0] >= 360)
            thirdBlockAngle[0] -= 360;
        if (thirdBlockAngle[1] >= 360)
            thirdBlockAngle[1] -= 360;

        if (fourthBlockAngle[0] >= 360)
            fourthBlockAngle[0] -= 360;
        if (fourthBlockAngle[1] >= 360)
            fourthBlockAngle[1] -= 360;
        if (fourthBlockAngle[2] >= 360)
            fourthBlockAngle[2] -= 360;

        updateCoords(board, "left");
    }

    public void rotateRight(Board board) {
        rotateStatus--;

        if (rotateStatus == -1)
            rotateStatus = 3;

        secondBlockAngle -= 90;
        thirdBlockAngle[0] -= 90;
        thirdBlockAngle[1] -= 90;
        fourthBlockAngle[0] -= 90;
        fourthBlockAngle[1] -= 90;
        fourthBlockAngle[2] -= 90;

        if (secondBlockAngle <= -360)
            secondBlockAngle += 360;

        if (thirdBlockAngle[0] <= -360)
            thirdBlockAngle[0] += 360;
        if (thirdBlockAngle[1] <= -360)
            thirdBlockAngle[1] += 360;

        if (fourthBlockAngle[0] <= -360)
            fourthBlockAngle[0] += 360;
        if (fourthBlockAngle[1] <= -360)
            fourthBlockAngle[1] += 360;
        if (fourthBlockAngle[2] <= -360)
            fourthBlockAngle[2] += 360;

        updateCoords(board, "right");
    }

    private void revertRotateStatus(String rotate) {
        if (rotate.equals("left")) {
            rotateStatus++;

            if (rotateStatus == 4)
                rotateStatus = 0;
        }
        else if (rotate.equals("right")) {
            rotateStatus--;

            if (rotateStatus == -1)
                rotateStatus = 3;
        }
    }

    /**
     *
     * @param blockIndex
     * @param angle
     */
    private void changeCoords(int blockIndex, int angle) {
        if (angle == 0) {
            newCoords[blockIndex][0] = newCoords[blockIndex][0] + 1;
            newCoords[blockIndex][1] = newCoords[blockIndex][1];
        }
        else if (angle == 90 || angle == -270) {
            newCoords[blockIndex][0] = newCoords[blockIndex][0];
            newCoords[blockIndex][1] = newCoords[blockIndex][1] - 1;
        }
        else if (angle == 180 || angle == -180) {
            newCoords[blockIndex][0] = newCoords[blockIndex][0] - 1;
            newCoords[blockIndex][1] = newCoords[blockIndex][1];
        }
        else if (angle == 270 || angle == -90) {
            newCoords[blockIndex][0] = newCoords[blockIndex][0];
            newCoords[blockIndex][1] = newCoords[blockIndex][1] + 1;
        }
    }

    /**
     *
     */
    private void checkBoardBoundsRight(int width) {
        for (int i = 0; i < 4; i++) {
            if (newCoords[i][0] > (width - 1)) {
                newCoords[0][0] = newCoords[0][0] - 1;
                newCoords[1][0] = newCoords[1][0] - 1;
                newCoords[2][0] = newCoords[2][0] - 1;
                newCoords[3][0] = newCoords[3][0] - 1;
                break;
            }
        }
    }

    private void checkBoardBoundsLeft() {
        for (int i = 0; i < 4; i++) {
            if (newCoords[i][0] < 1) {
                newCoords[0][0] = newCoords[0][0] + 1;
                newCoords[1][0] = newCoords[1][0] + 1;
                newCoords[2][0] = newCoords[2][0] + 1;
                newCoords[3][0] = newCoords[3][0] + 1;
                break;
            }
        }
    }

    private void checkBoardBoundsDown(int height) {
        for (int i = 0; i < 4; i++) {
            if (newCoords[i][1] > (height - 1)) {
                newCoords[0][1] = newCoords[0][1] - 1;
                newCoords[1][1] = newCoords[1][1] - 1;
                newCoords[2][1] = newCoords[2][1] - 1;
                newCoords[3][1] = newCoords[3][1] - 1;
                break;
            }
        }
    }

    private void checkBoardBoundsUp() {
        for (int i = 0; i < 4; i++) {
            if (newCoords[i][1] < 1) {
                newCoords[0][1] = newCoords[0][1] + 1;
                newCoords[1][1] = newCoords[1][1] + 1;
                newCoords[2][1] = newCoords[2][1] + 1;
                newCoords[3][1] = newCoords[3][1] + 1;
                break;
            }
        }
    }

    private void checkBoardStorageCollision(int width, int height, int[][] boardBlocks, String movement) {
        int moveCounter = 0;
        int allowedMoves = 0;
        int max, max2, min, min2;

        switch (movement) {
            case "left":
                max = (newCoords[0][0] > newCoords[1][0] ? newCoords[0][0] : newCoords[1][0]);
                max2 = (newCoords[2][0] > newCoords[3][0] ? newCoords[2][0] : newCoords[3][0]);
                max = (max > max2 ? max : max2);
                allowedMoves = width - max - length;
                break;
            case "right":
                min = (newCoords[0][0] < newCoords[1][0] ? newCoords[0][0] : newCoords[1][0]);
                min2 = (newCoords[2][0] < newCoords[3][0] ? newCoords[2][0] : newCoords[3][0]);
                min = (min < min2 ? min : min2);
                allowedMoves = min - length;
                break;
            case "up":
                max = (newCoords[0][1] > newCoords[1][1] ? newCoords[0][1] : newCoords[1][1]);
                max2 = (newCoords[2][1] > newCoords[3][1] ? newCoords[2][1] : newCoords[3][1]);
                max = (max > max2 ? max : max2);
                allowedMoves = height - max - length;
                break;
            case "down":
                min = (newCoords[0][1] < newCoords[1][1] ? newCoords[0][1] : newCoords[1][1]);
                min2 = (newCoords[2][1] < newCoords[3][1] ? newCoords[2][1] : newCoords[3][1]);
                min = (min < min2 ? min : min2);
                allowedMoves = min - length;
                break;
        }

        while (true) {
            int collision = 0;
            if (allowedMoves <= 0)
                break;
            for (int i = 0; i < 4; i++) {
                if (boardBlocks[newCoords[i][0]][newCoords[i][1]] != 0)
                    collision = 1;
            }
            if (collision == 0)
                break;
            if (moveCounter == 3)
                break;
            switch (movement) {
                case "right":
                    moveRight(width, boardBlocks, "newCoords");
                    break;
                case "left":
                    moveLeft(boardBlocks, "newCoords");
                    break;
                case "down":
                    moveDown(height, boardBlocks, "newCoords");
                    break;
                case "up":
                    moveUp(boardBlocks, "newCoords");
                    break;
            }
            moveCounter++;
            allowedMoves--;
        }
    }

    private boolean checkIllegalRotate(int [][] boardBlocks, String rotate) {
        for (int i = 0; i < 4; i++) {
            if (boardBlocks[newCoords[i][0]][newCoords[i][1]] != 0) {
                revertRotateStatus(rotate);
                return true;
            }
        }
        return false;
    }

    /**
     *
     * @param board
     * @param rotate
     */
    private void updateCoords(Board board, String rotate) {
        newCoords[0][0] = coords[0][0];
        newCoords[0][1] = coords[0][1];
        newCoords[1][0] = coords[0][0];
        newCoords[1][1] = coords[0][1];
        newCoords[2][0] = coords[0][0];
        newCoords[2][1] = coords[0][1];
        newCoords[3][0] = coords[0][0];
        newCoords[3][1] = coords[0][1];
        int[][] boardBlocks = board.getStoredBlocks();
        int width = board.getWidth();
        int height = board.getHeight();
        changeCoords(1, secondBlockAngle);

        changeCoords(2, thirdBlockAngle[0]);
        changeCoords(2, thirdBlockAngle[1]);

        changeCoords(3, fourthBlockAngle[0]);
        changeCoords(3, fourthBlockAngle[1]);
        changeCoords(3, fourthBlockAngle[2]);

        switch(rotateStatus) {
            case 0:
                for (int i = 0; i < length; i++) {
                    checkBoardBoundsLeft();
                    checkBoardBoundsRight(width);
                    checkBoardBoundsUp();
                    checkBoardBoundsDown(height);
                }

                checkBoardStorageCollision(width, height, boardBlocks, "left");

                if (checkIllegalRotate(boardBlocks, rotate))
                    return;

                break;
            case 1:
                for (int i = 0; i < length; i++) {
                    checkBoardBoundsUp();
                    checkBoardBoundsLeft();
                    checkBoardBoundsRight(width);
                    checkBoardBoundsDown(height);
                }

                checkBoardStorageCollision(width, height, boardBlocks, "down");

                if (checkIllegalRotate(boardBlocks, rotate))
                    return;

                break;
            case 2:
                for (int i = 0; i < length; i++) {
                    checkBoardBoundsLeft();
                    checkBoardBoundsUp();
                    checkBoardBoundsRight(width);
                    checkBoardBoundsDown(height);
                }

                checkBoardStorageCollision(width, height, boardBlocks, "right");

                if (checkIllegalRotate(boardBlocks, rotate))
                    return;

                break;
            case 3:
                for (int i = 0; i < length; i++) {
                    checkBoardBoundsDown(height);
                    checkBoardBoundsLeft();
                    checkBoardBoundsRight(width);
                    checkBoardBoundsUp();
                }

                checkBoardStorageCollision(width, height, boardBlocks, "up");

                if (checkIllegalRotate(boardBlocks, rotate))
                    return;

                break;
        }
        coords[0][0] = newCoords[0][0];
        coords[0][1] = newCoords[0][1];
        coords[1][0] = newCoords[1][0];
        coords[1][1] = newCoords[1][1];
        coords[2][0] = newCoords[2][0];
        coords[2][1] = newCoords[2][1];
        coords[3][0] = newCoords[3][0];
        coords[3][1] = newCoords[3][1];
    }

    /**
     *
     * @param height
     * @param boardBlocks
     * @param option
     * @return
     */
    public int moveDown(int height, int[][] boardBlocks, String option) {
        for(int i = 0; i < 4; i++) {
            if (option.equals("currentCoords")) {
                if (coords[i][1] == (height - 1)) // lowest point
                    return 1;
            }
            else if (option.equals("newCoords"))
                if (newCoords[i][1] == (height - 1)) // lowest point
                    return 1;
        }

        for(int i = 0; i < 4; i++){
            if (option.equals("currentCoords")) {
                if (boardBlocks[coords[i][0]][coords[i][1] + 1] != 0)
                    return 1;
            }
            else if (option.equals("newCoords"))
                if (boardBlocks[newCoords[i][0]][newCoords[i][1] + 1] != 0)
                    return 1;
        }

        for(int i = 0; i < 4; i++){
            if (option.equals("currentCoords"))
                coords[i][1] = coords[i][1] + 1;
            else if (option.equals("newCoords"))
                newCoords[i][1] = newCoords[i][1] + 1;
        }
        return 0;
    }

    public void moveUp(int[][] boardBlocks, String option) {
        for(int i = 0; i < 4; i++) {
            if (option.equals("currentCoords")) {
                if (coords[i][1] <= 1) // highest point
                    return;
            }
            else if (option.equals("newCoords"))
                if (newCoords[i][1] <= 1) // highest point
                    return;
        }

        for(int i = 0; i < 4; i++){
            if (option.equals("currentCoords")) {
                if (boardBlocks[coords[i][0]][coords[i][1] - 1] != 0)
                    return;
            }
            else if (option.equals("newCoords"))
                if (boardBlocks[newCoords[i][0]][newCoords[i][1] - 1] != 0)
                    return;
        }

        for(int i = 0; i < 4; i++){
            if (option.equals("currentCoords"))
                coords[i][1] = coords[i][1] - 1;
            else if (option.equals("newCoords"))
                newCoords[i][1] = newCoords[i][1] - 1;
        }
    }

    public void moveLeft(int [][] boardBlocks, String option) {
        for(int i = 0; i < 4; i++){
            if (option.equals("currentCoords")) {
                if (coords[i][0] == 1)
                    return;
            }
            else if (option.equals("newCoords"))
                if (newCoords[i][0] == 1)
                    return;
        }

        for(int i = 0; i < 4; i++){
            if (option.equals("currentCoords")) {
                if (boardBlocks[coords[i][0] - 1][coords[i][1]] != 0)
                    return;
            }
            else if (option.equals("newCoords"))
                if (boardBlocks[newCoords[i][0] - 1][newCoords[i][1]] != 0)
                    return;
        }

        for(int i = 0; i < 4; i++){
            if (option.equals("currentCoords"))
                coords[i][0] = coords[i][0] - 1;
            else if (option.equals("newCoords"))
                newCoords[i][0] = newCoords[i][0] - 1;
        }
    }

    public void moveRight(int width, int [][] boardBlocks, String option) {
        for(int i = 0; i < 4; i++) {
            if (option.equals("currentCoords")) {
                if (coords[i][0] == (width - 1))
                    return;
            }
            else if (option.equals("newCoords"))
                if (newCoords[i][0] == (width - 1))
                    return;
        }

        for(int i = 0; i < 4; i++){
            if (option.equals("currentCoords")) {
                if (boardBlocks[coords[i][0] + 1][coords[i][1]] != 0)
                    return;
            }
            else if (option.equals("newCoords"))
                if (boardBlocks[newCoords[i][0] + 1][newCoords[i][1]] != 0)
                    return;
        }

        for(int i = 0; i < 4; i++){
            if (option.equals("currentCoords"))
                coords[i][0] = coords[i][0] + 1;
            else if (option.equals("newCoords"))
                newCoords[i][0] = newCoords[i][0] + 1;
        }
    }

    /**
     *
     * @param board
     */
    public void place(Board board) {
        int [][] boardStorage = board.getStoredBlocks();
        boardStorage[coords[0][0]][coords[0][1]] = identifier;
        boardStorage[coords[1][0]][coords[1][1]] = identifier;
        boardStorage[coords[2][0]][coords[2][1]] = identifier;
        boardStorage[coords[3][0]][coords[3][1]] = identifier;
        board.setStoredBlocks(boardStorage);
    }

    /**
     *
     * @param coords
     */
    protected void setCoords(int[][] coords) {
        this.coords = coords;
    }
}
