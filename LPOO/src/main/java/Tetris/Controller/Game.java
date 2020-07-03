package Tetris.Controller;

import Tetris.View.*;
import Tetris.Model.*;

import java.util.*;

import static java.util.stream.Collectors.toMap;

public class Game {

    /**
     * Instance variables.
     */
    private int stopFlag = 0;
    private int cursor = 0;
    private int moveDownCounter = 0;
    private int score = 0;
    private int restart = 0;
    private int gameOver = 0;
    private int scoreIncrement = 0;
    private int lineClears = 0;
    private int level = 1;
    private int gameMenu = 0;
    private char[] highScoreName;
    private Map<String, Integer> highScores = new HashMap<>();
    private String[] highScoreNames;
    private int[] scores;
    private int nameLength = 0;
    private boolean bankSwapAvailable = true;
    private int[] nextPositions = new int[3];
    private Random rand = new Random();
    private Board board;
    private Piece piece;
    private Piece bankPiece;
    private Piece[] nextPieces = new Piece[3];
    private Display display;

    /**
     * Constructor.
     */
    public Game(String mode) {
        board = new Board(11, 21);
        nextPositions[0] = 18 + board.getWidth();

        if(mode.equals("LANTERNA"))
            display = new LanternaMode(this);
        else if(mode.equals("SWING"))
            display = new SwingMode(this);
    }

    /**
     * Get functions.
     */
    public Board getBoard() { return this.board; }

    public Piece getPiece() { return this.piece; }

    public Piece [] getNextPieces() { return this.nextPieces; }

    public int getScore() { return this.score; }

    public int getScoreIncrement() { return  this.scoreIncrement; }

    public int getLineClears() { return this.lineClears; }

    public int getLevel(){ return this.level; }

    public char[] getHighScoreName(){ return this.highScoreName; }

    public Piece getBankPiece() {
        return bankPiece;
    }

    public int[] getScores() { return this.scores; }

    public String[] getHighScoreNames() { return this.highScoreNames; }

    public int getNameLength() { return this.nameLength; }

    public int getCursor() { return this.cursor; }

