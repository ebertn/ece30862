// Hola

package com.nickebert.centipede.entity;

import com.nickebert.centipede.board.MushroomGrid;
import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.utils.Collision;
import com.nickebert.centipede.utils.GridPoint;
import com.nickebert.centipede.utils.Vector2f;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.util.ArrayList;

public class Centipede extends Entity {

    private Centipede ahead, back; // Centipede is a linked list
    private GridPoint gridPos;
    public static final int rad = 12;

    public ArrayList<Bullet> bullets;
    private MushroomGrid mg;

    public static final int segmentLen = MushroomGrid.mushSideLen;

    private boolean passedGridLine;
    private int lives = 2;

    private int dir, prevDir;
    private final int LEFT = -1;
    private final int DOWN = 0;
    private final int RIGHT = 1;
    private final int UP = 2;

    public Centipede(Sprite sprite, Vector2f pos, ArrayList<Bullet> bullets, MushroomGrid mg){
        super(sprite, bullets);

        this.pos = pos;
        this.bullets = bullets;

        this.gridPos = mg.gridPointFromPos(pos);

        this.hitBounds = new Collision(pos, rad, rad);

        this.mg = mg;

        this.dir = RIGHT;
        this.prevDir = dir;
        this.passedGridLine = false;
        this.maxSpeed = 3f;

        this.alive = true;

        this.ahead = null;
        this.back = null;
    }

    public Centipede(Sprite sprite, Centipede ahead) {
        this(sprite, new Vector2f(ahead.pos.x - 2*rad, ahead.pos.y), ahead.bullets, ahead.mg);

        this.ahead = ahead;
        this.ahead.setBack(this);
    }

    public void setBack(Centipede c){
        this.back = c;
    }

    public int update() {
        if(!alive) { return 0; }

        super.update();
        gridPos = mg.gridPointFromPos(pos);

        if(isHead()){
            // Follow rules for head motion
            GridPoint next = new GridPoint(gridPos.row + dir, gridPos.col);
            if(dir == DOWN){
                // if down is finished, change dir
                if(passedGridLine && (pos.y + 1) > 2 * (gridPos.col) * rad){ // In bottom half of box
                    passedGridLine = false;
                    dir = prevDir;
                    changeDir();
                    prevDir = DOWN;
                } else {
                    GridPoint down = new GridPoint(gridPos.row, gridPos.col + 1);
                    Vector2f dest = mg.posFromGridPoint(down);
                    GridPoint before = new GridPoint(gridPos);
                    moveDown(dest.y);

                    this.gridPos = mg.gridPointFromPos(pos);
                    if(!passedGridLine && before.col != gridPos.col){
                        passedGridLine = true;
                    }

                }
            } else {
                // if should go down, change dir to down
                if((dir == RIGHT && pos.x > 2 * gridPos.row * rad + rad
                        || dir == LEFT && pos.x < 2 * gridPos.row * rad + rad)
                        && (mg.hasMush(next) || mg.isWall(next))){
                    if(mg.isWall(next) && gridPos.col == (mg.numCols - mg.playerAreaSize - mg.centipedeAreaSize)){
                        changeDir();
                    } else {
                        prevDir = dir;
                        dir = DOWN;
                    }
                } else {
                    Vector2f dest = mg.posFromGridPoint(next);
                    if (dir == RIGHT) {
                        moveRight(dest.x);
                        prevDir = dir;
                        dir = RIGHT;
                    } else if (dir == LEFT) {
                        moveLeft(dest.x);
                        prevDir = dir;
                        dir = LEFT;
                    }
                }
            }
        } else {
            dir = ahead.dir;
            prevDir = ahead.prevDir;
            moveTowardHead();
        }

        return this.points;
    }

    @Override
    public void bulletHit() {
        //mg.addMushroom(gridPos);
        lives--;
        points += 2;
        if(lives <= 0){
            alive = false;
            points += 5;
            if(back != null){
                back.ahead = null;
                back.changeDir();
            }
            if(ahead != null){ ahead.back = null; };
            ahead = null;
            back = null;
        }
    }

    private boolean wallAdjacent(){
        GridPoint left = new GridPoint(gridPos.row - 1, gridPos.col);
        GridPoint right = new GridPoint(gridPos.row + 1, gridPos.col);

        return mg.isWall(left) || mg.isWall(right);
    }

    private void changeDir(){
        prevDir = dir;
        if(dir == RIGHT){
            dir = LEFT;
            //prevDir = LEFT;
        } else if(dir == LEFT) {
            dir = RIGHT;
            //prevDir = RIGHT;
        }
    }

    private void moveRight(float x){
        if(pos.x < x){
            dx = maxSpeed;

        }
        dy = 0;

        this.pos.addX(dx);
        this.pos.addY(dy);
        dx = 0;
        dy = 0;
    }

    private void moveLeft(float x){
        if(pos.x > x){
            dx = -maxSpeed;
        }
        dy = 0;

        this.pos.addX(dx);
        this.pos.addY(dy);
        dx = 0;
        dy = 0;
    }

    private void moveDown(float y){
        if(pos.y < y){
            dy = maxSpeed;
        }
        dx = 0;

        this.pos.addX(dx);
        this.pos.addY(dy);
        dx = 0;
        dy = 0;
    }

    private void moveTowardHead(){
        if(pos.dist(ahead.pos) > 2 * rad){
            Vector2f orientation = (ahead.pos.sub(this.pos)).normalize();
            this.pos.addX(orientation.x * maxSpeed);
            this.pos.addY(orientation.y * maxSpeed);
        }
    }

    private boolean isHead(){
        return ahead == null;
    }

    @Override
    public void render(Graphics2D g) {
        if(alive) {
            g.setColor(new Color(174, 0, 9));
            g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            Shape theCircle = new Ellipse2D.Double(pos.x - rad, pos.y /*- rad*/, 2.0 * rad, 2.0 * rad);
            g.fill(theCircle);
        }
    }
}
