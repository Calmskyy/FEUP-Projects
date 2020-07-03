package Tetris.View;

import Tetris.Controller.*;

import javax.swing.*;
import java.awt.*;

public class GamePanel extends JPanel {

    private Game game;
    private boolean gameOver = false;

    public GamePanel(Game game){
        this.game = game;
        setLayout(null);

        setSize();

        setVisible(true);
    }

    public void setGameOver(boolean gameOver){
        this.gameOver = gameOver;
    }

    @Override
    public void paint(Graphics g) {
        this.removeAll();

        if(gameOver){
            drawBoard();

            drawScore();

            drawGameOver();
        }
        else {
            drawScore();

            drawLevel();

            drawControls();

            drawBank();

            drawNext();

            drawPiece(this.game.getPiece());

            drawBoard();
        }

        super.paint(g);
    }

    private void setSize(){
        setBounds(0, 0, 925, 775);
    }

    private Color getColor(String hexColor){
        Color pieceColor = null;

        switch (hexColor){
            case "#FFFF33":
                pieceColor = Color.YELLOW;
                break;

            case "#00F1F1":
                pieceColor = Color.cyan;
                break;

            case "#A000F1":
                pieceColor = Color.PINK;
                break;

            case "#00F100":
                pieceColor = Color.GREEN;
                break;

            case "#F10000":
                pieceColor = Color.RED;
                break;

            case "#F1A000":
                pieceColor = Color.ORANGE;
                break;

            case "#0000F1":
                pieceColor = Color.blue;
                break;

            default:
                pieceColor = null;
                break;

        }

        return pieceColor;
    }

    private void drawPiece(Piece piece) {
        int [][] coords = piece.getCoords();
        Color pieceColor = getColor(piece.getHexColor());

        for(int i = 0; i < 4; i++){

            JLabel block = new JLabel("■");
            block.setBounds(coords[i][0] * 25 + 40,coords[i][1] * 25 + 50, 65, 65);
            block.setFont(new Font("Serif", Font.PLAIN, 65));
            block.setForeground(pieceColor);

            add(block);
        }
    }


    public void drawBoard() {

        Board board = this.game.getBoard();
        int width = board.getWidth();
        int height = board.getHeight();
        int[][] storedBlocks = board.getStoredBlocks();
        Color pieceColor = null;


        for(int i = 0; i < width; i++){
            for (int j = 0; j < height; j++){
                JLabel block = new JLabel("■");

                if (storedBlocks[i][j] == 1){
                    pieceColor = Color.YELLOW;
                    block.setBounds(i * 25 + 40,j * 25 + 50, 65, 65);
                }

                if (storedBlocks[i][j] == 2) {
                    pieceColor = Color.cyan;
                    block.setBounds(i * 25 + 40,j * 25 + 50, 65, 65);
                }

                if (storedBlocks[i][j] == 3){
                    pieceColor = Color.PINK;
                    block.setBounds(i * 25 + 40,j * 25 + 50, 65, 65);
                }

                if (storedBlocks[i][j] == 4){
                    pieceColor = Color.GREEN;
                    block.setBounds(i * 25 + 40,j * 25 + 50, 65, 65);
                }

                if (storedBlocks[i][j] == 5){
                    pieceColor = Color.RED;
                    block.setBounds(i * 25 + 40,j * 25 + 50, 65, 65);
                }

                if (storedBlocks[i][j] == 6){
                    pieceColor = Color.ORANGE;
                    block.setBounds(i * 25 + 40,j * 25 + 50, 65, 65);
                }

                if (storedBlocks[i][j] == 7){
                    pieceColor = Color.blue;
                    block.setBounds(i * 25 + 40,j * 25 + 50, 65, 65);
                }

                block.setFont(new Font("Serif", Font.PLAIN, 65));
                block.setForeground(pieceColor);

                add(block);
            }
        }

        JPanel limits = new JPanel();
        limits.setBounds(70,65,250,525);
        limits.setBackground(Color.BLACK);
        add(limits);

        JPanel Back = new JPanel();
        Back.setBounds(40,35,315,590);
        Back.setBackground(Color.GRAY);
        add(Back);
    }

