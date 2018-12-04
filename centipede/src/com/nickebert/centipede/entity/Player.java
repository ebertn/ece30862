package com.nickebert.centipede.entity;

import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.utils.Collision;
import com.nickebert.centipede.utils.KeyHandler;
import com.nickebert.centipede.utils.MouseHandler;
import com.nickebert.centipede.utils.Vector2f;
import com.nickebert.centipede.Window;

import java.awt.*;
import java.util.ArrayList;

public class Player extends Entity {

    private final int width = 30;
    private final int height = 30;

    private ArrayList<Bullet> bullets;
    private long last_shot_time = -1;
    private final int next_bullet_delay_nano = 200000000;

    public Player(Sprite sprite, ArrayList<Bullet> bullets){
        super(sprite, null);

        this.setMaxSpeed(0); // Mouse directly controls position
        this.bullets = bullets;

        this.hitBounds = new Collision(pos, width, height);

    }

    public int update() {
        super.update();

        return points;
    }

    @Override
    public void bulletHit() {}

    @Override
    public void render(Graphics2D g) {
        g.setColor(new Color(234, 255, 77));
        g.fillRect((int) this.pos.x - width/2, (int) this.pos.y, width, height);
    }

    public void input(MouseHandler mouse, KeyHandler key){
        super.input(mouse, key);

        this.pos.setX(mouse.getX());
        this.pos.setY(mouse.getY());

        if(last_shot_time + next_bullet_delay_nano < System.nanoTime()
                && key.attack.down){
            bullets.add(new Bullet(new Sprite("Empty"), (int) pos.x, (int) pos.y));
            last_shot_time = System.nanoTime();
        }
    }
}
