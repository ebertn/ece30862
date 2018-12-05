package com.nickebert.centipede.utils;

public class Vector2f {

    public float x;
    public float y;

    public Vector2f() {
        x = 0;
        y = 0;
    }

    public Vector2f(Vector2f vec) {
        this.x = vec.x;
        this.y = vec.y;
    }

    public Vector2f(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public void addX(float f) {
        x += f;
    }

    public void addY(float f) {
        y += f;
    }

    public void setX(float f) {
        x = f;
    }

    public void setY(float f) {
        y = f;
    }

    public Vector2f sub(Vector2f v){
        return new Vector2f(x - v.x, y - v.y);
    }

    public Vector2f mult(float f){
        return new Vector2f(x * f, y * f);
    }

    public float mag(){
        return (float) Math.sqrt(x*x + y*y);
    }

    public void setVector(Vector2f vec) {
        this.x = vec.x;
        this.y = vec.y;
    }

    public void setVector(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public float dist(Vector2f v){
        return (float) Math.sqrt(Math.pow(v.x - this.x, 2) + Math.pow(v.y - this.y, 2));
    }

    public Vector2f normalize(){
        float norm = (float) Math.sqrt(Math.pow(this.x, 2) + Math.pow(this.y, 2));
        return new Vector2f(this.x / norm, this.y / norm);
    }

    public static Vector2f randUnitVector2f(){
        float xComp = (float) (2 * Math.random() - 1);
        float yComp = (float) (2 * Math.random() - 1);
        return new Vector2f(xComp, yComp).normalize();
    }

    @Override
    public String toString() {
        return x + ", " + y;
    }
}

