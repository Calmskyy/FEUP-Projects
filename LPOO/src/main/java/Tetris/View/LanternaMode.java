package Tetris.View;

import Tetris.Controller.Board;
import Tetris.Controller.Game;
import Tetris.Controller.Piece;
import com.googlecode.lanterna.SGR;
import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.screen.Screen;
import com.googlecode.lanterna.screen.TerminalScreen;
import com.googlecode.lanterna.terminal.DefaultTerminalFactory;
import com.googlecode.lanterna.terminal.Terminal;

import java.io.IOException;

public class LanternaMode extends Display{

    private Screen screen;
    private TextGraphics graphics;

    /**
     * Constructor.
     *
     * @param game
     */
    public LanternaMode(Game game) {
        super(game);
    }

    /**
     * Get functions
     * @return
     */
    public char getNameBuffer() {
        return nameBuffer;
    }

    /**
     * Set function
     * @param nameBuffer
     */
    public void setNameBuffer(char nameBuffer) {
        this.nameBuffer = nameBuffer;
    }

    /**
     * --------------------- VIEW MODE ----------------------
     *
     * DONE
     */


    /**
     * DONE menuFrame, gameFrame, gameOver
     */
    @Override
    public void initializeViewMode() {
        try {
            Terminal terminal = new DefaultTerminalFactory().createTerminal();
            screen = new TerminalScreen(terminal);

            screen.setCursorPosition(null);   // we don't need a cursor
            screen.startScreen();             // screens must be started
            screen.doResizeIfNecessary();     // resize screen if necessary
            graphics = screen.newTextGraphics();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * --------------------------------------------------
     *
     * --------------------- MENU ----------------------
     *
     * DONE
     */

    @Override
    public void drawMenu() {
        int cursor = game.getCursor();

        String key = readInput();
        if (key != null)
            game.menuProcessKey(key);

        screen.clear();

        drawLogo();

        if (cursor == 0)
            drawPlayButton(true);
        else
            drawPlayButton(false);

        if (cursor == 1)
            drawHighScoresButton(true);
        else
            drawHighScoresButton(false);

        if (cursor == 2)
            drawQuitButton(true);
        else
            drawQuitButton(false);

        try {
            screen.refresh();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * TBD
     */
    @Override
    public void drawLogo() {
        graphics.setForegroundColor(TextColor.Factory.fromString("#A000F1"));

        graphics.drawLine(20, 0, 24, 0, '■');
        graphics.drawLine(22, 0, 22, 4, '■');

        graphics.setForegroundColor(TextColor.Factory.fromString("#FFFF33"));

        graphics.drawLine(26, 0, 30, 0, '■');
        graphics.drawLine(26, 1, 26, 1, '■');
        graphics.drawLine(26, 2, 28, 2, '■');
        graphics.drawLine(26, 3, 26, 3, '■');
        graphics.drawLine(26, 4, 30, 4, '■');

        graphics.setForegroundColor(TextColor.Factory.fromString("#A000F1"));

        graphics.drawLine(32, 0, 36, 0, '■');
        graphics.drawLine(34, 0, 34, 4, '■');

        graphics.setForegroundColor(TextColor.Factory.fromString("#F1A000"));

        graphics.putString(new TerminalPosition(38, 0), "■■■■");
        graphics.putString(new TerminalPosition(38, 1), "■  ■");
        graphics.putString(new TerminalPosition(38, 2), "■■■■");
        graphics.putString(new TerminalPosition(38, 3), "■  ■");
        graphics.putString(new TerminalPosition(38, 4), "■   ■");

        graphics.setForegroundColor(TextColor.Factory.fromString("#00F1F1"));

        graphics.drawLine(44, 0, 44, 4, '■');

        graphics.setForegroundColor(TextColor.Factory.fromString("#00F100"));

        graphics.drawLine(46, 0, 50, 0, '■');
        graphics.drawLine(46, 0, 46, 2, '■');
        graphics.drawLine(46, 2, 50, 2, '■');
        graphics.drawLine(50, 2, 50, 4, '■');
        graphics.drawLine(50, 4, 46, 4, '■');
    }

    private void drawPlayButton(boolean hover) {

        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        if (!hover) {
            graphics.drawLine(25, 6, 45, 6, '■');
            graphics.drawLine(45, 6, 45, 10, '■');
            graphics.drawLine(45, 10,25, 10, '■');
            graphics.drawLine(25, 10, 25, 6, '■');
        }
        else{
            graphics.drawLine(25, 6, 45, 6, '■');
            graphics.drawLine(25, 7, 31, 7, '■');
            graphics.drawLine(38, 7, 45, 7, '■');
            graphics.drawLine(25, 8, 31, 8, '■');
            graphics.drawLine(38, 8, 45, 8, '■');
            graphics.drawLine(25, 9, 31, 9, '■');
            graphics.drawLine(38, 9, 45, 9, '■');
            graphics.drawLine(25, 10, 45, 10, '■');
            graphics.setForegroundColor(TextColor.Factory.fromString("#FFAA00"));
        }

        graphics.putString(new TerminalPosition(33, 8), "PLAY");
    }

    private void drawHighScoresButton(boolean hover) {
        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        if (!hover) {
            graphics.drawLine(25, 12, 45, 12, '■');
            graphics.drawLine(45, 12, 45, 16, '■');
            graphics.drawLine(45, 16, 25, 16, '■');
            graphics.drawLine(25, 16, 25, 12, '■');
        }
        else{
            graphics.drawLine(25, 12, 45, 12, '■');
            graphics.drawLine(25, 13, 28, 13, '■');
            graphics.drawLine(42, 13, 45, 13, '■');
            graphics.drawLine(25, 14, 28, 14, '■');
            graphics.drawLine(42, 14, 45, 14, '■');
            graphics.drawLine(25, 15, 28, 15, '■');
            graphics.drawLine(42, 15, 45, 15, '■');
            graphics.drawLine(25, 16, 45, 16, '■');
            graphics.setForegroundColor(TextColor.Factory.fromString("#FFAA00"));
        }

        graphics.putString(new TerminalPosition(30, 14), "HIGH SCORES");
    }

    private void drawQuitButton(boolean hover) {
        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        if (!hover) {
            graphics.drawLine(25, 18, 45, 18, '■');
            graphics.drawLine(45, 18, 45, 22, '■');
            graphics.drawLine(45, 22, 25, 22, '■');
            graphics.drawLine(25, 22, 25, 18, '■');
        }
        else{
            graphics.drawLine(25, 18, 45, 18, '■');
            graphics.drawLine(25, 19, 31, 19, '■');
            graphics.drawLine(38, 19, 45, 19, '■');
            graphics.drawLine(25, 20, 31, 20, '■');
            graphics.drawLine(38, 20, 45, 20, '■');
            graphics.drawLine(25, 21, 31, 21, '■');
            graphics.drawLine(38, 21, 45, 21, '■');
            graphics.drawLine(25, 22, 45, 22, '■');
            graphics.setForegroundColor(TextColor.Factory.fromString("#FFAA00"));
        }

        graphics.putString(new TerminalPosition(33, 20), "QUIT");
    }

    /**
     *--------------------------------------------------
     *
     * --------------------- GAME ----------------------
     */
    @Override
    public void drawGame() {
        screen.clear();

        drawPiece(this.game.getPiece());

        drawBoard();

        drawNext();

        drawScore();

        drawLevel();

        drawControls();

        drawBank();

        try {
            screen.refresh();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * DONE
     * @param piece
     */
    private void drawPiece(Piece piece) {
        int [][] coords = piece.getCoords();
        String hexColor = piece.getHexColor();

        graphics.setForegroundColor(TextColor.Factory.fromString(hexColor));

        for(int i = 0; i < 4; i++){
            graphics.putString(new TerminalPosition(coords[i][0],coords[i][1]), "■");
        }
    }

    /**
     *
     */
    private void drawBoard() {
        Board board = this.game.getBoard();
        int width = board.getWidth();
        int height = board.getHeight();
        int[][] storedBlocks = board.getStoredBlocks();

        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        for (int i = 0; i <= width; i++) {
            graphics.putString(new TerminalPosition(i, 0), "█");
            graphics.putString(new TerminalPosition(i, height), "█");
        }

        for (int i = -1; i <= height; i++) {
            if (i == height)
                graphics.putString(new TerminalPosition(0, i), "█");
            else
                graphics.putString(new TerminalPosition(0, i), "█");
            if (i == height)
                graphics.putString(new TerminalPosition(width, i), "█");
            else
                graphics.putString(new TerminalPosition(width, i), "█");
        }

        for (int i = 0; i < width; i++) {

            for (int j = 0; j < height; j++) {

                graphics.setForegroundColor(TextColor.Factory.fromString("#FFFF33"));
                if (storedBlocks[i][j] == 1)
                    graphics.putString(new TerminalPosition(i, j), "■");

                graphics.setForegroundColor(TextColor.Factory.fromString("#00F1F1"));
                if (storedBlocks[i][j] == 2)
                    graphics.putString(new TerminalPosition(i, j), "■");

                graphics.setForegroundColor(TextColor.Factory.fromString("#A000F1"));
                if (storedBlocks[i][j] == 3)
                    graphics.putString(new TerminalPosition(i, j), "■");

                graphics.setForegroundColor(TextColor.Factory.fromString("#00F100"));
                if (storedBlocks[i][j] == 4)
                    graphics.putString(new TerminalPosition(i, j), "■");

                graphics.setForegroundColor(TextColor.Factory.fromString("#F10000"));
                if (storedBlocks[i][j] == 5)
                    graphics.putString(new TerminalPosition(i, j), "■");

                graphics.setForegroundColor(TextColor.Factory.fromString("#F1A000"));
                if (storedBlocks[i][j] == 6)
                    graphics.putString(new TerminalPosition(i, j), "■");

                graphics.setForegroundColor(TextColor.Factory.fromString("#0000F1"));
                if (storedBlocks[i][j] == 7)
                    graphics.putString(new TerminalPosition(i, j), "■");
            }
        }
    }

    /**
     *
     */
    private void drawNext() {
        Board board = this.game.getBoard();
        Piece [] nextPieces = this.game.getNextPieces();

        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        graphics.putString(new TerminalPosition(board.getWidth() + 5, 3), "Next Pieces: ");

        drawPiece(nextPieces[0]);
        drawPiece(nextPieces[1]);
        drawPiece(nextPieces[2]);
    }

    /**
     *
     */
    private void drawScore() {
        Board board = this.game.getBoard();
        int gameScore = game.getScore();
        int gameScoreIncrement = game.getScoreIncrement();
        int gameLineClears = game.getLineClears();

        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        String score = String.valueOf(gameScore);
        int size = score.length();

        char[] zero = new char[9 - size];

        for(int i = 0; i < 9 - size; ++i){
            zero[i] = '0';
        }

        String output = new String(zero) + score;
        String scoreIncrement = String.valueOf(gameScoreIncrement);
        String lineClears = String.valueOf(gameLineClears);

        graphics.putString(new TerminalPosition(board.getWidth() + 5, 6), "Score: ");
        graphics.putString(new TerminalPosition(board.getWidth() + 12, 6), output);


        if (gameScoreIncrement != 0)
            graphics.putString(new TerminalPosition(board.getWidth() + 21, 6), " (+" + scoreIncrement + ")");

        if (gameLineClears != 0) {
            if (gameLineClears == 1)
                graphics.putString(new TerminalPosition(board.getWidth() + 22, 7), lineClears + " line clear!");
            else
                graphics.putString(new TerminalPosition(board.getWidth() + 22, 7), lineClears + " line clears!");
        }
    }

    /**
     *
     */
    private void drawLevel() {
        Board board = this.game.getBoard();
        int level = this.game.getLevel();

        String levelString = String.valueOf(level);

        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        graphics.putString(new TerminalPosition(board.getWidth() + 5, 8), "Level: ");
        graphics.putString(new TerminalPosition(board.getWidth() + 12, 8), levelString);
    }

    /**
     *
     */
    private void drawControls() {
        Board board = this.game.getBoard();

        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        graphics.putString(new TerminalPosition(board.getWidth() + 5, 10), "Controls: ");
        graphics.putString(new TerminalPosition(board.getWidth() + 5, 11), "↓  - Move down");
        graphics.putString(new TerminalPosition(board.getWidth() + 5, 12), "←  - Move left");
        graphics.putString(new TerminalPosition(board.getWidth() + 5, 13), "→  - Move right");
        graphics.putString(new TerminalPosition(board.getWidth() + 5, 14), "Z  - Rotate left");
        graphics.putString(new TerminalPosition(board.getWidth() + 5, 15), "X  - Rotate right");
        graphics.putString(new TerminalPosition(board.getWidth() + 5, 16), "E - Store piece in bank");
        graphics.putString(new TerminalPosition(board.getWidth() + 5, 17), "R  - Restart");
        graphics.putString(new TerminalPosition(board.getWidth() + 5, 18), "Q  - Exit");
    }

    /**
     *
     */
    private void drawBank() {
        Board board = game.getBoard();
        Piece bankPiece = game.getBankPiece();

        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        graphics.putString(new TerminalPosition(board.getWidth() + 24, 8), "Bank:");
        graphics.drawLine(board.getWidth() + 30, 8, board.getWidth() + 36, 8, '▪');
        graphics.drawLine(board.getWidth() + 36, 8, board.getWidth() + 36, 11, '▪');
        graphics.drawLine(board.getWidth() + 36, 11, board.getWidth() + 30, 11, '▪');
        graphics.drawLine(board.getWidth() + 30, 11, board.getWidth() + 30, 8, '▪');

        if (bankPiece != null)
            drawPiece(bankPiece);
    }


    /**
     *--------------------------------------------------
     *
     *------------------- GAME OVER -------------------
     */

    /**
     *
     */
    @Override
    public void drawGameOver() {
        screen.clear();

        //draws the layout of the board
        drawBoard();

        //draws Score
        drawScore();

        Board board = this.game.getBoard();

        graphics.putString(new TerminalPosition(board.getWidth() + 6, 9), "GAME OVER: ");
        graphics.putString(new TerminalPosition(board.getWidth() + 6, 10), "Press R to restart, ");
        graphics.putString(new TerminalPosition(board.getWidth() + 6, 11), "or Q to quit. ");

        try {
            screen.refresh();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     *--------------------------------------------------
     *
     *------------------- FINAL MENU -------------------
     */

    /**
     *
     */
    @Override
    public void drawFinalMenu() {

        screen.clear();

        drawFinalScore();

        drawTyping();

        try {
            screen.refresh();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * DONE
     */
    @Override
    protected void drawFinalScore() {
        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        graphics.setForegroundColor(TextColor.Factory.fromString("#FF0505"));
        graphics.putString(new TerminalPosition(30, 2), "GAME OVER");
        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.putString(new TerminalPosition(23, 4), "FINAL SCORE:");

        String score = String.valueOf(game.getScore());
        int size = score.length();

        char[] zero = new char[9 - size];

        for(int i = 0; i < 9 - size; ++i){
            zero[i] = '0';
        }

        String output = new String(zero) + score;

        graphics.putString(new TerminalPosition(37, 4), output);
    }

    /**
     * DONE BUT MISSING SOMETHING
     */
    @Override
    protected void drawTyping() {
        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        graphics.putString(new TerminalPosition(10, 8), "Your name:");

        String name = new String(game.getHighScoreName());

        graphics.putString(new TerminalPosition(21, 8), name);
        int length = game.getNameLength();
        if (length != 15)
            graphics.putString(new TerminalPosition(21 + game.getNameLength(), 8), "_");

        graphics.putString(new TerminalPosition(10, 10), "(Name has a maximum of 15 characters)");
        graphics.putString(new TerminalPosition(10, 11), "(Leave it empty to not save anything)");
    }

    /**
     *--------------------------------------------------
     *
     *------------------- HIGH SCORE -------------------
     */

    /**
     *
     */
    public void drawHighScoreMenu() {

        screen.clear();

        drawHighScores();

        drawBackButton();

        graphics.putString(new TerminalPosition(30, 2), "HIGH SCORES: ");

        try {
            screen.refresh();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * DONE
     */
    public void drawHighScores() {

        int[] scores = game.getScores();
        String[] names = game.getHighScoreNames();

        graphics.setForegroundColor(TextColor.Factory.fromString("#D3D3D3"));
        graphics.enableModifiers(SGR.BOLD);

        for (int i = 0; i < 10; i++) {
            graphics.putString(new TerminalPosition(20, 4 + (i * 2)), names[i]);

            String score = String.valueOf(scores[i]);
            int size = score.length();

            char[] zero = new char[9 - size];

            for(int j = 0; j < 9 - size; j++){
                zero[j] = '0';
            }

            String output = new String(zero) + score;

            graphics.putString(new TerminalPosition(40, 4 + (i * 2)), output);
        }
    }

    /**
     * DONE
     */
    public void drawBackButton() {
        graphics.drawLine(6, 19, 15, 19, '■');
        graphics.drawLine(6, 21, 15, 21, '■');
        graphics.drawLine(6, 19, 6, 21, '■');
        graphics.drawLine(15, 19, 15, 21, '■');

        graphics.setForegroundColor(TextColor.Factory.fromString("#FFAA00"));
        graphics.putString(new TerminalPosition(8, 20), "RETURN");
    }

    /**
     *--------------------------------------------------
     *
     *
     */
    public String readInput(){
        String input = null;

        KeyStroke key = null;

        try{
            key = screen.pollInput();
        } catch (IOException e) {
            e.printStackTrace();
        }

        if(key == null)
            return null;

        switch(key.getKeyType()){
            case ArrowDown:
                input = "ARROWDOWN";
                break;
            case ArrowLeft:
                input = "ARROWLEFT";
                break;
            case ArrowRight:
                input = "ARROWRIGHT";
                break;
            case ArrowUp:
                input = "ARROWUP";
                break;
            case Enter:
                input = "ENTER";
                break;
            case Backspace:
                input = "DELETE";
                break;
            case Character:
                nameBuffer = key.getCharacter();
                if (key.getCharacter() == 'q' || key.getCharacter() == 'Q') {
                    input = "QUIT";
                }
                else if (key.getCharacter() == 'z' || key.getCharacter() == 'Z')
                    input = "ROTATELEFT";
                else if (key.getCharacter() == 'x' || key.getCharacter() == 'X')
                    input = "ROTATERIGHT";
                else if (key.getCharacter() == 'r' || key.getCharacter() == 'R')
                    input = "RESTART";
                else if (key.getCharacter() == 'e' || key.getCharacter() == 'E')
                    input = "BANK";

                if (input == null)
                    input = "CHARACTER";
                break;
            case EOF:
                input = "STOP";
                break;
            default:
                break;
        }

        return input;
    }

    /**
     *
     */
    public void closeScreen(){

        try {
            screen.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}