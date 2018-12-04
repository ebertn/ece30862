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

    public Mushroom(Sprite sprite, Vector2f pos, ArrayList<Bullet> bullets) {
        super(sprite, bullets);
        this.pos = pos;
        alive = true;
        this.bullets = bullets;

        this.hitBounds = new Collision(pos, rad, rad);
    }

    public int update() {
        if(alive) {
            super.update();
        }

        return points;
    }

    @Override
    public void bulletHit() {
        lives--;
        points += 1;
        if(lives <= 0){
            alive = false;
            points += 5;
        }

        //System.out.println("Bullet hit. Points = " + points);
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

}
