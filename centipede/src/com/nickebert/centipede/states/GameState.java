package com.nickebert.centipede.states;

import com.nickebert.centipede.utils.KeyHandler;
import com.nickebert.centipede.utils.MouseHandler;

import java.awt.*;

public abstract class GameState {

    private GameStateManager gsm;

    public GameState(GameStateManager gsm){
        this.gsm = gsm;
    }

    public abstract void update();
    public abstract void input(MouseHandler mouse, KeyHandler key);
    public abstract void render(Graphics2D g);
}
