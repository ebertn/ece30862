package com.nickebert.centipede.utils;

public class Collision {

    private Vector2f pos;
    private float width;
    private float height;

    public Collision(Vector2f pos, int w, int h){
        this.pos = pos;
        this.width = w;
        this.height = h;
    }

    public Vector2f getPos(){ return pos; }

    public float getWidth() { return width; }
    public float getHeight() { return height; }

    public void setBox(Vector2f pos, int w, int h){
        this.pos = pos;
        this.width = w;
        this.height = h;

    }

    public void setWidth(float f){ this.width = f; }
    public void setHeight(float f) { this.height = f; }

    public boolean collides(Collision bBox){
        // ax & ay are for this object
        float ax = pos.x + width / 2;
        float ay = pos.y + height / 2;

        // bx & by are for dbox object
        float bx = bBox.pos.x + bBox.getWidth() / 2;
        float by = bBox.pos.y + bBox.getHeight() / 2;

        if(Math.abs(ax - bx) < (width / 2) + bBox.getWidth() / 2) {
            if (Math.abs(ay - by) < (height / 2) + bBox.getHeight() / 2) {
                return true;
            }
        }

        ax = pos.x - width / 2;
        ay = pos.y - height / 2;

        // bx & by are for dbox object
        bx = bBox.pos.x - bBox.getWidth() / 2;
        by = bBox.pos.y - bBox.getHeight() / 2;

        if(Math.abs(ax - bx) < (width / 2) + bBox.getWidth() / 2) {
            if (Math.abs(ay - by) < (height / 2) + bBox.getHeight() / 2) {
                return true;
            }
        }

        return false;
    }


}
