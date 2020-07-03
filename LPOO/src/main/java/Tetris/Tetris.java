package Tetris;

import Tetris.Controller.Game;

import javax.swing.*;

public class Tetris {

    public static void main(String[] args) {
        JFrame frame=new JFrame("Choose View Mode");
        frame.setLayout(new BoxLayout(frame.getContentPane(),BoxLayout.X_AXIS));

        JButton button1=new JButton("Lanterna");
        button1.addActionListener(actionEvent->{
            frame.setVisible(false);
            new Thread() {
                @Override
                public void run() {
                    Game game = new Game("LANTERNA");
                    game.run();
                }
            }.start();
        });
        button1.setBounds(30,115,100,40);

        JButton button2=new JButton("Swing");
        button2.addActionListener(actionEvent->{
            frame.setVisible(false);
            new Thread() {
                @Override
                public void run() {
                    Game game = new Game("SWING");
                    game.run();
                }
            }.start();
        });
        button2.setBounds(150,115,100,40);

        frame.getContentPane().add(button1);
        frame.getContentPane().add(button2);

        frame.setSize(300,300);//400 width and 500 height

        frame.setLayout(null);//using no layout managers
        frame.setVisible(true);
    }
}
