package Tetris.View;

import Tetris.Controller.Game;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;

public class SwingMode extends Display{


    private JFrame menuFrame;

    private JFrame gameFrame;
    private GamePanel gamePanel;

    private JFrame highScoreFrame;

    private JFrame finalMenuFrame;

    private KeyEvent key;

    /**
     * Constructor.
     *
     * @param game
     */
    public SwingMode(Game game) {
        super(game);
    }

    /**
     * Get Funtcion
     * @return
     */
    @Override
    public char getNameBuffer() {
        return this.nameBuffer;
    }

    /**
     * Set Function
     * @param nameBuffer
     */
    @Override
    public void setNameBuffer(char nameBuffer) {
        this.nameBuffer = nameBuffer;
    }

    /**
     * --------------------- VIEW MODE ----------------------
     */
    @Override
    public void initializeViewMode() {
        //MENU
        menuFrame = new JFrame("MENU");
        menuFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        menuFrame.setLayout(new BoxLayout(menuFrame.getContentPane(), BoxLayout.Y_AXIS));
        menuFrame.setSize(1000,1000);//1000 width and 1000 height
        menuFrame.setLayout(null);//using no layout managers

        //GAME
        gameFrame = new JFrame("GAME");
        gameFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        gameFrame.setLayout(new BoxLayout(gameFrame.getContentPane(), BoxLayout.Y_AXIS));
        gameFrame.setSize(925,775);//1000 width and 1000 height
        gameFrame.setLayout(null);//using no layout managers

        gamePanel = new GamePanel(game);

        gameFrame.getContentPane().add(gamePanel);

        //High Score
        highScoreFrame = new JFrame("HIGH SCORES");
        highScoreFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        highScoreFrame.setLayout(new BoxLayout(highScoreFrame.getContentPane(), BoxLayout.Y_AXIS));
        highScoreFrame.setSize(1000,1000);//1000 width and 1000 height
        highScoreFrame.setLayout(null);//using no layout managers

        //Final Menu
        finalMenuFrame = new JFrame("FINAL MENU");
        finalMenuFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        finalMenuFrame.setLayout(new BoxLayout(highScoreFrame.getContentPane(), BoxLayout.Y_AXIS));
        finalMenuFrame.setSize(1000,1000);//1000 width and 1000 height
        finalMenuFrame.setLayout(null);//using no layout managers


        KeyEventDispatcher keyEventDispatcher = e -> {
            key = e;
            return false;
        };
        KeyboardFocusManager
                .getCurrentKeyboardFocusManager()
                .addKeyEventDispatcher(keyEventDispatcher);

        menuFrame.setVisible(true);
    }

    /**
     * --------------------------------------------------
     *
     * --------------------- MENU ----------------------
     */
    @Override
    public void drawMenu() {
        finalMenuFrame.setVisible(false);
        highScoreFrame.setVisible(false);
        gameFrame.setVisible(false);
        menuFrame.setVisible(true);
        drawMenuSwing();

        menuFrame.repaint();
    }

    private void drawMenuSwing() {
        drawLogo();

        JButton play = new JButton("Play");
        play.setBounds(350, 200, 300, 100);
        play.addActionListener(actionEvent -> {
            game.menuProcessKey("ENTER");
            menuFrame.setVisible(false);
            gameFrame.setVisible(true);
        });


        JButton highScore = new JButton("HighScore");
        highScore.setBounds(350, 350, 300, 100);
        highScore.addActionListener(actionEvent -> {
            game.menuProcessKey("ARROWDOWN");
            game.menuProcessKey("ENTER");
            menuFrame.setVisible(false);
            highScoreFrame.setVisible(true);
        });


        JButton quit = new JButton("Quit");
        quit.setBounds(350, 500, 300, 100);
        quit.addActionListener(actionEvent -> {
            game.menuProcessKey("ARROWDOWN");
            game.menuProcessKey("ARROWDOWN");
            game.menuProcessKey("ENTER");
            menuFrame.setVisible(false);
        });

        menuFrame.getContentPane().add(play);
        menuFrame.getContentPane().add(highScore);
        menuFrame.getContentPane().add(quit);

        menuFrame.validate();
        menuFrame.repaint();
    }

    @Override
    public void drawLogo() {

    }

    /**
     *--------------------------------------------------
     *
     * --------------------- GAME ----------------------
     */
    @Override
    public void drawGame() {
        finalMenuFrame.setVisible(false);
        menuFrame.setVisible(false);
        highScoreFrame.setVisible(false);
        gameFrame.setVisible(true);

        gamePanel.repaint();
        gamePanel.revalidate();
    }

    /**
     *-------------------
     *
     *---- GAME OVER ----
     */
    @Override
    public void drawGameOver() {

        gamePanel.setGameOver(true);

        gameFrame.repaint();
    }

    /**
     *--------------------
     *
     *---- FINAL MENU ----
     */