    private void drawNext() {

        Piece [] nextPieces = this.game.getNextPieces();

        JLabel nextPiece = new JLabel("Next Piece: ");
        nextPiece.setBounds(600,25, 100, 100);
        add(nextPiece);

        for (int j = 0; j < 3; ++j){
            int [][] coords = nextPieces[j].getCoords();
            Color pieceColor = getColor(nextPieces[j].getHexColor());


            for(int i = 0; i < 4; i++){

                JLabel block = new JLabel("■");
                block.setBounds(coords[i][0] * 20 + 40,coords[i][1] * 20 + 50, 55, 55);
                block.setFont(new Font("Serif", Font.PLAIN, 55));
                block.setForeground(pieceColor);

                add(block);
            }
        }

        JPanel nextBox = new JPanel();
        nextBox.setBounds(600, 100, 300, 100);
        nextBox.setBackground(Color.GRAY);
        add(nextBox);

    }

    public void drawScore() {

        int gameScore = game.getScore();
        int gameScoreIncrement = game.getScoreIncrement();
        int gameLineClears = game.getLineClears();

        String score = String.valueOf(gameScore);
        int size = score.length();

        char[] zero = new char[9 - size];

        for(int i = 0; i < 9 - size; ++i){
            zero[i] = '0';
        }

        String output = new String(zero) + score;
        String scoreIncrement = String.valueOf(gameScoreIncrement);
        String lineClears = String.valueOf(gameLineClears);

        JLabel value = new JLabel("Score: ");
        value.setBounds(600, 200, 100, 100);
        add(value);

        JLabel value2 = new JLabel(output);
        value2.setBounds(650, 200, 100, 100);
        add(value2);

        if (gameScoreIncrement != 0) {
            JLabel scoreInc = new  JLabel(" (+" + scoreIncrement + ")");
            scoreInc.setBounds(750, 200, 100, 100);
            add(scoreInc);
        }

        if (gameLineClears != 0) {
            JLabel lineC = new  JLabel(lineClears + " line clear!");
            lineC.setBounds(750, 200 + 25, 100, 100);
            add(lineC);
        }

    }

    private void drawLevel() {

        int level = this.game.getLevel();

        String levelString = String.valueOf(level);

        JLabel l = new JLabel("Level: " + levelString);
        l.setBounds(600, 250, 100, 100);
        add(l);

    }

    private void drawControls() {
        JLabel controls = new JLabel("Controls: ");
        controls.setBounds(600,500, 100, 100);
        add(controls);

        JLabel down = new JLabel("↓  - Move down");
        down.setBounds(600,520, 100, 100);
        add(down);

        JLabel left = new JLabel("←  - Move left");
        left.setBounds(600,540, 100, 100);
        add(left);

        JLabel right = new JLabel("→  - Move right");
        right.setBounds(600,560, 100, 100);
        add(right);

        JLabel z = new JLabel("Z  - Rotate left");
        z.setBounds(600,580, 100, 100);
        add(z);

        JLabel x = new JLabel("X  - Rotate right");
        x.setBounds(600,600, 200, 100);
        add(x);

        JLabel e = new JLabel("E - Store piece in bank");
        e.setBounds(600,620, 200, 100);
        add(e);

        JLabel r = new JLabel("R  - Restart");
        r.setBounds(600,640, 100, 100);
        add(r);

        JLabel q = new JLabel("Q  - Exit");
        q.setBounds(600,660, 100, 100);
        add(q);
    }


    private void drawBank() {
        Piece bankPiece = game.getBankPiece();

        JLabel bankString = new JLabel("Bank: ");
        bankString.setBounds(600, 275, 100, 100);
        add(bankString);

        if (bankPiece != null){
            int [][] coords = bankPiece.getCoords();
            Color pieceColor = getColor(bankPiece.getHexColor());


            for(int i = 0; i < 4; i++){

                JLabel block = new JLabel("■");
                block.setBounds(coords[i][0]*20 - 225,coords[i][1]*20 + 200, 55, 55);
                block.setFont(new Font("Serif", Font.PLAIN, 55));
                block.setForeground(pieceColor);

                add(block);
            }
        }

        JPanel bankBox = new JPanel();
        bankBox.setBounds(600, 350, 150, 150);
        bankBox.setBackground(Color.GRAY);
        add(bankBox);
    }

    public void drawGameOver() {

        JLabel gameOver = new JLabel("GAME OVER:");
        gameOver.setBounds(450, 100, 500, 100);
        gameOver.setFont(new Font("Serif", Font.PLAIN, 65));
        add(gameOver);

        JLabel info1 = new JLabel("Press R to restart, ");
        info1.setBounds(600, 300, 150, 50);
        add(info1);

        JLabel info2 = new JLabel("or Q to quit. ");
        info2.setBounds(600, 350, 100, 50);
        add(info2);
    }

}