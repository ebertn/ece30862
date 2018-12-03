package com.nickebert.centipede.states;

import com.nickebert.centipede.Window;
import com.nickebert.centipede.board.MushroomGrid;
import com.nickebert.centipede.entity.Bullet;
import com.nickebert.centipede.entity.Centipede;
import com.nickebert.centipede.entity.Mushroom;
import com.nickebert.centipede.entity.Player;
import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.utils.GridPoint;
import com.nickebert.centipede.utils.KeyHandler;
import com.nickebert.centipede.utils.MouseHandler;
import com.nickebert.centipede.utils.Vector2f;

import java.awt.*;
import java.util.ArrayList;
import java.util.Random;
import java.util.Vector;

public class PlayState extends GameState {

    private Player player;
    private ArrayList<Bullet> bullets;
    private MushroomGrid mushGrid;
    private Centipede centipede;

    public PlayState(GameStateManager gsm){
        super(gsm);

        bullets = new ArrayList<Bullet>();
        player = new Player(new Sprite("Empty"), bullets);
        mushGrid = new MushroomGrid(bullets);

        Vector2f centipedeStart = mushGrid.posFromGridPoint(new GridPoint(mushGrid.numRows / 2, 1));
        System.out.println("----------" + centipedeStart.x + " " + centipedeStart.y);

        centipede = new Centipede(new Sprite("Empty"), centipedeStart, bullets, mushGrid);

//        GridPoint gp = mushGrid.gridPointFromPos(mushGrid.posFromGridPoint(new GridPoint(27, 1)));
//        System.out.println(gp.row + " " + gp.col);
//        Vector2f pos = mushGrid.posFromGridPoint(new GridPoint(0, 0));
//        System.out.println(gp.row + " " + gp.col);
    }

    public void update(){
        player.update();
        mushGrid.update();
        centipede.update();

        //System.out.println(centipede.pos.x + " " + centipede.pos.y);

        Bullet b;
        for(int i = 0; i < bullets.size(); i++){
            b = bullets.get(i);
            if(b.removable()) {
                bullets.remove(i);
            } else {
                b.update();
            }
        }
    }

    public void input(MouseHandler mouse, KeyHandler key){
        player.input(mouse, key);
    }

    public void render(Graphics2D g){
        player.render(g);
        centipede.render(g);

        for(Bullet b: bullets){
            b.render(g);
        }

        mushGrid.render(g);
    }
}
