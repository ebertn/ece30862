package com.nickebert.centipede.entity;

import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.utils.Collision;
import com.nickebert.centipede.utils.KeyHandler;
import com.nickebert.centipede.utils.MouseHandler;
import com.nickebert.centipede.utils.Vector2f;
import com.nickebert.centipede.Window;

import java.awt.*;
import java.util.ArrayList;

public abstract class Entity {

    protected Sprite sprite;
    protected ArrayList<Bullet> bullets;
    public Vector2f pos;

    protected boolean up;
    protected boolean down;
    protected boolean right;
    protected boolean left;

    protected float dx;
    protected float dy;

    protected float maxSpeed;

    protected int points;
    protected boolean alive;
    public int lives;

    protected Collision hitBounds = null;

    public Entity(Sprite sprite, ArrayList<Bullet> bullets){
        this.sprite = sprite;
        this.bullets = bullets;
        this.pos = new Vector2f(Window.game_width / 2, 7 * Window.game_height / 8 );

        this.points = 0;
    }

    public void setSprite(Sprite sprite) {
        this.sprite = sprite;
    }

    public boolean getUp() { return up; }
    public boolean getDown() { return down; }
    public boolean getLeft() { return left; }
    public boolean getRight() { return right; }

    public void setMaxSpeed(float f) { maxSpeed = f; }

    public float getMaxSpeed() { return maxSpeed; }

    public Collision getBounds() { return hitBounds; }
    public float getSpeedx() {return dx; }
    public float getSpeedy() {return dy; }

    public int update(){
        this.points = 0;

        this.pos.addX(dx);
        this.pos.addY(dy);

        if(bullets != null) {
            Bullet b;
            for (int i = 0; i < bullets.size(); i++) {
                b = bullets.get(i);
                if (hitBounds.collides(b.getBounds())) {
                    bullets.remove(i);
                    bulletHit();
                }
            }
        }

        return this.points;
    }

    public boolean isAlive(){
        return alive;
    }

    public abstract void bulletHit();

    public abstract void render(Graphics2D g);

    public void input(MouseHandler mouse, KeyHandler key) {}
}
