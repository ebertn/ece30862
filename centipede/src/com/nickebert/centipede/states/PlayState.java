package com.nickebert.centipede.states;

import com.nickebert.centipede.GamePanel;
import com.nickebert.centipede.Window;
import com.nickebert.centipede.board.MushroomGrid;
import com.nickebert.centipede.entity.*;
import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.utils.GridPoint;
import com.nickebert.centipede.utils.KeyHandler;
import com.nickebert.centipede.utils.MouseHandler;
import com.nickebert.centipede.utils.Vector2f;

import java.awt.*;
import java.io.File;
import java.util.ArrayList;
import java.util.Random;
import java.util.Vector;
import java.util.concurrent.TimeUnit;

import static java.lang.Thread.sleep;

public class PlayState extends GameState {

    private Player player;
    private ArrayList<Bullet> bullets;
    private MushroomGrid mushGrid;
    private ArrayList<Centipede> centipedes;
    private final int centipedeLength = 6;
    private Vector2f centipedeStart;
    private Spider spider;

    public static File bulletSound;

    protected int points;


    public PlayState(GameStateManager gsm){
        super(gsm);

        bulletSound = new File("/home/ebertn/School/ece30862/centipede/sounds/bullet_sound.wav");

        bullets = new ArrayList<Bullet>();
        player = new Player(new Sprite("Empty"), bullets);
        mushGrid = new MushroomGrid(bullets);

        centipedeStart = mushGrid.posFromGridPoint(new GridPoint(0, 0));
        centipedeStart.x -= Centipede.rad;
        centipedeStart.y -= Centipede.rad;

        centipedes = new ArrayList<Centipede>();
        createCentipede(centipedeStart, centipedeLength);

        spider = new Spider(new Sprite("Empty"), bullets);

        points = 0;

    }

    public void update(){
        player.update();

        points += mushGrid.update();

        Centipede c;
        for(int i = 0; i < centipedes.size(); i++){
            c = centipedes.get(i);
            if(!c.isAlive()) {
                centipedes.remove(i);
            } else {
                points += c.update();
            }

            if(player.getBounds().collides(c.getBounds())){
                playerDeath();
                return;
            }
        }

        if(centipedes.size() <= 0){
            points += 600;
            createCentipede(centipedeStart, centipedeLength);
        }

        Bullet b;
        for(int i = 0; i < bullets.size(); i++){
            b = bullets.get(i);
            if(b.removable()) {
                bullets.remove(i);
            } else {
                b.update();
            }
        }

        points += spider.update();

        if(player.getBounds().collides(spider.getBounds())){
            playerDeath();
            return;
        }

        if(player.lives <= 0){
            restartGame();
        }
    }

    public void input(MouseHandler mouse, KeyHandler key){
        player.input(mouse, key);
    }

    public void render(Graphics2D g){

        player.render(g);

        for(Centipede c: centipedes){
            c.render(g);
        }

        for(Bullet b: bullets){
            b.render(g);
        }

        mushGrid.render(g);

        spider.render(g);

        renderStats(g);

    }

    public void renderStats(Graphics2D g){
        g.setColor(new Color(0, 174, 169));
        g.setFont(new Font("Arial", Font.PLAIN, Window.score_height));
        g.drawString("Score: " + points, 10, Window.game_height + Window.score_height - 10);

        g.drawString("Lives: " + player.lives, Window.game_width - 200, Window.game_height + Window.score_height - 10);
    }

    private void playerDeath(){
        player.lives--;
        points += mushGrid.restore();
        centipedes.clear();
        createCentipede(centipedeStart, centipedeLength);
        bullets.clear();
        spider = spider = new Spider(new Sprite("Empty"), bullets);
    }

    private void restartGame(){
        player.lives = 3;
        points = 0;
        centipedes.clear();
        createCentipede(centipedeStart, centipedeLength);
        mushGrid = new MushroomGrid(bullets);
    }

    private void createCentipede(Vector2f startPos, int len){
        Sprite sprite = new Sprite("Empty");
        Centipede cur;
        Centipede ahead = new Centipede(sprite, new Vector2f(startPos.x, startPos.y), bullets, mushGrid);
        centipedes.add(ahead);
        for(int i = 1; i < len; i++){
            cur = new Centipede(sprite, ahead);
            centipedes.add(cur);
            ahead = cur;
        }
    }
}