    /**
     *
     */
    public void run() {
        double FPS = 30;
        double TPS = 1000000000/FPS;
        double delta = 0;
        long now;
        long lastTime = System.nanoTime();

        display.initializeViewMode();

        initializeHighScores();

        while (stopFlag == 0) {
            now = System.nanoTime();
            delta += (now - lastTime)/TPS;
            lastTime = now;
            if (delta >= 1) {
                if (gameMenu == 0) {
                    display.drawMenu();
                }
                else if (gameMenu == 1) {

                    String key = display.readInput();
                    if (key != null)
                        gameProcessKey(key);
                    if (restart == 1)
                        resetGame();
                    if (gameOver == 1) {
                        gameOver();
                        delta = 0;
                    }

                    moveDownCounter++;
                    if (moveDownCounter == getMoveDownSpeed()) {
                        if (piece.moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords") == 1) {
                            placePiece(board);
                        }
                        moveDownCounter = 0;
                    }
                    display.drawGame();
                }
                else if (gameMenu == 2) {

                    display.setNameBuffer(' ');
                    String key = display.readInput();
                    if (key != null)
                        finalMenuProcessKey(key);


                    display.drawFinalMenu();
                }
                else if (gameMenu == 3) {

                    String key = display.readInput();
                    if (key != null)
                        highScoreMenuProcessKey(key);


                    display.drawHighScoreMenu();
                }
                delta--;
            }
            try {
                Thread.sleep(10);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        display.closeScreen();
        System.exit(0);
    }

    /**
     *
     */
    private void resetGame() {
        score = 0;
        scoreIncrement = 0;
        restart = 0;
        level = 1;
        moveDownCounter = 0;
        lineClears = 0;
        board = new Board(11, 21);
        piece = createPiece(0, "random", 0);
        nextPieces[0] = createPiece(0, "nextRandom", 0);
        nextPositions[1] = nextPositions[0] + nextPieces[0].getLength() + 1;
        nextPieces[1] = createPiece(0, "nextRandom", 1);
        nextPositions[2] = nextPositions[1] + nextPieces[1].getLength() + 1;
        nextPieces[2] = createPiece(0, "nextRandom", 2);
        bankPiece = null;
        bankSwapAvailable = true;
    }

    /**
     *
     */
    private void resetHighScoreName() {
        highScoreName = new char[16];
        for(int i = 0; i < highScoreName.length; i++) {
            highScoreName[i] = ' ';
        }
        nameLength = 0;
    }

    /**
     *
     */
    private void initializeHighScores() {

        highScores.put("PLACEHOLDER 1", 50000);
        highScores.put("PLACEHOLDER 2", 45000);
        highScores.put("PLACEHOLDER 3", 40000);
        highScores.put("PLACEHOLDER 4", 30000);
        highScores.put("PLACEHOLDER 5", 10000);
        highScores.put("PLACEHOLDER 6", 5000);
        highScores.put("PLACEHOLDER 7", 0);
        highScores.put("PLACEHOLDER 8", 0);
        highScores.put("PLACEHOLDER 9", 0);
        highScores.put("PLACEHOLDER 10", 0);

        saveHighScore(true);
    }

    /**
     *
     */
    private void saveHighScore(boolean initialSave) {
        if (!initialSave) {
            if (highScoreName[0] == ' ')
                return;

            highScores.put(new String(highScoreName), score);
        }

        highScoreNames = new String[10];
        scores = new int [10];

        highScores = highScores
                .entrySet()
                .stream()
                .sorted(Collections.reverseOrder(Map.Entry.comparingByValue()))
                .collect(
                        toMap(Map.Entry::getKey, Map.Entry::getValue, (e1, e2) -> e2,
                                LinkedHashMap::new));

        Set scoreSet = highScores.entrySet();
        int counter = 0;
        for (Object o : scoreSet) {
            Map.Entry mapEntry = (Map.Entry) o;
            highScoreNames[counter] = (String) mapEntry.getKey();
            scores[counter] = (int) mapEntry.getValue();
            counter++;
            if (counter == 10)
                break;
        }
    }

    /**
     *
     */
    private void gameOver() {
        display.drawGameOver();
        String key;

        while (true) {
            key = display.readInput();

            if (key != null) {
                if (key.equals("RESTART")) {
                    resetGame();
                    break;
                } else if (key.equals("QUIT")) {
                    gameMenu = 2;
                    resetHighScoreName();
                    break;
                }
            }
        }
        gameOver = 0;
    }

    /**
     *
     */
    private void changeLevel() {
        int [] levelIncrement = new int [9];
        for (int i = 0; i < 9; i++) {
            if (i == 0) {
                levelIncrement[i] = 1000;
                continue;
            }
            levelIncrement[i] = levelIncrement[i - 1] + (1000 * i );
        }
        for (int i = 8; i >= 0; i--) {
            if (score >= levelIncrement[i]) {
                level = i + 2;
                return;
            }
        }
    }

    private void bankSwap() {
        if (!bankSwapAvailable)
            return;
        if (bankPiece == null) {
            bankPiece = createPiece(piece.getIdentifier(), "bank", 0);
            piece = createPiece(nextPieces[0].getIdentifier(), "specific", 0);
            nextPieces[0] = createPiece(nextPieces[1].getIdentifier(), "nextSpecific", 0);
            nextPositions[1] = nextPositions[0] + nextPieces[0].getLength() + 1;
            nextPieces[1] = createPiece(nextPieces[2].getIdentifier(), "nextSpecific", 1);
            nextPositions[2] = nextPositions[1] + nextPieces[1].getLength() + 1;
            nextPieces[2] = createPiece(0, "nextRandom", 2);
        }
        else {
            int tempIdentifier = piece.getIdentifier();
            piece = createPiece(bankPiece.getIdentifier(), "specific", 0);
            bankPiece = createPiece(tempIdentifier, "bank", 0);
        }
        bankSwapAvailable = false;
    }

    /**
     *
     * @return
     */
    private int getMoveDownSpeed() {
        return 45 - (level * 4);
    }

    /**
     *
     * @param piece
     * @param option
     * @param nextOrder
     * @return
     */
    private Piece createPiece(int piece, String option, int nextOrder) {
        int type = piece;
        if (option.equals("random"))
            type = rand.nextInt(7) + 1;

        if (option.equals("bank"))
            switch (type) {
                case 1:
                    return new Square(32 + board.getWidth(), 9);
                case 2:
                    return new Rectangle(32 + board.getWidth(), 9);
                case 3:
                    return new TPiece(32 + board.getWidth(), 9);
                case 4:
                    return new SPiece(32 + board.getWidth(), 10);
                case 5:
                    return new ZPiece(32 + board.getWidth(), 9);
                case 6:
                    return new LPiece(34 + board.getWidth(), 10);
                case 7:
                    return new JPiece(32 + board.getWidth(), 10);
            }

        if (option.equals("nextRandom") || option.equals("nextSpecific")) {
            if (option.equals("nextRandom"))
                type = rand.nextInt(7) + 1;
            switch (type) {
                case 1:
                    return new Square(nextPositions[nextOrder], 3);
                case 2:
                    return new Rectangle(nextPositions[nextOrder], 3);
                case 3:
                    return new TPiece(nextPositions[nextOrder], 3);
                case 4:
                    return new SPiece(nextPositions[nextOrder], 4);
                case 5:
                    return new ZPiece(nextPositions[nextOrder], 3);
                case 6:
                    return new LPiece(nextPositions[nextOrder] + 2, 4);
                case 7:
                    return new JPiece(nextPositions[nextOrder], 4);
            }
        }
        switch (type) {
            case 1:
                return new Square(board.getWidth());
            case 2:
                return new Rectangle(board.getWidth());
            case 3:
                return new TPiece(board.getWidth());
            case 4:
                return new SPiece(board.getWidth());
            case 5:
                return new ZPiece(board.getWidth());
            case 6:
                return new LPiece(board.getWidth());
            case 7:
                return new JPiece(board.getWidth());
        }
        return new Square(board.getWidth()); // default to square in case something goes wrong (shouldn't happen)
    }

    /**
     *
     * @param board
     */
    private void placePiece(Board board) {
        piece.place(board);
        if (board.gameOverCheck())
            gameOver = 1;
        scoreIncrement = 0;
        int scorePerLine = 0;
        lineClears = 0;
        int returnFlag;
        while (true) {
            returnFlag = board.clearLine();
            if (returnFlag == 0)
                break;
            else if (returnFlag == 1) {
                lineClears++;
                if (scorePerLine == 0)
                    scorePerLine = 1000;
                else
                    scorePerLine = scorePerLine * 2;
                scoreIncrement += scorePerLine;
            }
        }

        scoreIncrement = scoreIncrement + 100;
        score = score + scoreIncrement;
        changeLevel();
        piece = createPiece(nextPieces[0].getIdentifier(), "specific", 0);
        nextPieces[0] = createPiece(nextPieces[1].getIdentifier(), "nextSpecific", 0);
        nextPositions[1] = nextPositions[0] + nextPieces[0].getLength() + 1;
        nextPieces[1] = createPiece(nextPieces[2].getIdentifier(), "nextSpecific", 1);
        nextPositions[2] = nextPositions[1] + nextPieces[1].getLength() + 1;
        nextPieces[2] = createPiece(0, "nextRandom", 2);
        bankSwapAvailable = true;
    }

    /**
     *
     * @param key
     */
    private void gameProcessKey(String key) {
        switch(key) {
            case "ARROWDOWN":
                if (piece.moveDown(board.getHeight(), board.getStoredBlocks(), "currentCoords") == 1) {
                    placePiece(board);
                    moveDownCounter = 0;
                }
                break;
            case "ARROWLEFT":
                piece.moveLeft(board.getStoredBlocks(), "currentCoords");
                break;
            case "ARROWRIGHT":
                piece.moveRight(board.getWidth(), board.getStoredBlocks(), "currentCoords");
                break;
            case "QUIT":
                gameMenu = 2;
                resetHighScoreName();
                break;
            case "ROTATELEFT":
                piece.rotateLeft(board);
                break;
            case "ROTATERIGHT":
                piece.rotateRight(board);
                break;
            case "BANK":
                    bankSwap();
                break;
            case "RESTART":
                restart = 1;
                break;
            case "STOP":
                stopFlag = 1;
                break;
            default:
                break;
        }
    }

    /**
     *
     * @param key
     */
    public void menuProcessKey(String key) {
        switch(key) {
            case "ARROWDOWN":
                cursor++;
                if (cursor > 2)
                    cursor = 2;
                break;
            case "ARROWUP":
                cursor--;
                if (cursor < 0)
                    cursor = 0;
                break;
            case "ENTER":
                if (cursor == 0) {
                    resetGame();
                    gameMenu = 1;
                }
                if (cursor == 1)
                    gameMenu = 3;
                if (cursor == 2)
                    stopFlag = 1;
                break;
            default:
                break;
        }
    }

    private void finalMenuProcessKey(String key) {
        switch(key) {
            case "ENTER":
                gameMenu = 0;
                saveHighScore(false);
                break;
            case "DELETE":
                if (nameLength <= 0)
                    break;
                highScoreName[nameLength - 1] = ' ';
                nameLength--;
                break;
            default:
                if (nameLength > 14)
                    break;
                highScoreName[nameLength] = display.getNameBuffer();
                nameLength++;
                break;
        }
    }

    private void highScoreMenuProcessKey(String key) {

        if ("ENTER".equals(key)) {
            gameMenu = 0;
        }
    }
}
