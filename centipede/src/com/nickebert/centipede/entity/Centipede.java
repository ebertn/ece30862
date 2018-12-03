package com.nickebert.centipede.entity;

import com.nickebert.centipede.board.MushroomGrid;
import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.utils.GridPoint;
import com.nickebert.centipede.utils.Vector2f;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.util.ArrayList;

public class Centipede extends Entity {

    private Centipede ahead, back; // Centipede is a doubly linked list
    private GridPoint gridPos;
    private boolean alive;
    public static final int rad = 12;

    public ArrayList<Bullet> bullets;
    private MushroomGrid mg;

    public static final int segmentLen = MushroomGrid.mushSideLen;

    private boolean passedGridLine;

    private int dir, prevDir;
    private final int LEFT = -1;
    private final int DOWN = 0;
    private final int RIGHT = 1;
    private final int UP = 2;

    public Centipede(Sprite sprite, Vector2f pos, ArrayList<Bullet> bullets, MushroomGrid mg){
        super(sprite);

        this.pos = pos;
        this.bullets = bullets;

        this.gridPos = mg.gridPointFromPos(pos);

        this.mg = mg;

        this.dir = LEFT;
        this.prevDir = LEFT;
        this.passedGridLine = false;
        this.maxSpeed = 3f;

        this.alive = true;

        this.ahead = null;
        this.back = null;
    }

    public Centipede(Sprite sprite, Centipede ahead, Centipede back) {
        this(sprite, new Vector2f(ahead.pos.x - segmentLen, back.pos.y), ahead.bullets, ahead.mg);

        this.ahead = ahead;
        this.back = back;

    }

    // use gridPointFromPos

    public void update() {
        //super.update();

        gridPos = mg.gridPointFromPos(pos);
        if(dir == RIGHT)
            System.out.println("Dir = Right");
        else if(dir == LEFT)
            System.out.println("Dir = Left");
        else
            System.out.println("Dir = Down");
//
        if(prevDir == RIGHT)
            System.out.println("Prev dir = Right");
        else if(prevDir == LEFT)
            System.out.println("Prev dir = Left");
        else
            System.out.println("Prev dir = Down");

        if(isHead()){
            // Follow rules for head motion
            GridPoint next = new GridPoint(gridPos.row + dir, gridPos.col);
            if(dir == DOWN){
                // if down is finished, change dir
                System.out.println("First: " + passedGridLine + " " + (pos.y > 2 * (gridPos.col) * rad));
                System.out.println("pos.y: " + pos.y + ", middle: " + (2 * (gridPos.col) * rad));
                if(passedGridLine && (pos.y + 1) > 2 * (gridPos.col) * rad){ // In bottom half of box
                    System.out.println("Holaaaaaaaaaaaaaaaaaaaaa");
                    passedGridLine = false;
                    dir = prevDir;
                    changeDir();
                } else {
                    GridPoint down = new GridPoint(gridPos.row, gridPos.col + 1);
                    Vector2f dest = mg.posFromGridPoint(down);
                    GridPoint before = new GridPoint(gridPos);
                    moveDown(dest.y);

                    // Here it decides that down is the shit and
                    // all other directions must be eliminated.
                    // I have created down hitler

                    // Change passedGridLine, based on if col has changed after moveDown
                    this.gridPos = mg.gridPointFromPos(pos);
                    System.out.println("Second: " + (!passedGridLine) + " " + (before.col != gridPos.col));
                    if(!passedGridLine && before.col != gridPos.col){
                        System.out.println("passGridLine changed - before = (" + before.row + ", " + before.col +  "), after = (" + gridPos.row + ", " + gridPos.col + ")");
                        passedGridLine = true;
                    }

                }
            } else {
                //passedGridLine = false;
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
                        //System.out.println("right");
                        moveRight(dest.x);
                        dir = RIGHT;
                        prevDir = RIGHT;
                    } else if (dir == LEFT) {
                        //System.out.println("left");
                        moveLeft(dest.x);
                        dir = LEFT;
                        prevDir = LEFT;
                    }
                }
            }

