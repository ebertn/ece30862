package com.nickebert.centipede.board;

import com.nickebert.centipede.Window;
import com.nickebert.centipede.entity.Bullet;
import com.nickebert.centipede.entity.Mushroom;
import com.nickebert.centipede.graphics.Sprite;
import com.nickebert.centipede.utils.GridPoint;
import com.nickebert.centipede.utils.Vector2f;

import java.awt.*;
import java.util.ArrayList;

public class MushroomGrid {

    private Mushroom[][] grid;

    private ArrayList<Bullet> bullets;

    private static int winWidth;
    private static int winHeight;
    public static int mushSideLen;

    public static int numRows;
    public static int numCols;

    private final float mushChance = 0.1f;
    public final static int playerAreaSize = 6;
    public final static int centipedeAreaSize = 1;

    protected int points;

    public MushroomGrid(ArrayList<Bullet> bullets){
        this.bullets = bullets;

        winWidth = Window.game_width;
        winHeight = (int) (Window.game_height);

        mushSideLen = 2 * Mushroom.rad;

        numRows = (winWidth + mushSideLen) / mushSideLen - 1;
        numCols = (winHeight + mushSideLen) / mushSideLen;

        grid = new Mushroom[numRows][numCols];
        points = 0;

        generateGrid();
    }

    public int update(){
        points = 0;
        Mushroom m;
        for(int col = 0; col < numCols; col++) {
            for (int row = 0; row < numRows; row++) {
                m = grid[row][col];
                if(m != null){
                    if(!m.isAlive()) {
                        grid[row][col] = null;
                    } else {
                        points += m.update();
                    }
                }
            }
        }

        return points;
    }

    public int restore(){
        int points = 0;
        Mushroom m;
        for(int col = 0; col < numCols; col++) {
            for (int row = 0; row < numRows; row++) {
                m = grid[row][col];
                if(m != null && m.lives < 3){
                    m.lives = 3;
                    points += 10;
                }
            }
        }

        return points;
    }

    public void render(Graphics2D g){
        Mushroom m;
        for(int col = 0; col < numCols; col++) {
            for (int row = 0; row < numRows; row++) {
                m = grid[row][col];
                if(m != null){
                    m.render(g);
                }
            }
        }
    }

    private void generateGrid(){
        for(int col = 1; col < numCols; col++){
            for(int row = 1; row < numRows - 1; row++){
                if(col < numCols - playerAreaSize - centipedeAreaSize
                        && generateMush() && (!hasMush(row-1, col-1)
                        && !hasMush(row+1, col-1))){
                    int posX = row * mushSideLen + mushSideLen / 2;
                    int posY = col * mushSideLen + mushSideLen / 2;

                    grid[row][col] = new Mushroom(new Sprite("Empty"),
                            new Vector2f(posX, posY), bullets);
                }
            }
        }
    }

    // Should a mushroom be created?
    private boolean generateMush(){
        return Math.random() < mushChance;
    }

    public boolean hasMush(int row, int col){
        return hasMush(new GridPoint(row, col));
    }

    public boolean hasMush(GridPoint gp){
        return !isWall(gp) && !(grid[gp.row][gp.col] == null);
    }

    public boolean isWall(GridPoint gp){
        return gp.row >= numRows || gp.row < 0;
    }

    public static GridPoint gridPointFromPos(Vector2f pos){
        int row = (int) (((pos.x) / winWidth) * numRows);
        int col = (int) (((pos.y) / winHeight) * numCols);

        return new GridPoint(row, col);
    }

    public static Vector2f posFromGridPoint(GridPoint gp){
        int posX = gp.row * mushSideLen + mushSideLen / 2;
        int posY = gp.col * mushSideLen + mushSideLen / 2;

        return new Vector2f(posX, posY);
    }

    public void addMushroom(GridPoint gp){
        int posX = gp.row * mushSideLen + mushSideLen / 2;
        int posY = gp.col * mushSideLen + mushSideLen / 2;
        grid[gp.row][gp.col] = new Mushroom(new Sprite("Empty"),
                new Vector2f(posX, posY), bullets);
    }

}
