package com.nickebert.centipede;

import javax.swing.JFrame;

public class Window extends JFrame {

    public static final int game_width = 1280;
    public static final int game_height = 720;

    public Window(){
        setTitle("Centipede");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setContentPane(new GamePanel(game_width, game_height));

        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }
}