            /*GridPoint next = new GridPoint(gridPos.row + dir, gridPos.col);
            if(dir == DOWN || (dir == RIGHT && pos.x > 2 * gridPos.row * rad + rad
                                || dir == LEFT && pos.x < 2 * gridPos.row * rad + rad)
                                && (mg.hasMush(next) || wallAdjacent())){
//                if(dir != DOWN && pos.y > 2 * gridPos.col * rad + rad){
//                    dir = prevDir;
//                    changeDir();
//                    //dir = RIGHT;
//                } else {
//                if(wallAdjacent()){
//                    dir = prevDir;
//                    changeDir();
//                }
                // Going down, but dir != DOWN

                System.out.println("Trying to go down " + dir);

                GridPoint down = new GridPoint(gridPos.row, gridPos.col + 1);
                Vector2f dest = mg.posFromGridPoint(down);
                moveDown(dest.y);
                if(dir != DOWN) {
                    dir = prevDir;
                    //dir = DOWN;
                } else {
                    System.out.println("Goes in here");
                    dir = prevDir;
                    //prevDir = dir;
                    changeDir();
                }
                    //changeDir();

//                }
            } else {//if (pos.y > 2 * gridPos.col * rad + rad){
                if(pos.y < 2 * gridPos.col * rad + rad){
                    prevDir = dir;
                    dir = DOWN;
//                    dir = prevDir;
//                    changeDir();
                } else {
                    System.out.print("Trying to go ");
                    Vector2f dest = mg.posFromGridPoint(next);

                    if(dir == RIGHT) {
                        System.out.println("right");
                        moveRight(dest.x);
                        dir = RIGHT;
                        prevDir = RIGHT;
                    } else if (dir == LEFT){
                        System.out.println("left");
                        moveLeft(dest.x);
                        dir = LEFT;
                        prevDir = LEFT;
                    }
                }
            }*/
        } else {
            // Follow ahead
            //moveToward(ahead.gridPos);
        }
    }

    private boolean wallAdjacent(){
        GridPoint left = new GridPoint(gridPos.row - 1, gridPos.col);
        GridPoint right = new GridPoint(gridPos.row + 1, gridPos.col);

        return mg.isWall(left) || mg.isWall(right);
    }

    private void changeDir(){
        if(dir == RIGHT){
            dir = LEFT;
            prevDir = LEFT;
        } else if(dir == LEFT) {
            dir = RIGHT;
            prevDir = RIGHT;
        }
    }

    private void moveRight(float x){
        if(pos.x < x){
            dx = maxSpeed;

        }
        dy = 0;

        this.pos.addX(dx);
        this.pos.addY(dy);
    }

    private void moveLeft(float x){
        if(pos.x > x){
            dx = -maxSpeed;
        }
        dy = 0;

        this.pos.addX(dx);
        this.pos.addY(dy);
    }

    private void moveDown(float y){
        if(pos.y < y){
            dy = maxSpeed;
        }
        dx = 0;

        this.pos.addX(dx);
        this.pos.addY(dy);
    }

    private void moveToward(GridPoint gp){
        Vector2f dest = mg.posFromGridPoint(gp);
        dest = new Vector2f(dest.x, dest.y);
        System.out.println("dest.x: " + dest.x + ", dest.y: " + dest.y);
        System.out.println("pos.x: " + pos.x + ", pos.y: " + pos.y);
        Vector2f dir = dest.sub(pos).mult(1/dest.sub(pos).mag());
        dx = dir.mult(maxSpeed).x;
        dy = -dir.mult(maxSpeed).y;
        System.out.println("dx; " + dx + ", dy: " + dy);

//        if(dir == RIGHT){
//            System.out.println("Going right");
//            dx = maxSpeed;
//            dy = 0;
//        } else if (dir == LEFT){
//            System.out.println("Going left");
//            dx = -maxSpeed;
//            dy = 0;
//        } else if (dir == DOWN){
//            System.out.println("Going down");
//            dx = 0;
//            dy = maxSpeed;
//        }
    }

    private void moveToward(int row, int col){
        moveToward(new GridPoint(row, col));
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
