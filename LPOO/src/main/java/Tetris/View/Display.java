package Tetris.View;

import Tetris.Controller.*;

public abstract class Display {

    /**
     * Instance variables.
     */
    protected Game game;
    protected char nameBuffer;

    /**
     * Constructor.
     */
    public Display(Game game) {
        this.game = game;
    }

    /**
     * Get functions
     * @return
     */
    public abstract char getNameBuffer();

    /**
     * Set function
     * @param nameBuffer
     */
    public abstract void setNameBuffer(char nameBuffer);

    /**
     * --------------------- VIEW MODE ----------------------
     *
     * DONE
     */


    /**
     * DONE
     */
    public abstract void initializeViewMode();

    /**
     * --------------------------------------------------
     *
     * --------------------- MENU ----------------------
     *
     * DONE
     */
    public abstract void drawMenu();

    /**
     *
     */
    public abstract void drawLogo();

    /**
     *--------------------------------------------------
     *
     * --------------------- GAME ----------------------
     */
    public abstract void drawGame();


    /**
     *--------------------------------------------------
     *
     *------------------- GAME OVER -------------------
     */

    /**
     * TBD
     */
    public abstract void drawGameOver();

    /**
     *--------------------------------------------------
     *
     *------------------- FINAL MENU -------------------
     */
    public abstract void drawFinalMenu();

    /**
     * DONE
     */
    protected abstract void drawFinalScore();

    /**
     * DONE
     */
    protected abstract void drawTyping();

    /**
     *--------------------------------------------------
     *
     *------------------- HIGH SCORE -------------------
     */
    public abstract void drawHighScoreMenu();

    /**
     * DONE
     */
    public abstract void drawHighScores();

    /**
     * DONE
     */
    public abstract void drawBackButton();

    /**
     *--------------------------------------------------
     *
     *
     */
    public abstract String readInput();

    /**
     *
     */
    public abstract void closeScreen();

}