    @Override
    public void drawFinalMenu() {
        menuFrame.setVisible(false);
        highScoreFrame.setVisible(false);
        gameFrame.setVisible(false);
        finalMenuFrame.setVisible(true);

        drawFinalScore();

        drawTyping();

        finalMenuFrame.repaint();
    }

    @Override
    protected void drawFinalScore() {
        JLabel gameOver = new JLabel("GAME OVER");
        gameOver.setForeground(Color.RED);
        gameOver.setFont(new Font("Serif", Font.BOLD, 48));
        gameOver.setBounds(350, 150, 500, 100);
        finalMenuFrame.getContentPane().add(gameOver);

        String score = String.valueOf(game.getScore());
        int size = score.length();

        char[] zero = new char[9 - size];

        for(int i = 0; i < 9 - size; ++i){
            zero[i] = '0';
        }

        String output = new String(zero) + score;

        JLabel finalScore = new JLabel("FINAL SCORE: " + output);
        finalScore.setFont(new Font("Serif", Font.BOLD, 25));
        finalScore.setBounds(350, 200, 500, 200);
        finalMenuFrame.getContentPane().add(finalScore);
    }

    @Override
    protected void drawTyping() {
        JLabel name = new JLabel("Your name: ");
        name.setFont(new Font("Serif", Font.BOLD, 20));
        name.setBounds(275, 300, 300, 200);
        finalMenuFrame.getContentPane().add(name);

        JLabel info1 = new JLabel("(Name has a maximum of 15 characters)");
        info1.setBounds(400, 450, 300, 50);
        finalMenuFrame.getContentPane().add(info1);

        JLabel info2 = new JLabel("(Leave it empty to not save anything)");
        info2.setBounds(400, 475, 300, 50);
        finalMenuFrame.getContentPane().add(info2);

        JTextField t1 = new JTextField();
        t1.setBounds(400,380, 300,30);
        finalMenuFrame.getContentPane().add(t1);
    }

    /**
     *--------------------------------------------------
     *
     *------------------- HIGH SCORE -------------------
     */
    @Override
    public void drawHighScoreMenu() {

        drawHighScores();

        drawBackButton();

        highScoreFrame.repaint();
    }

    @Override
    public void drawHighScores() {
        int[] scores = game.getScores();
        String[] names = game.getHighScoreNames();

        for (int i = 0; i < 10; i++) {

            JLabel n = new JLabel(names[i]);
            n.setBounds(200, 50 + 65*i, 200, 100);
            highScoreFrame.getContentPane().add(n);

            String score = String.valueOf(scores[i]);
            int size = score.length();

            char[] zero = new char[9 - size];

            for(int j = 0; j < 9 - size; j++){
                zero[j] = '0';
            }

            String output = new String(zero) + score;

            JLabel o = new JLabel(output);
            o.setBounds(700, 50 + 65*i, 200, 100);
            highScoreFrame.getContentPane().add(o);
        }
    }

    @Override
    public void drawBackButton() {
        JButton back = new JButton("RETURN");
        back.addActionListener(actionEvent -> {
            game.menuProcessKey("ARROWUP");
            highScoreFrame.setVisible(false);
            menuFrame.setVisible(true);
        });
        back.setBounds(25, 600, 100, 100);

        highScoreFrame.getContentPane().add(back);
    }

    /**
     *--------------------------------------------------
     *
     *
     */
    @Override
    public String readInput() {
        String input = null;

        if(key == null)
            return null;

        if(key.getID() == KeyEvent.KEY_PRESSED){
            switch (key.getKeyCode()){
                //ArrowDown
                case KeyEvent.VK_DOWN:
                    input = "ARROWDOWN";
                    break;
                //ArrowLeft
                case KeyEvent.VK_LEFT:
                    input = "ARROWLEFT";
                    break;
                //ArrowUP
                case KeyEvent.VK_UP:
                    input = "ARROWUP";
                    break;
                //ArrowRight
                case KeyEvent.VK_RIGHT:
                    input = "ARROWRIGHT";
                    break;
                default:
                    break;
            }
        }

        else {
            switch(key.getKeyCode()){
                //Enter
                case KeyEvent.VK_ENTER:
                    input = "ENTER";
                    break;
                //BackSpace
                case KeyEvent.VK_SPACE:
                    input = "DELETE";
                    break;
                //EOF
                case 157:
                    input = "STOP";
                    break;
                //q
                case KeyEvent.VK_Q:
                    input = "QUIT";
                    break;
                //z
                case KeyEvent.VK_Z:
                    input = "ROTATELEFT";
                    break;
                //x
                case KeyEvent.VK_X:
                    input = "ROTATERIGHT";
                    break;
                //r
                case KeyEvent.VK_R:
                    input = "RESTART";
                    break;
                //e
                case KeyEvent.VK_E:
                    input = "BANK";
                    break;
                default:
                    break;
            }
        }

        key = null;

        return input;
    }

    @Override
    public void closeScreen() {
        menuFrame.setVisible(false);
        gameFrame.setVisible(false);
        highScoreFrame.setVisible(false);
        finalMenuFrame.setVisible(false);
    }
}