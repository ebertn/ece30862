package com.nickebert.centipede.entity;

import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.utils.Collision;
import com.nickebert.centipede.utils.KeyHandler;
import com.nickebert.centipede.utils.MouseHandler;
import com.nickebert.centipede.utils.Vector2f;

import java.awt.*;

public abstract class Entity {

    protected Sprite sprite;
    public Vector2f pos;

    protected boolean up;
    protected boolean down;
    protected boolean right;
    protected boolean left;

    protected float dx;
    protected float dy;

    protected float maxSpeed;

    protected Collision hitBounds = null;

    public Entity(Sprite sprite){
        this.sprite = sprite;
        this.pos = new Vector2f(0, 0);
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

    public void update(){
        //if (Math.pow(dx, 2) + Math.pow(dy, 2) <= Math.pow(maxSpeed, 2) + 0.001) {
        this.pos.addX(dx);
        this.pos.addY(dy);
        //}
    }

    public abstract void render(Graphics2D g);

    public void input(MouseHandler mouse, KeyHandler key) {}
}
