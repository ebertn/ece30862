package com.nickebert.centipede.entity;

import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.utils.Collision;
import com.nickebert.centipede.utils.Vector2f;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.util.ArrayList;

public class Mushroom extends Entity {

    private ArrayList<Bullet> bullets;
    public static final int rad = 12;
    private int lives = 3;
    private boolean alive;

    public Mushroom(Sprite sprite, Vector2f pos, ArrayList<Bullet> bullets) {
        super(sprite);
        this.pos = pos;
        alive = true;
        this.bullets = bullets;

        this.hitBounds = new Collision(pos, rad, rad);
    }

    public void update() {
        super.update();

        Bullet b;
        for(int i = 0; i < bullets.size(); i++) {
            b = bullets.get(i);
            if (hitBounds.collides(b.getBounds())) {
                lives--;
                bullets.remove(i);
            }

            if(lives <= 0){
                alive = false;
            }
        }
    }

    @Override
    public void render(Graphics2D g) {
        if(alive) {
            g.setColor(new Color(0, 174, 93));
            g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            Shape theCircle = new Ellipse2D.Double(pos.x - rad, pos.y - rad, 2.0 * rad, 2.0 * rad);
            g.fill(theCircle);
        }
    }

    public boolean isAlive(){
        return alive;
    }
}
